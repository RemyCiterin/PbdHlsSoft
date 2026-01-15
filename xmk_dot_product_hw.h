// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x00000 : Control signals
//           bit 0  - ap_start (Read/Write/COH)
//           bit 1  - ap_done (Read/COR)
//           bit 2  - ap_idle (Read)
//           bit 3  - ap_ready (Read)
//           bit 7  - auto_restart (Read/Write)
//           others - reserved
// 0x00004 : Global Interrupt Enable Register
//           bit 0  - Global Interrupt Enable (Read/Write)
//           others - reserved
// 0x00008 : IP Interrupt Enable Register (Read/Write)
//           bit 0  - enable ap_done interrupt (Read/Write)
//           bit 1  - enable ap_ready interrupt (Read/Write)
//           others - reserved
// 0x0000c : IP Interrupt Status Register (Read/TOW)
//           bit 0  - ap_done (COR/TOW)
//           bit 1  - ap_ready (COR/TOW)
//           others - reserved
// 0x02000 ~
// 0x03fff : Memory 'Output_r' (1456 * 32b)
//           Word n : bit [31:0] - Output_r[n]
// 0x08000 ~
// 0x0ffff : Memory 'MatrixA' (7904 * 32b)
//           Word n : bit [31:0] - MatrixA[n]
// 0x10000 ~
// 0x17fff : Memory 'MatrixB' (4256 * 32b)
//           Word n : bit [31:0] - MatrixB[n]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XMK_DOT_PRODUCT_CONTROL_ADDR_AP_CTRL       0x00000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_GIE           0x00004
#define XMK_DOT_PRODUCT_CONTROL_ADDR_IER           0x00008
#define XMK_DOT_PRODUCT_CONTROL_ADDR_ISR           0x0000c
#define XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_BASE 0x02000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_HIGH 0x03fff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_OUTPUT_R     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_OUTPUT_R     1456
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA_BASE  0x08000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA_HIGH  0x0ffff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA      32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA      7904
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB_BASE  0x10000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB_HIGH  0x17fff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB      32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB      4256

