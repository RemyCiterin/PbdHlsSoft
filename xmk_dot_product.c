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

u32 XMk_dot_product_Get_MatrixA_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA_BASE);
}

u32 XMk_dot_product_Get_MatrixA_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA_HIGH);
}

u32 XMk_dot_product_Get_MatrixA_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixA_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA;
}

u32 XMk_dot_product_Get_MatrixA_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA;
}

u32 XMk_dot_product_Write_MatrixA_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixA_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixA_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA_BASE + offset + i);
    }
    return length;
}

u32 XMk_dot_product_Get_MatrixB_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB_BASE);
}

u32 XMk_dot_product_Get_MatrixB_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB_HIGH);
}

u32 XMk_dot_product_Get_MatrixB_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB_BASE + 1);
}

u32 XMk_dot_product_Get_MatrixB_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB;
}

u32 XMk_dot_product_Get_MatrixB_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB;
}

u32 XMk_dot_product_Write_MatrixB_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_MatrixB_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_MatrixB_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB_BASE + offset + i);
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

