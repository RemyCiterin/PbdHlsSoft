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

float fixed2float(int fixed) {
  return ((float)fixed) / 65536.0;
}

int float2fixed(float f) {
  return (int)(f * 65536.0);
}

// Load a 52 * 160 matrix into the fpga memory
void load_weights(XMk_dot_product *ex, float *M1) {
  int m1_buffer[160 * 52];

  for (int i=0; i < 160; i++)
    for (int j=0; j < 52; j++)
      m1_buffer[i * 52 + j] = float2fixed(M1[j * 160 + i]);

  assert(XMk_dot_product_Write_MatrixA0_Words(ex, 0, &m1_buffer[32*52*0], 32*52) == 32*52);
  assert(XMk_dot_product_Write_MatrixA1_Words(ex, 0, &m1_buffer[32*52*1], 32*52) == 32*52);
  assert(XMk_dot_product_Write_MatrixA2_Words(ex, 0, &m1_buffer[32*52*2], 32*52) == 32*52);
  assert(XMk_dot_product_Write_MatrixA3_Words(ex, 0, &m1_buffer[32*52*3], 32*52) == 32*52);
  assert(XMk_dot_product_Write_MatrixA4_Words(ex, 0, &m1_buffer[32*52*4], 32*52) == 32*52);
}

// M2 must be a 160 * 28 matrix
// Out must be a 52 * 28 matrix
void do_matmul(XMk_dot_product *ex, float *M2, float *Out) {
  int m2_buffer[160 * 28];
  int out_buffer[52 * 28];

  for (int i=0; i < 160; i++)
    for (int j=0; j < 28; j++)
      m2_buffer[i * 28 + j] = float2fixed(M2[i * 28 + j]);

  assert(XMk_dot_product_Write_MatrixB0_Words(ex, 0, &m2_buffer[32*28*0], 32*28) == 32*28);
  assert(XMk_dot_product_Write_MatrixB1_Words(ex, 0, &m2_buffer[32*28*1], 32*28) == 32*28);
  assert(XMk_dot_product_Write_MatrixB2_Words(ex, 0, &m2_buffer[32*28*2], 32*28) == 32*28);
  assert(XMk_dot_product_Write_MatrixB3_Words(ex, 0, &m2_buffer[32*28*3], 32*28) == 32*28);
  assert(XMk_dot_product_Write_MatrixB4_Words(ex, 0, &m2_buffer[32*28*4], 32*28) == 32*28);

  while (!XMk_dot_product_IsReady(ex)) {}
  XMk_dot_product_Start(ex);
  while (!XMk_dot_product_IsDone(ex)) {}

  assert(XMk_dot_product_Read_Output_r_Words(ex, 0, &out_buffer[0], 28*52) == 28*52);

  for (int i=0; i < 52; i++)
    for (int j=0; j < 28; j++)
      Out[i * 28 + j] = fixed2float(out_buffer[i * 28 + j]);
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

  cfg = mmap(NULL, 0x200000, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0x40000000);

  printf("mmap done\n");

  ex.Control_BaseAddress = (uint32_t)cfg;
  ex.IsReady = 1;

  float M1[52 * 160];
  float M2[160 * 28];
  float M3[52 * 28];

  for (int i=0; i < 52; i++)
    for (int j=0; j < 160; j++)
      M1[i * 160 + j] = (float)(rand() % 65536) / 65536;

  for (int i=0; i < 160; i++)
    for (int j=0; j < 28; j++)
      M2[i * 28 + j] = (float)(rand() % 65536) / 65536;


  load_weights(&ex, M1);

  float copy_time = 0;
  float ready_time = 0;
  float done_time = 0;

  printf("start processing!\n");

  int t1 = dtime();
  for (int iter=0; iter < 100; iter++) {
    do_matmul(&ex, M2, M3);
  }


  float t2 = dtime();

  printf("total time: %.4f\n", t2 - t1);
  printf("  ready time: %.4f\n", ready_time);
  printf("  done time: %.4f\n", done_time);
  printf("  copy time: %.4f\n", copy_time);

  float eps = 0.0001;
  int err_count = 0;
  for (int i=0; i < 52; i++) {
    for (int j=0; j < 28; j++) {
      float sum = 0.0;

      for (int k=0; k < 160; k++) {
        sum += M1[i*160+k] * M2[k*28+j];
      }

      if (i < 3 && j < 5) printf("%f %f\n", M3[i*28+j], sum);

      if (sum > M3[i*28+j] + eps || sum < M3[i*28+j] - eps) err_count++;
    }
  }

  printf("%d\n", err_count);

  return 0;
}
