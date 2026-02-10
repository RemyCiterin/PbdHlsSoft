// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XMK_DOT_PRODUCT_H
#define XMK_DOT_PRODUCT_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xmk_dot_product_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u32 Control_BaseAddress;
} XMk_dot_product_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XMk_dot_product;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XMk_dot_product_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XMk_dot_product_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XMk_dot_product_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XMk_dot_product_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XMk_dot_product_Initialize(XMk_dot_product *InstancePtr, u16 DeviceId);
XMk_dot_product_Config* XMk_dot_product_LookupConfig(u16 DeviceId);
int XMk_dot_product_CfgInitialize(XMk_dot_product *InstancePtr, XMk_dot_product_Config *ConfigPtr);
#else
int XMk_dot_product_Initialize(XMk_dot_product *InstancePtr, const char* InstanceName);
int XMk_dot_product_Release(XMk_dot_product *InstancePtr);
#endif

void XMk_dot_product_Start(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_IsDone(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_IsIdle(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_IsReady(XMk_dot_product *InstancePtr);
void XMk_dot_product_EnableAutoRestart(XMk_dot_product *InstancePtr);
void XMk_dot_product_DisableAutoRestart(XMk_dot_product *InstancePtr);

u32 XMk_dot_product_Get_MatrixB0_BaseAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixB0_HighAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixB0_TotalBytes(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixB0_BitWidth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixB0_Depth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Write_MatrixB0_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Read_MatrixB0_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Write_MatrixB0_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Read_MatrixB0_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Get_MatrixA0_BaseAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixA0_HighAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixA0_TotalBytes(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixA0_BitWidth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixA0_Depth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Write_MatrixA0_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Read_MatrixA0_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Write_MatrixA0_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Read_MatrixA0_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Get_MatrixA1_BaseAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixA1_HighAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixA1_TotalBytes(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixA1_BitWidth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixA1_Depth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Write_MatrixA1_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Read_MatrixA1_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Write_MatrixA1_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Read_MatrixA1_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Get_MatrixA2_BaseAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixA2_HighAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixA2_TotalBytes(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixA2_BitWidth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixA2_Depth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Write_MatrixA2_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Read_MatrixA2_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Write_MatrixA2_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Read_MatrixA2_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Get_MatrixA3_BaseAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixA3_HighAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixA3_TotalBytes(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixA3_BitWidth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixA3_Depth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Write_MatrixA3_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Read_MatrixA3_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Write_MatrixA3_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Read_MatrixA3_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Get_MatrixA4_BaseAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixA4_HighAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixA4_TotalBytes(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixA4_BitWidth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixA4_Depth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Write_MatrixA4_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Read_MatrixA4_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Write_MatrixA4_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Read_MatrixA4_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Get_MatrixB1_BaseAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixB1_HighAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixB1_TotalBytes(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixB1_BitWidth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixB1_Depth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Write_MatrixB1_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Read_MatrixB1_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Write_MatrixB1_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Read_MatrixB1_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Get_MatrixB2_BaseAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixB2_HighAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixB2_TotalBytes(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixB2_BitWidth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixB2_Depth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Write_MatrixB2_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Read_MatrixB2_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Write_MatrixB2_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Read_MatrixB2_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Get_MatrixB3_BaseAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixB3_HighAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixB3_TotalBytes(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixB3_BitWidth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixB3_Depth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Write_MatrixB3_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Read_MatrixB3_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Write_MatrixB3_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Read_MatrixB3_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Get_MatrixB4_BaseAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixB4_HighAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixB4_TotalBytes(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixB4_BitWidth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_MatrixB4_Depth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Write_MatrixB4_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Read_MatrixB4_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Write_MatrixB4_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Read_MatrixB4_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Get_Output_r_BaseAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Output_r_HighAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Output_r_TotalBytes(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Output_r_BitWidth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Output_r_Depth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Write_Output_r_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Read_Output_r_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Write_Output_r_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Read_Output_r_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);

void XMk_dot_product_InterruptGlobalEnable(XMk_dot_product *InstancePtr);
void XMk_dot_product_InterruptGlobalDisable(XMk_dot_product *InstancePtr);
void XMk_dot_product_InterruptEnable(XMk_dot_product *InstancePtr, u32 Mask);
void XMk_dot_product_InterruptDisable(XMk_dot_product *InstancePtr, u32 Mask);
void XMk_dot_product_InterruptClear(XMk_dot_product *InstancePtr, u32 Mask);
u32 XMk_dot_product_InterruptGetEnabled(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_InterruptGetStatus(XMk_dot_product *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
