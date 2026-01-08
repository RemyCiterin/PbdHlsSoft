// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xmk_dot_product.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XMk_dot_product_CfgInitialize(XMk_dot_product *InstancePtr, XMk_dot_product_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XMk_dot_product_Start(XMk_dot_product *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMk_dot_product_ReadReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_AP_CTRL) & 0x80;
    XMk_dot_product_WriteReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XMk_dot_product_IsDone(XMk_dot_product *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMk_dot_product_ReadReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XMk_dot_product_IsIdle(XMk_dot_product *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMk_dot_product_ReadReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XMk_dot_product_IsReady(XMk_dot_product *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMk_dot_product_ReadReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XMk_dot_product_EnableAutoRestart(XMk_dot_product *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMk_dot_product_WriteReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XMk_dot_product_DisableAutoRestart(XMk_dot_product *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMk_dot_product_WriteReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_AP_CTRL, 0);
}

u32 XMk_dot_product_Get_OffsetA_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETA_BASE);
}

u32 XMk_dot_product_Get_OffsetA_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETA_HIGH);
}

u32 XMk_dot_product_Get_OffsetA_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETA_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETA_BASE + 1);
}

u32 XMk_dot_product_Get_OffsetA_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_OFFSETA;
}

u32 XMk_dot_product_Get_OffsetA_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_OFFSETA;
}

u32 XMk_dot_product_Write_OffsetA_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETA_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETA_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETA_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_OffsetA_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETA_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETA_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETA_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_OffsetA_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETA_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETA_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETA_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_OffsetA_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETA_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETA_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETA_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_OffsetB_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETB_BASE);
}

u32 XMk_dot_product_Get_OffsetB_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETB_HIGH);
}

u32 XMk_dot_product_Get_OffsetB_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETB_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETB_BASE + 1);
}

u32 XMk_dot_product_Get_OffsetB_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_OFFSETB;
}

u32 XMk_dot_product_Get_OffsetB_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_OFFSETB;
}

u32 XMk_dot_product_Write_OffsetB_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETB_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETB_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETB_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_OffsetB_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETB_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETB_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETB_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_OffsetB_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETB_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETB_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETB_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_OffsetB_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETB_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETB_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETB_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_Size_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SIZE_BASE);
}

u32 XMk_dot_product_Get_Size_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SIZE_HIGH);
}

u32 XMk_dot_product_Get_Size_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_SIZE_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SIZE_BASE + 1);
}

u32 XMk_dot_product_Get_Size_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_SIZE;
}

u32 XMk_dot_product_Get_Size_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_SIZE;
}

u32 XMk_dot_product_Write_Size_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_SIZE_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SIZE_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SIZE_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_Size_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_SIZE_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SIZE_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SIZE_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_Size_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_SIZE_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SIZE_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SIZE_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_Size_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_SIZE_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SIZE_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SIZE_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_Result_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_BASE);
}

u32 XMk_dot_product_Get_Result_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_HIGH);
}

u32 XMk_dot_product_Get_Result_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_BASE + 1);
}

u32 XMk_dot_product_Get_Result_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_RESULT;
}

u32 XMk_dot_product_Get_Result_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_RESULT;
}

u32 XMk_dot_product_Write_Result_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_Result_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_Result_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_Result_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_Scratchpad_0_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_0_BASE);
}

u32 XMk_dot_product_Get_Scratchpad_0_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_0_HIGH);
}

u32 XMk_dot_product_Get_Scratchpad_0_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_0_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_0_BASE + 1);
}

u32 XMk_dot_product_Get_Scratchpad_0_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_SCRATCHPAD_0;
}

u32 XMk_dot_product_Get_Scratchpad_0_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_SCRATCHPAD_0;
}

u32 XMk_dot_product_Write_Scratchpad_0_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_0_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_0_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_0_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_Scratchpad_0_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_0_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_0_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_0_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_Scratchpad_0_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_0_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_0_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_0_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_Scratchpad_0_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_0_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_0_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_0_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_Scratchpad_1_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_1_BASE);
}

u32 XMk_dot_product_Get_Scratchpad_1_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_1_HIGH);
}

u32 XMk_dot_product_Get_Scratchpad_1_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_1_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_1_BASE + 1);
}

u32 XMk_dot_product_Get_Scratchpad_1_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_SCRATCHPAD_1;
}

u32 XMk_dot_product_Get_Scratchpad_1_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_SCRATCHPAD_1;
}

u32 XMk_dot_product_Write_Scratchpad_1_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_1_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_1_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_1_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_Scratchpad_1_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_1_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_1_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_1_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_Scratchpad_1_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_1_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_1_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_1_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_Scratchpad_1_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_1_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_1_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_1_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_Scratchpad_2_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_2_BASE);
}

u32 XMk_dot_product_Get_Scratchpad_2_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_2_HIGH);
}

u32 XMk_dot_product_Get_Scratchpad_2_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_2_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_2_BASE + 1);
}

u32 XMk_dot_product_Get_Scratchpad_2_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_SCRATCHPAD_2;
}

u32 XMk_dot_product_Get_Scratchpad_2_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_SCRATCHPAD_2;
}

u32 XMk_dot_product_Write_Scratchpad_2_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_2_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_2_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_2_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_Scratchpad_2_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_2_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_2_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_2_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_Scratchpad_2_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_2_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_2_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_2_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_Scratchpad_2_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_2_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_2_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_2_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_Scratchpad_3_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_3_BASE);
}

u32 XMk_dot_product_Get_Scratchpad_3_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_3_HIGH);
}

u32 XMk_dot_product_Get_Scratchpad_3_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_3_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_3_BASE + 1);
}

u32 XMk_dot_product_Get_Scratchpad_3_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_SCRATCHPAD_3;
}

u32 XMk_dot_product_Get_Scratchpad_3_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_SCRATCHPAD_3;
}

u32 XMk_dot_product_Write_Scratchpad_3_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_3_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_3_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_3_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_Scratchpad_3_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_3_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_3_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_3_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_Scratchpad_3_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_3_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_3_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_3_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_Scratchpad_3_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_3_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_3_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_3_BASE + offset + i);
    }
    return length;
}

void XMk_dot_product_InterruptGlobalEnable(XMk_dot_product *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMk_dot_product_WriteReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_GIE, 1);
}

void XMk_dot_product_InterruptGlobalDisable(XMk_dot_product *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMk_dot_product_WriteReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_GIE, 0);
}

void XMk_dot_product_InterruptEnable(XMk_dot_product *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMk_dot_product_ReadReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_IER);
    XMk_dot_product_WriteReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_IER, Register | Mask);
}

void XMk_dot_product_InterruptDisable(XMk_dot_product *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMk_dot_product_ReadReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_IER);
    XMk_dot_product_WriteReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_IER, Register & (~Mask));
}

void XMk_dot_product_InterruptClear(XMk_dot_product *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMk_dot_product_WriteReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_ISR, Mask);
}

u32 XMk_dot_product_InterruptGetEnabled(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMk_dot_product_ReadReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_IER);
}

u32 XMk_dot_product_InterruptGetStatus(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMk_dot_product_ReadReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_ISR);
}

