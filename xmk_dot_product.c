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

u32 XMk_dot_product_Get_MatrixB0_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB0_BASE);
}

u32 XMk_dot_product_Get_MatrixB0_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB0_HIGH);
}

u32 XMk_dot_product_Get_MatrixB0_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB0_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB0_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixB0_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB0;
}

u32 XMk_dot_product_Get_MatrixB0_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB0;
}

u32 XMk_dot_product_Write_MatrixB0_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB0_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB0_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB0_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB0_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB0_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB0_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB0_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixB0_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB0_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB0_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB0_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB0_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB0_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB0_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB0_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_MatrixA0_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA0_BASE);
}

u32 XMk_dot_product_Get_MatrixA0_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA0_HIGH);
}

u32 XMk_dot_product_Get_MatrixA0_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA0_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA0_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixA0_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA0;
}

u32 XMk_dot_product_Get_MatrixA0_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA0;
}

u32 XMk_dot_product_Write_MatrixA0_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA0_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA0_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA0_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA0_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA0_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA0_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA0_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixA0_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA0_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA0_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA0_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA0_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA0_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA0_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA0_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_MatrixA1_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA1_BASE);
}

u32 XMk_dot_product_Get_MatrixA1_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA1_HIGH);
}

u32 XMk_dot_product_Get_MatrixA1_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA1_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA1_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixA1_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA1;
}

u32 XMk_dot_product_Get_MatrixA1_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA1;
}

u32 XMk_dot_product_Write_MatrixA1_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA1_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA1_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA1_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA1_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA1_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA1_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA1_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixA1_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA1_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA1_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA1_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA1_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA1_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA1_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA1_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_MatrixA2_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA2_BASE);
}

u32 XMk_dot_product_Get_MatrixA2_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA2_HIGH);
}

u32 XMk_dot_product_Get_MatrixA2_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA2_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA2_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixA2_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA2;
}

u32 XMk_dot_product_Get_MatrixA2_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA2;
}

u32 XMk_dot_product_Write_MatrixA2_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA2_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA2_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA2_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA2_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA2_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA2_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA2_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixA2_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA2_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA2_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA2_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA2_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA2_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA2_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA2_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_MatrixA3_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA3_BASE);
}

u32 XMk_dot_product_Get_MatrixA3_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA3_HIGH);
}

u32 XMk_dot_product_Get_MatrixA3_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA3_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA3_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixA3_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA3;
}

u32 XMk_dot_product_Get_MatrixA3_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA3;
}

u32 XMk_dot_product_Write_MatrixA3_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA3_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA3_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA3_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA3_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA3_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA3_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA3_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixA3_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA3_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA3_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA3_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA3_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA3_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA3_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA3_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_MatrixA4_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA4_BASE);
}

u32 XMk_dot_product_Get_MatrixA4_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA4_HIGH);
}

u32 XMk_dot_product_Get_MatrixA4_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA4_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA4_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixA4_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA4;
}

u32 XMk_dot_product_Get_MatrixA4_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA4;
}

u32 XMk_dot_product_Write_MatrixA4_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA4_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA4_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA4_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA4_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA4_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA4_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA4_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixA4_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA4_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA4_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA4_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA4_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA4_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA4_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA4_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_MatrixA5_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA5_BASE);
}

u32 XMk_dot_product_Get_MatrixA5_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA5_HIGH);
}

u32 XMk_dot_product_Get_MatrixA5_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA5_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA5_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixA5_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA5;
}

u32 XMk_dot_product_Get_MatrixA5_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA5;
}

u32 XMk_dot_product_Write_MatrixA5_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA5_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA5_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA5_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA5_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA5_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA5_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA5_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixA5_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA5_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA5_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA5_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA5_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA5_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA5_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA5_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_MatrixA6_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA6_BASE);
}

u32 XMk_dot_product_Get_MatrixA6_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA6_HIGH);
}

u32 XMk_dot_product_Get_MatrixA6_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA6_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA6_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixA6_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA6;
}

u32 XMk_dot_product_Get_MatrixA6_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA6;
}

u32 XMk_dot_product_Write_MatrixA6_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA6_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA6_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA6_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA6_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA6_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA6_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA6_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixA6_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA6_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA6_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA6_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA6_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA6_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA6_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA6_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_MatrixA7_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA7_BASE);
}

u32 XMk_dot_product_Get_MatrixA7_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA7_HIGH);
}

u32 XMk_dot_product_Get_MatrixA7_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA7_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA7_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixA7_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA7;
}

u32 XMk_dot_product_Get_MatrixA7_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA7;
}

u32 XMk_dot_product_Write_MatrixA7_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA7_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA7_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA7_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA7_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA7_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA7_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA7_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixA7_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA7_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA7_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA7_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA7_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA7_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA7_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA7_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_MatrixA8_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA8_BASE);
}

u32 XMk_dot_product_Get_MatrixA8_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA8_HIGH);
}

u32 XMk_dot_product_Get_MatrixA8_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA8_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA8_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixA8_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA8;
}

u32 XMk_dot_product_Get_MatrixA8_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA8;
}

u32 XMk_dot_product_Write_MatrixA8_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA8_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA8_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA8_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA8_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA8_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA8_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA8_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixA8_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA8_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA8_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA8_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA8_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA8_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA8_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA8_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_MatrixA9_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA9_BASE);
}

u32 XMk_dot_product_Get_MatrixA9_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA9_HIGH);
}

u32 XMk_dot_product_Get_MatrixA9_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA9_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA9_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixA9_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA9;
}

