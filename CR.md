# PBD-HLS Project report

## Table of contents
- [PBD-HLS Project report](#pbd-hls-project-report)
	- [Table of contents](#table-of-contents)
	- [Authors](#authors)
	- [Introduction](#introduction)
	- [Profiling](#profiling)
		- [On a standard computer (AMD Ryzen 7840HS)](#on-a-standard-computer-amd-ryzen-7840hs)
			- [Using gnu gprof](#using-gnu-gprof)
			- [Using high precision system timers](#using-high-precision-system-timers)
		- [On the Zybo Z7](#on-the-zybo-z7)
		- [comparison](#comparison)
		- [With -O3](#with--o3)
		- [General remarks](#general-remarks)
	- [Programming the FPGA by SSH](#programming-the-fpga-by-ssh)
	- [Algorithmic modifications](#algorithmic-modifications)
		- [Approximations of sigmoid](#approximations-of-sigmoid)
		- [Replacing convolutions by matrix multiplications in layers 3 and 4](#replacing-convolutions-by-matrix-multiplications-in-layers-3-and-4)
		- [Fully utilizing the CPU capabilities](#fully-utilizing-the-cpu-capabilities)
	- [New profiling of the full CPU optimized version](#new-profiling-of-the-full-cpu-optimized-version)
	- [Utilizing the integrated FPGA for](#utilizing-the-integrated-fpga-for)
	- [Demonstration setup](#demonstration-setup)

## Authors
- Rémy Citérin
- Clément Hondemarck
- Yujia Sun

## Introduction
This project takes place as part of the "Platform Based Design - High Level Synthesis" course of Sorbonne Université.

It aims at implementing the Lenet Algorithm for optical character recognition on a Digilent ZYBO-Z7 board, which implements a Zynq-7000 SoC, made of a dual core Cortex A9 CPU and an integrated Xilinx FPGA.

The overall objective is to explore the space of solutions to the optimization problem based on the following factors :
- Throughput
- Latency
- Power consumption

In this particular situation, throughput and latency are to be prioritized.
Those goals are to be reached starting from a fully software based algorithm, and after that implementing hardware accelerators for the relevant parts.

## Profiling
Before trying to make hardware accelerators for anything, we need to look at which part(s) of the program is (are) responsible of the bottleneck, if any.
To check this, we need to establish a profile by measuring execution times on a large number of repetitions.

### On a standard computer (AMD Ryzen 7840HS)
#### Using gnu gprof
gprof, or GNU Profiler, is a utility which automatically measures the time used by each function. More specifically, it only measures the time spent in the user space.

To use it, we need to compile the main code using gcc and the -gp flag, at both compiling and link editing steps.
After that, we run the program as usual, and then call `gprof` with the executable as parameter.
This produces a report, of which the following section is the one we look at with the most interest :

  %   cumulative   self              self     total
 time   seconds   seconds    calls  us/call  us/call  name
 57.13      4.72     4.72    10000   472.44   472.44  calculateLayer3
 36.55      7.75     3.02    10000   302.28   302.28  calculateLayer4
  6.29      8.27     0.52    10000    52.05    52.05  calculateLayer2
  0.12      8.28     0.01    10000     1.00     1.00  InitHostMem
  0.00      8.28     0.00   120000     0.00     0.00  dtime
  0.00      8.28     0.00    10000     0.00     0.00  calculateLayer1
  0.00      8.28     0.00    10000     0.00     0.00  calculateLayer5

InitHostMem is the function call that is in charge of initializing the weights of the network. It spends most of its time in the kernel space, and is not the most relevant part, as it is in principle only called once at the beginning of the program.
Similarly, dtime calls are to be ignored as they are only enabled for profiling purposes (cf. next section), and will be removed for the real application.

Moving to our actual calculations, we see that most of the time is spent in the calculations for the layer3 (~57% of the time), for the layer4 (~37%), and in a smaller proportion for the layer2 (~6%).
What seems odd at first glance is that the calculations for layers 1 and 5 seem to be so fast that they use absolutely no time in user space.
This of course is not truly the case, and is caused by a fundamental limit of gprof : its smallest resolution is 1µS. As such, if a function call only uses for instance 0.8µs, it should total a user space time of 8ms over 10 000 repetitions, but will be represented as 0 because each individual measurement is too small to be counted.

#### Using high precision system timers
Most modern computers come with very high frequency clocks and precise timers, usually able to measure up to the nanosecond. This can help solve the resolution issue that we encounter with gprof. To do that, we use system timers through the dtime library :

```C
CHRONO0_VAR ; //tInit;
CHRONO1_VAR ; //tLayer1;
CHRONO2_VAR ; //tLayer2;
CHRONO3_VAR ; //tLayer3;
CHRONO4_VAR ; //tLayer4;
CHRONO5_VAR ; //tLayer5;
for (int nIter = 0; nIter < 10000; ++nIter)
{
	CHRONO0_START;
	InitHostMem(Layer1_Weights_CPU, Layer2_Weights_CPU, Layer3_Weights_CPU, Layer4_Weights_CPU);
	CHRONO0_STOP;
	CHRONO1_START;
	calculateLayer1(Input, Layer1_Neurons_CPU);
	CHRONO1_STOP;
	CHRONO2_START;
	calculateLayer2(Layer1_Neurons_CPU, Layer1_Weights_CPU, Layer2_Neurons_CPU);
	CHRONO2_STOP;
	CHRONO3_START;
	calculateLayer3(Layer2_Neurons_CPU, Layer2_Weights_CPU, Layer3_Neurons_CPU);
	CHRONO3_STOP;
	CHRONO4_START;
	calculateLayer4(Layer3_Neurons_CPU, Layer3_Weights_CPU, Layer4_Neurons_CPU);
	CHRONO4_STOP;
	CHRONO5_START;
	calculateLayer5(Layer4_Neurons_CPU, Layer4_Weights_CPU, Layer5_Neurons_CPU);
	CHRONO5_STOP;
	scoremax = FLT_MIN;
	int indexmax = -1;
	for (i = 0; i < 10; i++)
	{
		//printf("%d : %f\n", i, Layer5_Neurons_CPU[i]);
		if (Layer5_Neurons_CPU[i] > scoremax)
		{
			scoremax = Layer5_Neurons_CPU[i];
			indexmax = i;
		}
	}
	//printf("Le resultat est : %d \n", indexmax);
}
printf("temps init total : %lf\n", CHRONO0_EVAL);
printf("temps Layer1 total : %lf\n", CHRONO1_EVAL);
printf("temps Layer2 total : %lf\n", CHRONO2_EVAL);
printf("temps Layer3 total : %lf\n", CHRONO3_EVAL);
printf("temps Layer4 total : %lf\n", CHRONO4_EVAL);
printf("temps Layer5 total : %lf\n", CHRONO5_EVAL);
double somme = CHRONO0_EVAL + CHRONO1_EVAL + CHRONO2_EVAL + CHRONO3_EVAL + CHRONO4_EVAL + CHRONO5_EVAL;
printf("temps global total : %lf\n", somme);
```

We compiled this code using the following command line : 
```bash
gcc fonctions_ES.c timers_b.c original.c -o original.x -I. -lm -O0
```

Using those timers, simply running the program gives us the time spent by each function call, including both user space and kernel space times.

```log
temps init total : 0.347915
temps Layer1 total : 0.004505
temps Layer2 total : 0.767018
temps Layer3 total : 4.873730
temps Layer4 total : 3.107407
temps Layer5 total : 0.029057
temps global total : 9.129632
```

### On the Zybo Z7
Here, we directly use the precise integrated timers to check for time distribution, as we want to choose which layer to optimize first, and then choose which layer would go on the FPGA part.
For this, we used the same exact code, with the same exact compilation flags, and got the following results : 

```log
temps init total : 16.537004
temps Layer1 total : 0.129045
temps Layer2 total : 25.224844
temps Layer3 total : 143.864549
temps Layer4 total : 112.462388
temps Layer5 total : 0.581014
temps global total : 298.798844
```

### comparison
The first thing that we see is of course slower calculations on all layers : the smallest increase in computation time is on Layer 5 with a 20x increase, while the largest one is on the memory initialisation with a 47.5x increase in time.  
This last result points to a much slower memory system, mainly because of a L1 cache that is too small to keep all weights at once, hence continued cache misses.  
On other layers that don't rely as much on the memory system, we see up to a 32.8x increase.

### With -O3
As we've seen, the execution is really slow and can easily be improved first by allowing the compiler to use aggressive optimizations.
Using -O3 option, we get the following results : 

| layer  | Ryzen 7840HS | Zybo Z7   | ratio |
| :----- | :----------- | :-------- | :---- |
| init   | 0.338411     | 16.261901 | 48.05 |
| Layer1 | 0.004810     | 0.137579  | 28.60 |
| Layer2 | 0.188852     | 6.246568  | 33.07 |
| Layer3 | 1.138083     | 21.401608 | 18.80 |
| Layer4 | 0.774708     | 22.229725 | 28.69 |
| Layer5 | 0.009700     | 0.212412  | 21.89 |
| global | 2.454564     | 66.489793 | 27.08 |

We can see first that the init stage doesn't change much, indicating that the bottleneck at this stage is the memory system, in both cases.  
However, while we see improvements on both systems, the improvement is slightly better on the Zybo Z7 system, as the ratio goes down to ~ x27, compared to ~ x32.7 in O0.

### General remarks
We see that the heaviest layers are the layers 3 and 4, with repesctively 32.2% and 33.4% of the total time used on the Zybo Z7 in O3. After that, layer 2 takes 9.4% of the time, and those 3 layers account for a cumulated 75.0% of the total time used.

As such, those layers will be the target of most of our optimizations, as trying to improve the memory initialization is not easy with simply parallelization, and in principle only happens once at the beginning of the program; and seeing that layers 1 and 5 are relatively extremely small.

## Programming the FPGA by SSH
To program the FPGA and the ARM cpu, on possibility is to use it without an operating system (in
bare-metal). But this make the process of iterating on multiple designs very slow. And it make
almost impossible to work on the project remotely. So another possibility is to install Linux on the
board, doing so it is possible to use the board by SSH, read the weight by opening a file, and
program the FPGA with the command `cat my_bitstream.bit > /dev/xdevcfg`.

To do so we used `petalinux`, the tools from Xilinx to configure and generate the bootloader, linux
kernel and file system (even I we used a different root file system that the one generated by
petalinux). But this come with a cost because `petalinux` is sometimes buggy, and the default
configurations of the zybo board doesn't suite our requirements.

As example the default configuration doesn't allow to program the FPGA at runtime, and use a RAM
file-system. This is motly because `petalinux` is built to be used in a production environment
instead of a research environment like we want to. So we tried to configure it to solve both of
those issues, but we encountered a certain amount of bugs in the process. In particular modern
versions of `petalinux` use a tool named `fpga_util` to program the FPGA but we didn't succede to
generate a working device-tree with it. So we decided to switch to an older version before the
use of `fpga_util` (from 2017), that use `/dev/xdevcfg` instead. In particular `fpga_util` is
designed to update the FPGA configuration at runtime, and the device tree to simplify the
communication with the FPGA. But this second fonctionality is not necessary because we can just
communicate with the it using `/dev/mem` instead.

But out first tentatives to do so where unsuccessfull, because the driver for `/dev/xdevcfg` where
broken, because it used non-voltaile load to check if the DMA finished it's operations, resulting in
a timeout from `cat`. We tried to apply the patch dirrectly with petalinux, using
`https://github.com/Xilinx/linux-xlnx/commit/a920e66a043`, but it didn't worked: the generated
linux kernel was two times smaller (something very surprising for a two lines patch), so didn't
boot. So we applied the patch by hand and tell to petalinux to use our own modified version of linux
as an external source.

## Algorithmic modifications
Before trying to move parts of the system over to the FPGA, we can first improve some calculations, and redo a profiling to then choose which layer to put on the FPGA.

### Approximations of sigmoid
The original version of the sigmoid function is defined as such : 

```C
#define SIGMOID(x) (1.7159 * tanh(0.66666667 * x))
```

It uses two multiplications, and a call to the hyperbolic tangent as defined in the glibc.  
This implementation of the hyperbolic tangent is made to be as general and accurate as possible, and as such can be quite slow at times, especially because of calls to further glibc functions such as exp().  
This function being used in all layers, it makes sense to improve it.  
Therefore, we redid our own implementation of an approximative hyperbolic tangent, using further approximations of the exponential function : 

```C
float my_tanh(float x)
{
    // tanh(x) = (e^(2x) - 1) / (e^(2x) + 1), using a taylor approximation is not very good for the
    // negatives values because those polynoms tends to be very different to 0 for the very large
    // negative values, but it works well for the positive values because
    //
    //    (y-1) / (y+1) -------------------> 1
    //                       y --> +inf
    //
    // and
    //
    //    taylor(n,x)  ------------------> +inf
    //    exp(x)       ------------------> +inf
    //                       x --> +inf
    //
    // So I used the symetry tanh(-x) = -tanh(x), and a taylor approximation of exp(x) for the
    // positives x.
    //
    // This approach doesn't generalize well using Neon because armv7-l doesn't implement vdivq_f32
    bool sign = x > 0;

    x = sign ? 2 * x : -2 * x;
    float xx = x * x;

    // Approximation of e^x of degree 4
    float e_approx = 1 + x + 0.5 * xx + 0.1666666666666666 * x * xx + 0.0416666666666666 * xx * xx;

    float ret = (e_approx - 1) / (e_approx + 1);

    return sign ? ret : -ret;
}
```

### Replacing convolutions by matrix multiplications in layers 3 and 4
Layers 3 and 4 essentially perform a convolution product over large matrices, which is quite slow algorithmically (Time complexity of O(MNmn) with M, N the height and width of the input matrix, m, n the height and width of the convolution mask).  
To improve on this aspect, we modified the code to instead do matrix multiplication, which after initialization gives a worst time complexity of O(n^3), with n the size of the matrix.  
In our more specific case, for the layer3, the original algorithm performs nested loops of 50, 5, 5, 5, 5, and 5 iterations (or 31250 iterations) of multiply-accumulate operations (not counting index computation).  
The matrix product version on the other hand, performs two nested loops of 6, 5, 5, 5, 5 (3750 iterations each, 7500 total) of 1 assignation (matrix initialization) and a nested loop of 52, 152 (7904) iterations, each iteration doing 4 multiplications and one addition (5 operations).  
Overall, we went from doing 31250 x 6 x 2 = 375000 operations (additions and multiplications) to just 7904 x 5 = 39520 operations per call of the layer3.  

As for layer 4, the original algorithm performs nested loops of 100, 50, 5, 5 (125000) iterations of one addition and one multiplication, so 250000 operations per call.  
Our modified version performs a nested loop of 100, 1248 + 1250 (249800) iterations of one addition and one multiplication, so 499 600 operations per call (still not counting index calculation), so technically a worse situation.

However, if we now count index calculations, the original algorithm performs at the deepest level of the loop 13 operations (adds/mults) to calculate the indices of the right hand of the operation, which combined to our 2 "real" operations gives 125000 x 15 = 1875000 operations per call.  
Our version on the other hand only requires 10 more operations, bringing the total to 249800 x 12 = 2997600 operations per call, which is still worse than the previous implementation, but less so.

### Fully utilizing the CPU capabilities
As we are effectively using an ARM cpu with an embedded linux distribution, we are able to use its SIMD modules through ARM Neon Intrinsics, more specifically, 128-bits wide operations, or up to 4 floating point operations per cycle.  
This allows us to replace many operations of the layer 3 and 4 by neon calls, effectively dividing by 4 the number of total iterations, from 7904 to 1976 iterations for layer 3, and from 249800 to 62450 iterations for layer 4, effectively "solving" our issue of the layer 4 being larger, and improving further the layer 3.

## New profiling of the full CPU optimized version
Now that we improved the base algorithm, we need to redo a profiling pass to see which layer now takes most of the time, and then decide which one to move over to the FPGA part.  
Once again, to verify these values, we compile using -O3 flag, and activate neon intrinsics, which finally gives us the following results for 10000 iterations : 

| layer  | Original  | Optimized | ratio |
| :----- | :-------- | :-------- | :---- |
| Layer1 | 0.137579  | 0.065412  | 0.48  |
| Layer2 | 6.246568  | 3.878206  | 0.62  |
| Layer3 | 21.401608 | 11.179308 | 0.52  |
| Layer4 | 22.229725 | 11.214924 | 0.50  |
| Layer5 | 0.212412  | 0.175986  | 0.83  |
| global | 66.489793 | 27.029240 | 0.41  |

We can observe an almost halving of most computation times, and at least a 17% reduction in the layer 5.  
The fact that the overall time is better than the average improvement is due to the fact that enabling SIMD functionality allows memcpy to also be faster, and better use the bus, hence also reducing the load and store times.  
We still see that the heaviest layers are the layer 3 and 4, and are thus the ones that should be the best candidates for using the FPGA part.

## Utilizing the integrated FPGA for

TO BE COMPLETED

## Demonstration setup
As this project is about implementing a character recognition network specialized in recognizing numbers, we decided to setup a way to use the board in real time.

For this, we implemented a two-part system : 
1. A computer with a webcam, which will apply modifications on the input image (going to black and white, resizing to 29x29 pixels), show a real time view of the webcam, and send the pixel matrix over UDP;
2. The Board, which will run an infinite loop in which it will catch the UDP packets, store the pixel matric as input, perform the recognition, then print the result.

The webcam script is written in python and uses openCV, as shown below : 

```python
import cv2 as cv
from itertools import chain
import socket

def main():
    webcam = cv.VideoCapture(0)
    if not webcam.isOpened():
        print("Cannot open camera")
        return -1

    UDP_IP = "192.168.1.43"	#Board IP
    UDP_PORT = 17014

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    while True:
        ret, frame = webcam.read()

        if not ret:
            print("Can't receive frame")
            webcam.release()
            return -2

        gray_disp = cv.cvtColor(frame, cv.COLOR_RGB2GRAY)	# going grayscale
        ret, gray_disp = cv.threshold(gray_disp, 127, 255, cv.THRESH_BINARY_INV)	#going black and white (negative)

        gray_sent = cv.resize(gray_disp, (40, 30))	#downsizing while keeping proportions
        ret, gray_sent = cv.threshold(gray_sent, 127, 1, cv.THRESH_BINARY)	#casting the sent matrix to 0 and 1 instead of 0 and 255)

        gray_sent = gray_sent[0:29, 0:29]	#cropping to 29x29

        arr = gray_sent.data.tolist()	#casting image to 2D list

        arr_1d = list(chain.from_iterable(arr))	#casting to 1D array

        arr_bytes = bytes(arr_1d)	#casting to byte array

        cv.imshow("frame", gray_disp)	#display
		if cv.waitKey(1) == ord("q"):
            break

        sock.sendto(arr_bytes, (UDP_IP, UDP_PORT))	#seding the UDP packet

if __name__ == "__main__":
    main()
```

On the board side, another code is added as follows : 

```c
#include "receiver.h"
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>

int receive_img(float* image, unsigned int size) // assumes square image of size*size pixels
{
	char received[size*size];
	int listenfd, len;
	struct sockaddr_in servaddr, cliaddr;
	bzero(&servaddr, sizeof(servaddr));

	listenfd = socket(AF_INET, SOCK_DGRAM, 0);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;

	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	while(1)
	{
		len = sizeof(cliaddr);
		int n = recvfrom(listenfd, received, size, 0, (struct sockaddr*)&cliaddr, &len);	//buffer au format 8 bits
		
		printf("\n");
		for(int i = 0; i < size; i++)
		{
			for(int j = 0; j < size; j++)
			{
				image[i*size+j] = (float)received[i*size+j];	//cast en float
			}
		}
	}
	return 0;
}
```