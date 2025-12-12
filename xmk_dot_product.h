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


void XMk_dot_product_Set_OffsetA(XMk_dot_product *InstancePtr, u32 Data);
u32 XMk_dot_product_Get_OffsetA(XMk_dot_product *InstancePtr);
void XMk_dot_product_Set_OffsetB(XMk_dot_product *InstancePtr, u32 Data);
u32 XMk_dot_product_Get_OffsetB(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Result(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Result_vld(XMk_dot_product *InstancePtr);
void XMk_dot_product_Set_Idle_i(XMk_dot_product *InstancePtr, u32 Data);
u32 XMk_dot_product_Get_Idle_i(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Idle_o(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Idle_o_vld(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Buff_BaseAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Buff_HighAddress(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Buff_TotalBytes(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Buff_BitWidth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Get_Buff_Depth(XMk_dot_product *InstancePtr);
u32 XMk_dot_product_Write_Buff_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Read_Buff_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length);
u32 XMk_dot_product_Write_Buff_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);
u32 XMk_dot_product_Read_Buff_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length);

#ifdef __cplusplus
}
#endif

#endif
