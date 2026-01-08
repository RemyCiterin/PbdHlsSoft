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
// 0x00080 ~
// 0x000ff : Memory 'OffsetA' (32 * 32b)
//           Word n : bit [31:0] - OffsetA[n]
// 0x00100 ~
// 0x0017f : Memory 'OffsetB' (32 * 32b)
//           Word n : bit [31:0] - OffsetB[n]
// 0x00180 ~
// 0x001ff : Memory 'Size' (32 * 32b)
//           Word n : bit [31:0] - Size[n]
// 0x00200 ~
// 0x0027f : Memory 'Result' (32 * 32b)
//           Word n : bit [31:0] - Result[n]
// 0x20000 ~
// 0x3ffff : Memory 'Scratchpad_0' (25000 * 32b)
//           Word n : bit [31:0] - Scratchpad_0[n]
// 0x40000 ~
// 0x5ffff : Memory 'Scratchpad_1' (25000 * 32b)
//           Word n : bit [31:0] - Scratchpad_1[n]
// 0x60000 ~
// 0x7ffff : Memory 'Scratchpad_2' (25000 * 32b)
//           Word n : bit [31:0] - Scratchpad_2[n]
// 0x80000 ~
// 0x9ffff : Memory 'Scratchpad_3' (25000 * 32b)
//           Word n : bit [31:0] - Scratchpad_3[n]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XMK_DOT_PRODUCT_CONTROL_ADDR_AP_CTRL           0x00000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_GIE               0x00004
#define XMK_DOT_PRODUCT_CONTROL_ADDR_IER               0x00008
#define XMK_DOT_PRODUCT_CONTROL_ADDR_ISR               0x0000c
#define XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETA_BASE      0x00080
#define XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETA_HIGH      0x000ff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_OFFSETA          32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_OFFSETA          32
#define XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETB_BASE      0x00100
#define XMK_DOT_PRODUCT_CONTROL_ADDR_OFFSETB_HIGH      0x0017f
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_OFFSETB          32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_OFFSETB          32
#define XMK_DOT_PRODUCT_CONTROL_ADDR_SIZE_BASE         0x00180
#define XMK_DOT_PRODUCT_CONTROL_ADDR_SIZE_HIGH         0x001ff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_SIZE             32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_SIZE             32
#define XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_BASE       0x00200
#define XMK_DOT_PRODUCT_CONTROL_ADDR_RESULT_HIGH       0x0027f
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_RESULT           32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_RESULT           32
#define XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_0_BASE 0x20000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_0_HIGH 0x3ffff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_SCRATCHPAD_0     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_SCRATCHPAD_0     25000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_1_BASE 0x40000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_1_HIGH 0x5ffff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_SCRATCHPAD_1     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_SCRATCHPAD_1     25000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_2_BASE 0x60000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_2_HIGH 0x7ffff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_SCRATCHPAD_2     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_SCRATCHPAD_2     25000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_3_BASE 0x80000
#define XMK_DOT_PRODUCT_CONTROL_ADDR_SCRATCHPAD_3_HIGH 0x9ffff
#define XMK_DOT_PRODUCT_CONTROL_WIDTH_SCRATCHPAD_3     32
#define XMK_DOT_PRODUCT_CONTROL_DEPTH_SCRATCHPAD_3     25000

