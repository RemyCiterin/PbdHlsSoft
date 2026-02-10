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
// 0x00800 ~
// 0x00fff : Memory 'MatrixB0' (448 * 32b)
//           Word n : bit [31:0] - MatrixB0[n]
// 0x01000 ~
// 0x01fff : Memory 'MatrixA0' (832 * 32b)
//           Word n : bit [31:0] - MatrixA0[n]
// 0x02000 ~
// 0x02fff : Memory 'MatrixA1' (832 * 32b)
//           Word n : bit [31:0] - MatrixA1[n]
// 0x03000 ~
// 0x03fff : Memory 'MatrixA2' (832 * 32b)
//           Word n : bit [31:0] - MatrixA2[n]
// 0x04000 ~
// 0x04fff : Memory 'MatrixA3' (832 * 32b)
//           Word n : bit [31:0] - MatrixA3[n]
// 0x05000 ~
// 0x05fff : Memory 'MatrixA4' (832 * 32b)
//           Word n : bit [31:0] - MatrixA4[n]
// 0x06000 ~
// 0x06fff : Memory 'MatrixA5' (832 * 32b)
//           Word n : bit [31:0] - MatrixA5[n]
// 0x07000 ~
// 0x07fff : Memory 'MatrixA6' (832 * 32b)
//           Word n : bit [31:0] - MatrixA6[n]
// 0x08000 ~
// 0x08fff : Memory 'MatrixA7' (832 * 32b)
//           Word n : bit [31:0] - MatrixA7[n]
// 0x09000 ~
// 0x09fff : Memory 'MatrixA8' (832 * 32b)
//           Word n : bit [31:0] - MatrixA8[n]
// 0x0a000 ~
// 0x0afff : Memory 'MatrixA9' (832 * 32b)
//           Word n : bit [31:0] - MatrixA9[n]
// 0x0b000 ~
// 0x0b7ff : Memory 'MatrixB1' (448 * 32b)
//           Word n : bit [31:0] - MatrixB1[n]
// 0x0b800 ~
// 0x0bfff : Memory 'MatrixB2' (448 * 32b)
//           Word n : bit [31:0] - MatrixB2[n]
// 0x0c000 ~
// 0x0c7ff : Memory 'MatrixB3' (448 * 32b)
//           Word n : bit [31:0] - MatrixB3[n]
// 0x0c800 ~
// 0x0cfff : Memory 'MatrixB4' (448 * 32b)
//           Word n : bit [31:0] - MatrixB4[n]
// 0x0d000 ~
// 0x0d7ff : Memory 'MatrixB5' (448 * 32b)
//           Word n : bit [31:0] - MatrixB5[n]
// 0x0d800 ~
// 0x0dfff : Memory 'MatrixB6' (448 * 32b)
//           Word n : bit [31:0] - MatrixB6[n]
// 0x0e000 ~
// 0x0e7ff : Memory 'MatrixB7' (448 * 32b)
//           Word n : bit [31:0] - MatrixB7[n]
// 0x0e800 ~
// 0x0efff : Memory 'MatrixB8' (448 * 32b)
//           Word n : bit [31:0] - MatrixB8[n]
// 0x0f000 ~
// 0x0f7ff : Memory 'MatrixB9' (448 * 32b)
//           Word n : bit [31:0] - MatrixB9[n]
// 0x10000 ~
// 0x11fff : Memory 'Output_r' (1456 * 32b)
//           Word n : bit [31:0] - Output_r[n]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XMK_DOT_PRODUCT_CONTROL_ADDR_AP_CTRL       0x00000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_GIE           0x00004
#define XMK_DOT_PRODUCT_CONTROL_ADDR_IER           0x00008
#define XMK_DOT_PRODUCT_CONTROL_ADDR_ISR           0x0000c
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB0_BASE 0x00800
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB0_HIGH 0x00fff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB0     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB0     448
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA0_BASE 0x01000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA0_HIGH 0x01fff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA0     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA0     832
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA1_BASE 0x02000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA1_HIGH 0x02fff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA1     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA1     832
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA2_BASE 0x03000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA2_HIGH 0x03fff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA2     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA2     832
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA3_BASE 0x04000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA3_HIGH 0x04fff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA3     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA3     832
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA4_BASE 0x05000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA4_HIGH 0x05fff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA4     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA4     832
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA5_BASE 0x06000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA5_HIGH 0x06fff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA5     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA5     832
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA6_BASE 0x07000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA6_HIGH 0x07fff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA6     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA6     832
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA7_BASE 0x08000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA7_HIGH 0x08fff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA7     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA7     832
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA8_BASE 0x09000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA8_HIGH 0x09fff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA8     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA8     832
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA9_BASE 0x0a000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXA9_HIGH 0x0afff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXA9     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXA9     832
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB1_BASE 0x0b000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB1_HIGH 0x0b7ff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB1     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB1     448
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB2_BASE 0x0b800
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB2_HIGH 0x0bfff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB2     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB2     448
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB3_BASE 0x0c000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB3_HIGH 0x0c7ff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB3     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB3     448
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB4_BASE 0x0c800
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB4_HIGH 0x0cfff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB4     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB4     448
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB5_BASE 0x0d000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB5_HIGH 0x0d7ff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB5     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB5     448
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB6_BASE 0x0d800
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB6_HIGH 0x0dfff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB6     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB6     448
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB7_BASE 0x0e000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB7_HIGH 0x0e7ff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB7     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB7     448
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB8_BASE 0x0e800
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB8_HIGH 0x0efff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB8     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB8     448
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB9_BASE 0x0f000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_MATRIXB9_HIGH 0x0f7ff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_MATRIXB9     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_MATRIXB9     448
#define XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_BASE 0x10000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_OUTPUT_R_HIGH 0x11fff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_OUTPUT_R     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_OUTPUT_R     1456

