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
// 0x01000 ~
// 0x01fff : Memory 'MatrixB0' (896 * 32b)
//           Word n : bit [31:0] - MatrixB0[n]
// 0x02000 ~
// 0x03fff : Memory 'MatrixA0' (1664 * 32b)
//           Word n : bit [31:0] - MatrixA0[n]
// 0x04000 ~
// 0x05fff : Memory 'MatrixA1' (1664 * 32b)
//           Word n : bit [31:0] - MatrixA1[n]
// 0x06000 ~
// 0x07fff : Memory 'MatrixA2' (1664 * 32b)
//           Word n : bit [31:0] - MatrixA2[n]
// 0x08000 ~
// 0x09fff : Memory 'MatrixA3' (1664 * 32b)
//           Word n : bit [31:0] - MatrixA3[n]
// 0x0a000 ~
// 0x0bfff : Memory 'MatrixA4' (1664 * 32b)
//           Word n : bit [31:0] - MatrixA4[n]
// 0x0c000 ~
// 0x0cfff : Memory 'MatrixB1' (896 * 32b)
//           Word n : bit [31:0] - MatrixB1[n]
// 0x0d000 ~
// 0x0dfff : Memory 'MatrixB2' (896 * 32b)
//           Word n : bit [31:0] - MatrixB2[n]
// 0x0e000 ~
// 0x0efff : Memory 'MatrixB3' (896 * 32b)
//           Word n : bit [31:0] - MatrixB3[n]
// 0x0f000 ~
// 0x0ffff : Memory 'MatrixB4' (896 * 32b)
//           Word n : bit [31:0] - MatrixB4[n]
// 0x10000 ~
// 0x11fff : Memory 'Output_r' (1456 * 32b)
//           Word n : bit [31:0] - Output_r[n]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XMK_DOT_PRODUCT_CONTROL_ADDR_AP_CTRL       0x00000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_GIE           0x00004
#define XMK_DOT_PRODUCT_CONTROL_ADDR_IER           0x00008
#define XMK_DOT_PRODUCT_CONTROL_ADDR_ISR           0x0000c
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB0_BASE 0x01000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB0_HIGH 0x01fff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB0     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB0     896
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA0_BASE 0x02000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA0_HIGH 0x03fff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA0     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA0     1664
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA1_BASE 0x04000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA1_HIGH 0x05fff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA1     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA1     1664
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA2_BASE 0x06000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA2_HIGH 0x07fff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA2     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA2     1664
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA3_BASE 0x08000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA3_HIGH 0x09fff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA3     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA3     1664
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA4_BASE 0x0a000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA4_HIGH 0x0bfff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA4     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA4     1664
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB1_BASE 0x0c000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB1_HIGH 0x0cfff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB1     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB1     896
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB2_BASE 0x0d000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB2_HIGH 0x0dfff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB2     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB2     896
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB3_BASE 0x0e000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB3_HIGH 0x0efff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB3     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB3     896
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB4_BASE 0x0f000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB4_HIGH 0x0ffff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB4     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB4     896
#define XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_BASE 0x10000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_HIGH 0x11fff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_OUTPUT_R     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_OUTPUT_R     1456

