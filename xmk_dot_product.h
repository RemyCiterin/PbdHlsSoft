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

u32 XMk_dot_product_Get_OffsetA_BaseAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_OffsetA_HighAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_OffsetA_TotalBytes(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_OffsetA_BitWidth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_OffsetA_Depth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Write_OffsetA_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Read_OffsetA_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Write_OffsetA_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Read_OffsetA_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Get_OffsetB_BaseAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_OffsetB_HighAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_OffsetB_TotalBytes(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_OffsetB_BitWidth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_OffsetB_Depth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Write_OffsetB_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Read_OffsetB_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Write_OffsetB_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Read_OffsetB_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Get_Size_BaseAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Size_HighAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Size_TotalBytes(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Size_BitWidth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Size_Depth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Write_Size_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Read_Size_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Write_Size_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Read_Size_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Get_Result_BaseAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Result_HighAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Result_TotalBytes(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Result_BitWidth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Result_Depth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Write_Result_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Read_Result_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Write_Result_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Read_Result_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Get_Scratchpad_BaseAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Scratchpad_HighAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Scratchpad_TotalBytes(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Scratchpad_BitWidth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Scratchpad_Depth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Write_Scratchpad_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Read_Scratchpad_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Write_Scratchpad_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Read_Scratchpad_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);

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