u32 XMk_dot_product_Get_MatrixA9_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA9;
}

u32 XMk_dot_product_Write_MatrixA9_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA9_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA9_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA9_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA9_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA9_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA9_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA9_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixA9_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA9_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA9_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA9_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA9_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA9_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA9_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA9_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_MatrixB1_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB1_BASE);
}

u32 XMk_dot_product_Get_MatrixB1_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB1_HIGH);
}

u32 XMk_dot_product_Get_MatrixB1_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB1_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB1_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixB1_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB1;
}

u32 XMk_dot_product_Get_MatrixB1_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB1;
}

u32 XMk_dot_product_Write_MatrixB1_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB1_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB1_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB1_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB1_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB1_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB1_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB1_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixB1_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB1_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB1_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB1_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB1_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB1_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB1_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB1_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_MatrixB2_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB2_BASE);
}

u32 XMk_dot_product_Get_MatrixB2_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB2_HIGH);
}

u32 XMk_dot_product_Get_MatrixB2_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB2_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB2_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixB2_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB2;
}

u32 XMk_dot_product_Get_MatrixB2_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB2;
}

u32 XMk_dot_product_Write_MatrixB2_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB2_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB2_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB2_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB2_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB2_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB2_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB2_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixB2_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB2_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB2_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB2_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB2_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB2_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB2_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB2_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_MatrixB3_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB3_BASE);
}

u32 XMk_dot_product_Get_MatrixB3_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB3_HIGH);
}

u32 XMk_dot_product_Get_MatrixB3_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB3_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB3_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixB3_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB3;
}

u32 XMk_dot_product_Get_MatrixB3_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB3;
}

u32 XMk_dot_product_Write_MatrixB3_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB3_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB3_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB3_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB3_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB3_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB3_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB3_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixB3_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB3_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB3_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB3_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB3_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB3_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB3_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB3_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_MatrixB4_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB4_BASE);
}

u32 XMk_dot_product_Get_MatrixB4_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB4_HIGH);
}

u32 XMk_dot_product_Get_MatrixB4_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB4_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB4_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixB4_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB4;
}

u32 XMk_dot_product_Get_MatrixB4_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB4;
}

u32 XMk_dot_product_Write_MatrixB4_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB4_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB4_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB4_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB4_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB4_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB4_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB4_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixB4_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB4_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB4_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB4_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB4_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB4_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB4_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB4_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_MatrixB5_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB5_BASE);
}

u32 XMk_dot_product_Get_MatrixB5_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB5_HIGH);
}

u32 XMk_dot_product_Get_MatrixB5_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB5_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB5_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixB5_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB5;
}

u32 XMk_dot_product_Get_MatrixB5_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB5;
}

u32 XMk_dot_product_Write_MatrixB5_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB5_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB5_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB5_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB5_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB5_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB5_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB5_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixB5_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB5_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB5_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB5_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB5_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB5_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB5_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB5_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_MatrixB6_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB6_BASE);
}

u32 XMk_dot_product_Get_MatrixB6_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB6_HIGH);
}

u32 XMk_dot_product_Get_MatrixB6_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB6_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB6_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixB6_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB6;
}

u32 XMk_dot_product_Get_MatrixB6_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB6;
}

u32 XMk_dot_product_Write_MatrixB6_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB6_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB6_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB6_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB6_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB6_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB6_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB6_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixB6_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB6_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB6_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB6_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB6_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB6_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB6_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB6_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_MatrixB7_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB7_BASE);
}

u32 XMk_dot_product_Get_MatrixB7_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB7_HIGH);
}

u32 XMk_dot_product_Get_MatrixB7_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB7_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB7_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixB7_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB7;
}

u32 XMk_dot_product_Get_MatrixB7_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB7;
}

u32 XMk_dot_product_Write_MatrixB7_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB7_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB7_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB7_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB7_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB7_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB7_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB7_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixB7_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB7_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB7_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB7_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB7_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB7_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB7_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB7_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_MatrixB8_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB8_BASE);
}

u32 XMk_dot_product_Get_MatrixB8_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB8_HIGH);
}

u32 XMk_dot_product_Get_MatrixB8_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB8_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB8_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixB8_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB8;
}

u32 XMk_dot_product_Get_MatrixB8_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB8;
}

u32 XMk_dot_product_Write_MatrixB8_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB8_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB8_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB8_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB8_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB8_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB8_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB8_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixB8_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB8_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB8_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB8_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB8_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB8_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB8_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB8_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_MatrixB9_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB9_BASE);
}

u32 XMk_dot_product_Get_MatrixB9_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB9_HIGH);
}

u32 XMk_dot_product_Get_MatrixB9_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB9_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB9_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixB9_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB9;
}

u32 XMk_dot_product_Get_MatrixB9_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB9;
}

u32 XMk_dot_product_Write_MatrixB9_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB9_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB9_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB9_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB9_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB9_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB9_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB9_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixB9_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB9_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB9_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB9_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB9_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB9_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB9_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB9_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_Output_r_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_BASE);
}

u32 XMk_dot_product_Get_Output_r_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_HIGH);
}

u32 XMk_dot_product_Get_Output_r_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_BASE + 1);
}

u32 XMk_dot_product_Get_Output_r_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_OUTPUT_R;
}

u32 XMk_dot_product_Get_Output_r_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_OUTPUT_R;
}

u32 XMk_dot_product_Write_Output_r_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_Output_r_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_Output_r_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_Output_r_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_BASE + offset + i);
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

