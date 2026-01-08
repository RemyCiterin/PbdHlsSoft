# PBD-HLS Project report

- [PBD-HLS Project report](#pbd-hls-project-report)

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

Using those timers, simply running the program gives us the time spent by each function call, including both user space and kernel space times.

temps init total : 0.488720
temps Layer1 total : 0.000000
temps Layer2 total : 0.712261
temps Layer3 total : 4.994266
temps Layer4 total : 3.110743
temps Layer5 total : 0.019994