#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <float.h>
#include <math.h>

#include "timers_b.h"

#include "xmk_dot_product.h"

// void XMk_dot_product_Start(XMk_dot_product *InstancePtr);
// u32 XMk_dot_product_IsDone(XMk_dot_product *InstancePtr);
// u32 XMk_dot_product_IsIdle(XMk_dot_product *InstancePtr);
// u32 XMk_dot_product_IsReady(XMk_dot_product *InstancePtr);
//
// u32 XMk_dot_product_Read_Output_r_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
// u32 XMk_dot_product_Write_MatrixA_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
// u32 XMk_dot_product_Write_MatrixB_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);

float fixed2float(int fixed) {
  return ((float)fixed) / 65536.0;
}

int float2fixed(float f) {
  return (int)(f * 65536.0);
}

extern float baseline_dot_product(float *x, float *y, int size);

int main() {
  XMk_dot_product ex;

  volatile void* cfg;
  int fd;

  printf("open /dev/mem\n");
  if((fd = open("/dev/mem", O_RDWR)) < 0) {
    perror("open");
    return EXIT_FAILURE;
  }

  cfg = mmap(NULL, 0x100000, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0x40000000);

  printf("mmap done\n");

  ex.Control_BaseAddress = (uint32_t)cfg;
  ex.IsReady = 1;

  int M1[52 * 152];
  int M2[152 * 28];
  int M3[52 * 28];

  for (int i=0; i < 52; i++)
    for (int j=0; j < 152; j++)
      M1[i * 152 + j] = rand() % 65536;

  for (int i=0; i < 152; i++)
    for (int j=0; j < 28; j++)
      M2[i * 28 + j] = rand() % 65536;

  XMk_dot_product_Write_MatrixA_Words(&ex, 0, M1, 52 * 152);

  float copy_time = 0;
  float ready_time = 0;
  float done_time = 0;

  printf("start processing!\n");

  int t1 = dtime();
  for (int iter=0; iter < 100; iter++) { // 250000
    copy_time -= dtime();
    XMk_dot_product_Write_MatrixB_Words(&ex, 0, M2, 28 * 152);
    copy_time += dtime();

    ready_time -= dtime();
    while (!XMk_dot_product_IsReady(&ex)) {}
    ready_time += dtime();

    XMk_dot_product_Start(&ex);

    done_time -= dtime();
    while (!XMk_dot_product_IsDone(&ex)) {}
    done_time += dtime();

    copy_time -= dtime();
    XMk_dot_product_Read_Output_r_Words(&ex, 0, M3, 28*52);
    copy_time += dtime();
  }


  float t2 = dtime();

  printf("total time: %.4f\n", t2 - t1);
  printf("  ready time: %.4f\n", ready_time);
  printf("  done time: %.4f\n", done_time);
  printf("  copy time: %.4f\n", copy_time);

  int num_error = 0;
  for (int i=0; i < 52; i++) {
    for (int j=0; j < 28; j++) {
      float sum = 0;

      for (int k=0; k < 152; k++) {
        sum += fixed2float(M1[i*152+k]) * fixed2float(M2[k*28+j]);
      }

      //printf("%f %f\n", fixed2float(M3[i*28+j]), sum);
    }
  }

  //printf("num errors: %d\n", num_error);

  return 0;
}
