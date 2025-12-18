
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

//void XMk_dot_product_Start(XMk_dot_product *InstancePtr);
//u32 XMk_dot_product_IsDone(XMk_dot_product *InstancePtr);
//u32 XMk_dot_product_IsIdle(XMk_dot_product *InstancePtr);
//u32 XMk_dot_product_IsReady(XMk_dot_product *InstancePtr);
//void XMk_dot_product_EnableAutoRestart(XMk_dot_product *InstancePtr);
//void XMk_dot_product_DisableAutoRestart(XMk_dot_product *InstancePtr);
//
//u32 XMk_dot_product_Write_OffsetA_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
//u32 XMk_dot_product_Read_OffsetA_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
//u32 XMk_dot_product_Write_OffsetB_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
//u32 XMk_dot_product_Read_OffsetB_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
//u32 XMk_dot_product_Write_Size_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
//u32 XMk_dot_product_Read_Size_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
//u32 XMk_dot_product_Write_Result_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
//u32 XMk_dot_product_Read_Result_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
//u32 XMk_dot_product_Write_Scratchpad_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
//u32 XMk_dot_product_Read_Scratchpad_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);


static inline void Write_Vector(XMk_dot_product* cfg, int offset, int* vector, int size) {
  XMk_dot_product_Write_Scratchpad_Words(cfg, offset, (word_type*)(vector), size);
}

static inline void Set_Size(XMk_dot_product* cfg, int processor, int size) {
  XMk_dot_product_Write_Size_Words(cfg, processor, (word_type*)(&size), 1);
}

static inline void Set_OffsetA(XMk_dot_product* cfg, int processor, int offset) {
  XMk_dot_product_Write_OffsetA_Words(cfg, processor, (word_type*)(&offset), 1);
}

static inline void Set_OffsetB(XMk_dot_product* cfg, int processor, int offset) {
  XMk_dot_product_Write_OffsetB_Words(cfg, processor, (word_type*)(&offset), 1);
}

static inline int Get_Result(XMk_dot_product* cfg, int processor) {
  int ret;
  XMk_dot_product_Read_Result_Words(cfg, processor, (word_type*)(&ret), 1);
  return ret;
}

#define COPIES 8
#define SIZE 1250

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

  for (int i=0; i < COPIES; i++) Set_Size(&ex, i, 0);

  int A[SIZE];

  float t1 = dtime();
  for (int i=0; i < SIZE; i++) A[i] = 1 * 6553;
  Write_Vector(&ex, 0, &A[0], SIZE);

  int ret;

  float copy_time = 0;
  float ready_time = 0;
  float done_time = 0;

  int B[COPIES][SIZE];
  for (int j=0; j < 100; j++) {
  for (int iter=0; iter < COPIES; iter++) {
    for (int i=0; i < SIZE; i++) B[iter][i] = 65536 * (iter * SIZE+i);

    copy_time -= dtime();
    Write_Vector(&ex, (1+iter) * SIZE, &B[iter][0], SIZE);
    copy_time += dtime();
  }
  }

  printf("start processing!\n");
  for (int iter=0; iter < 1300; iter++) { // 250000
    ready_time -= dtime();
    while (!XMk_dot_product_IsReady(&ex)) {}
    ready_time += dtime();

    for (int x=0; x < COPIES; x++) {
      Set_OffsetA(&ex, x, 0);
      Set_OffsetB(&ex, x, SIZE * (1+x));
      Set_Size(&ex, x, SIZE);
    }

    XMk_dot_product_Start(&ex);

    done_time -= dtime();
    while (!XMk_dot_product_IsDone(&ex)) {}
    done_time += dtime();

    ret = Get_Result(&ex, 0);
    for (int x=1; x < 8; x++) {
      ret += Get_Result(&ex, x);
    }

    //printf("result: %f\n", ret);
  }

  printf("result: %f\n", (float)(ret) / 65536.0);

  float t2 = dtime();

  //float t3 = dtime();
  //float result;
  //for (int iter=0; iter < 1300; iter++) {
  //  result = 0;
  //  for (int i=0; i < COPIES; i++) {
  //    result += baseline_dot_product(&A[0], &B[i][0], SIZE);
  //  }
  //}
  //float t4 = dtime();

  printf("total time: %.4f\n", t2 - t1);
  printf("  copy time: %.4f\n", copy_time);
  printf("  ready time: %.4f\n", ready_time);
  printf("  done time: %.4f\n", done_time);

  //printf("baseline time: %.4f\n", t4 - t3);
  //printf("  result: %.4f\n", result);

  return 0;
}
