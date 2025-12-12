// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x0000 : reserved
// 0x0004 : reserved
// 0x0008 : reserved
// 0x000c : reserved
// 0x0010 : Data signal of OffsetA
//          bit 31~0 - OffsetA[31:0] (Read/Write)
// 0x0014 : reserved
// 0x0018 : Data signal of OffsetB
//          bit 31~0 - OffsetB[31:0] (Read/Write)
// 0x001c : reserved
// 0x0020 : Data signal of Result
//          bit 31~0 - Result[31:0] (Read)
// 0x0024 : Control signal of Result
//          bit 0  - Result_ap_vld (Read/COR)
//          others - reserved
// 0x0030 : Data signal of Idle_i
//          bit 31~0 - Idle_i[31:0] (Read/Write)
// 0x0034 : reserved
// 0x0038 : Data signal of Idle_o
//          bit 31~0 - Idle_o[31:0] (Read)
// 0x003c : Control signal of Idle_o
//          bit 0  - Idle_o_ap_vld (Read/COR)
//          others - reserved
// 0x1000 ~
// 0x1fff : Memory 'Buff' (1000 * 32b)
//          Word n : bit [31:0] - Buff[n]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETA_DATA 0x0010
#define XMK_DOT_PRODUCT_CONTROL_BITS_OFFSETA_DATA 32
#define XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETB_DATA 0x0018
#define XMK_DOT_PRODUCT_CONTROL_BITS_OFFSETB_DATA 32
#define XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_DATA  0x0020
#define XMK_DOT_PRODUCT_CONTROL_BITS_RESULT_DATA  32
#define XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_CTRL  0x0024
#define XMK_DOT_PRODUCT_CONTROL_ADDR_IDLE_I_DATA  0x0030
#define XMK_DOT_PRODUCT_CONTROL_BITS_IDLE_I_DATA  32
#define XMK_DOT_PRODUCT_CONTROL_ADDR_IDLE_O_DATA  0x0038
#define XMK_DOT_PRODUCT_CONTROL_BITS_IDLE_O_DATA  32
#define XMK_DOT_PRODUCT_CONTROL_ADDR_IDLE_O_CTRL  0x003c
#define XMK_DOT_PRODUCT_CONTROL_ADDR_BUFF_BASE    0x1000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_BUFF_HIGH    0x1fff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_BUFF        32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_BUFF        1000

