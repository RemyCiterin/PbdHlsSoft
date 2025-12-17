#include "arm_neon.h"

float baseline_dot_product(float *x, float *y, int size) {
  float32x4_t acc = vmovq_n_f32(0.0);
  for (int i=0; i < size; i += 4) {
    float32x4_t lhs = vld1q_f32(&x[i]);
    float32x4_t rhs = vld1q_f32(&y[i]);
    acc = vaddq_f32(acc, vmulq_f32(lhs, rhs));
  }

  return vgetq_lane_f32(acc,0) + vgetq_lane_f32(acc,1) + vgetq_lane_f32(acc,2) + vgetq_lane_f32(acc,3);
}
