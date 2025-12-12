
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include "xmk_dot_product.h"

// void XMk_dot_product_Set_OffsetA(XMk_dot_product *InstancePtr, u32 Data);
// u32 XMk_dot_product_Get_OffsetA(XMk_dot_product *InstancePtr);
// void XMk_dot_product_Set_OffsetB(XMk_dot_product *InstancePtr, u32 Data);
// u32 XMk_dot_product_Get_OffsetB(XMk_dot_product *InstancePtr);
// u32 XMk_dot_product_Get_Result(XMk_dot_product *InstancePtr);
// u32 XMk_dot_product_Get_Result_vld(XMk_dot_product *InstancePtr);
// void XMk_dot_product_Set_Idle_i(XMk_dot_product *InstancePtr, u32 Data);
// u32 XMk_dot_product_Get_Idle_i(XMk_dot_product *InstancePtr);
// u32 XMk_dot_product_Get_Idle_o(XMk_dot_product *InstancePtr);
// u32 XMk_dot_product_Get_Idle_o_vld(XMk_dot_product *InstancePtr);
// u32 XMk_dot_product_Get_Buff_BaseAddress(XMk_dot_product *InstancePtr);
// u32 XMk_dot_product_Get_Buff_HighAddress(XMk_dot_product *InstancePtr);
// u32 XMk_dot_product_Get_Buff_TotalBytes(XMk_dot_product *InstancePtr);
// u32 XMk_dot_product_Get_Buff_BitWidth(XMk_dot_product *InstancePtr);
// u32 XMk_dot_product_Get_Buff_Depth(XMk_dot_product *InstancePtr);
// u32 XMk_dot_product_Write_Buff_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
// u32 XMk_dot_product_Read_Buff_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
// u32 XMk_dot_product_Write_Buff_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
// u32 XMk_dot_product_Read_Buff_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);


int main() {
  XMk_dot_product ex;

  volatile void* cfg;
  int fd;

  printf("open /dev/mem\n");
  if((fd = open("/dev/mem", O_RDWR)) < 0) {
    perror("open");
    return EXIT_FAILURE;
  }

  cfg = mmap(NULL, sysconf(_SC_PAGESIZE * 4), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0x40000000);

  printf("mmap done\n");

  ex.Control_BaseAddress = cfg;
  ex.IsReady = 1;

  float A[50];
  for (int i=0; i < 50; i++) A[i] = i;

  float B[50];
  for (int i=0; i < 50; i++) B[i] = 1;

  printf("wait for idle_o to be set to 1\n");
  while (XMk_dot_product_Get_Idle_o(&ex) == 0) {}
  printf("set idle_i to 1\n");
  XMk_dot_product_Set_Idle_i(&ex, 1);

  printf("load data\n");
  XMk_dot_product_Set_OffsetA(&ex, 0);
  XMk_dot_product_Set_OffsetB(&ex, 50);
  XMk_dot_product_Write_Buff_Words(&ex, 0, (word_type*)(&A[0]), 50);
  XMk_dot_product_Write_Buff_Words(&ex, 50, (word_type*)(&B[0]), 50);

  printf("set idle_i to 1\n");
  XMk_dot_product_Set_Idle_i(&ex, 0);

  printf("wait for Idle_o to be valid\n");
  while (!XMk_dot_product_Get_Idle_o_vld(&ex)) {}
  printf("wait for idle_o to be 1\n");
  while (XMk_dot_product_Get_Idle_o(&ex) == 0) {
    printf("Wait\n");
  }

  printf("wait for result to be valid\n");
  while (!XMk_dot_product_Get_Result_vld(&ex)) {}

  for (int i=0; i < 1000; i++) {
    int c = XMk_dot_product_Get_Result(&ex);
    float C = *(float*)(&c);
    printf("Result: %f\n", C);
  }

  return 0;
}
