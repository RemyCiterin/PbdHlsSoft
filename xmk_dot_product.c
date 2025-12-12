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

void XMk_dot_product_Set_OffsetA(XMk_dot_product *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMk_dot_product_WriteReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETA_DATA, Data);
}

u32 XMk_dot_product_Get_OffsetA(XMk_dot_product *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMk_dot_product_ReadReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETA_DATA);
    return Data;
}

void XMk_dot_product_Set_OffsetB(XMk_dot_product *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMk_dot_product_WriteReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETB_DATA, Data);
}

u32 XMk_dot_product_Get_OffsetB(XMk_dot_product *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMk_dot_product_ReadReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETB_DATA);
    return Data;
}

u32 XMk_dot_product_Get_Result(XMk_dot_product *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMk_dot_product_ReadReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_DATA);
    return Data;
}

u32 XMk_dot_product_Get_Result_vld(XMk_dot_product *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMk_dot_product_ReadReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_CTRL);
    return Data & 0x1;
}

void XMk_dot_product_Set_Idle_i(XMk_dot_product *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMk_dot_product_WriteReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_IDLE_I_DATA, Data);
}

u32 XMk_dot_product_Get_Idle_i(XMk_dot_product *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMk_dot_product_ReadReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_IDLE_I_DATA);
    return Data;
}

u32 XMk_dot_product_Get_Idle_o(XMk_dot_product *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMk_dot_product_ReadReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_IDLE_O_DATA);
    return Data;
}

u32 XMk_dot_product_Get_Idle_o_vld(XMk_dot_product *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMk_dot_product_ReadReg(InstancePtr->Control_BaseAddress, XMK_DOT_PRODUCT_CONTROL_ADDR_IDLE_O_CTRL);
    return Data & 0x1;
}

u32 XMk_dot_product_Get_Buff_BaseAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_BUFF_BASE);
}

u32 XMk_dot_product_Get_Buff_HighAddress(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_BUFF_HIGH);
}

u32 XMk_dot_product_Get_Buff_TotalBytes(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XMK_DOT_PRODUCT_CONTROL_ADDR_BUFF_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_BUFF_BASE + 1);
}

u32 XMk_dot_product_Get_Buff_BitWidth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_WIDTH_BUFF;
}

u32 XMk_dot_product_Get_Buff_Depth(XMk_dot_product *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMK_DOT_PRODUCT_CONTROL_DEPTH_BUFF;
}

u32 XMk_dot_product_Write_Buff_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_BUFF_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_BUFF_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_BUFF_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_Buff_Words(XMk_dot_product *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XMK_DOT_PRODUCT_CONTROL_ADDR_BUFF_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_BUFF_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_BUFF_BASE + (offset + i)*4);
    }
    return length;
}

u32 XMk_dot_product_Write_Buff_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_BUFF_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_BUFF_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_BUFF_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XMk_dot_product_Read_Buff_Bytes(XMk_dot_product *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XMK_DOT_PRODUCT_CONTROL_ADDR_BUFF_HIGH - XMK_DOT_PRODUCT_CONTROL_ADDR_BUFF_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XMK_DOT_PRODUCT_CONTROL_ADDR_BUFF_BASE + offset + i);
    }
    return length;
}

