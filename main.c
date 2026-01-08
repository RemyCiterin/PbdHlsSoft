
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include "timers_b.h"

#include "arm_neon.h"

#define IMGWIDTH 29
#define IMGHEIGHT 29
#define tour 10000

#define SIGMOID(x) (1.7159*my_tanh(0.66666667*(x)))

float my_tanh(float x) {
  // tanh(x) = (e^(2x) - 1) / (e^(2x) + 1), using a taylor approximation is not very good for the
  // negatives values because those polynoms tends to be very different to 0 for the very large
  // negative values, but I works well for the positive values because
  //
  //    (y-1) / (y+1) -------------------> 1
  //                       y --> +inf
  //
  // and
  //
  //    taylor(n,x)  ------------------> +inf
  //    exp(x)       ------------------> +inf
  //                       x --> +inf
  //
  // So I used the symetry tanh(-x) = -tanh(x), and a taylor approximation of exp(x) for the
  // positives x.
  //
  // This approach doesn't generalize well using Neon because armv7-l doesn't implement vdivq_f32
  bool sign = x > 0;

  x = sign ? 2 * x : - 2  * x;
  float xx = x * x;

  // Approximation of e^x of degree 4
  float e_approx = 1 + x + 0.5*xx + 0.1666666666666666*x*xx + 0.0416666666666666*xx*xx;

  float ret = (e_approx-1) / (e_approx+1);

  return sign ? ret : -ret;
}

void calculateLayer1(float* input, float* Layer1_Neurons_CPU);
void calculateLayer2(float* Layer1_Neurons_CPU, float* Layer1_Weights_CPU, float* Layer2_Neurons_CPU);
void calculateLayer3(float* Layer2_Neurons_CPU, float* Layer2_Weights_CPU, float* Layer3_Neurons_CPU);
void calculateLayer4(float* Layer3_Neurons_CPU, float* Layer3_Weights_CPU, float* Layer4_Neurons_CPU);
void calculateLayer5(float* Layer4_Neurons_CPU, float* Layer4_Weights_CPU, double* Layer5_Neurons_CPU);

void InitHostMem(float *Layer1_Weights_CPU,float *Layer2_Weights_CPU, float *Layer3_Weights_CPU,float *Layer4_Weights_CPU);

static double layerTimer1 = 0;
static double layerTimer2 = 0;
static double layerTimer3 = 0;
static double layerTimer4 = 0;
static double layerTimer5 = 0;

static double convolutionTimer3 = 0;
static double sigmoidTimer3 = 0;

static double productTimer4 = 0;
static double sigmoidTimer4 = 0;

int main(int argc, char** argv){

    float
        Layer1_Weights_CPU[(5*5+1)*6],
        Layer2_Weights_CPU[(5*5+1)*6*50],
        Layer3_Weights_CPU[(5*5*50+1)*100],
        Layer4_Weights_CPU[(100+1)*10];

    float
        Layer1_Neurons_CPU[IMGWIDTH*IMGHEIGHT],
        Layer2_Neurons_CPU[6*13*13],
        Layer3_Neurons_CPU[50*5*5],
        Layer4_Neurons_CPU[100];

    double
        Layer5_Neurons_CPU[10];

    int i;

    double scoremax;

    float Input[29*29] = {

    // caractère "2"

    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1

    // caractère "3"
    /*1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1

    // caractère "8"

    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
*/
    };

    InitHostMem(Layer1_Weights_CPU,Layer2_Weights_CPU,Layer3_Weights_CPU,Layer4_Weights_CPU);

    double global_timer = -dtime();

    int ITER = 100;
    for (int iter=0; iter < ITER; iter++) {
      calculateLayer1(Input, Layer1_Neurons_CPU);
      calculateLayer2(Layer1_Neurons_CPU, Layer1_Weights_CPU, Layer2_Neurons_CPU);
      calculateLayer3(Layer2_Neurons_CPU, Layer2_Weights_CPU, Layer3_Neurons_CPU);
      calculateLayer4(Layer3_Neurons_CPU, Layer3_Weights_CPU, Layer4_Neurons_CPU);
      calculateLayer5(Layer4_Neurons_CPU, Layer4_Weights_CPU, Layer5_Neurons_CPU);

      scoremax = FLT_MIN;
      int indexmax=-1;
      if (iter == ITER-1) for(i=0;i<10;i++)
      {
          printf("%d : %f\n",i,Layer5_Neurons_CPU[i]);
          if(Layer5_Neurons_CPU[i]>scoremax)
          {
              scoremax = Layer5_Neurons_CPU[i];
              indexmax = i;
          }
      }

      if (iter == ITER-1)
        printf("Le resultat est : %d \n",indexmax);
    }

    global_timer += dtime();

    printf("total: %.6f\n", global_timer);
    printf("layer 1: %.6f\n", layerTimer1);
    printf("layer 2: %.6f\n", layerTimer2);
    printf("layer 3: %.6f\n", layerTimer3);
    printf("layer 4: %.6f\n", layerTimer4);
    printf("layer 5: %.6f\n", layerTimer5);

    printf("convolution layer 3: %.6f\n", convolutionTimer3);
    printf("sigmoid layer 3: %.6f\n", sigmoidTimer3);

    printf("dot product layer 4: %.6f\n", productTimer4);
    printf("sigmoid layer 4: %.6f\n", sigmoidTimer4);

    return 0;
}




void calculateLayer1(float* input, float* Layer1_Neurons_CPU){
    layerTimer1 -= dtime();
    memcpy(Layer1_Neurons_CPU, input, IMGWIDTH*IMGHEIGHT*sizeof(float));
    layerTimer1 += dtime();
}

void calculateLayer2(float* Layer1_Neurons_CPU, float* Layer1_Weights_CPU, float* Layer2_Neurons_CPU){
    float somme;
    layerTimer2 -= dtime();
    int i,j,k,m,n;
    for(i=0;i<6;i++)
        for(j=0;j<13;j++)
            for(k=0;k<13;k++){
                somme = Layer1_Weights_CPU[26*i];
                for(m=0;m<5;m++)
                    for(n=0;n<5;n++)
                        somme += Layer1_Weights_CPU[26*i+5*m+n+1] * Layer1_Neurons_CPU[29*(m+2*j)+n+2*k];
                Layer2_Neurons_CPU[13*13*i+13*j+k] = (float) SIGMOID(somme);
            }
    layerTimer2 += dtime();
}

void calculateLayer3(float* Layer2_Neurons_CPU, float* Layer2_Weights_CPU, float* Layer3_Neurons_CPU){
    float somme;
    layerTimer3 -= dtime();
    int i,j,k,m,n;
    //for( i=0;i<50;i++)
    //    for(j=0;j<5;j++)
    //        for(k=0;k<5;k++){
    //            somme = Layer2_Weights_CPU[26*6*i];

    //            for( m=0;m<5;m++)
    //                for( n=0;n<5;n++){
    //                    somme += Layer2_Weights_CPU[26*6*i+1+6*(n+5*m)  ] * Layer2_Neurons_CPU[13*13*0+13*(2*j+m)+(2*k+n)];
    //                    somme += Layer2_Weights_CPU[26*6*i+1+6*(n+5*m)+1] * Layer2_Neurons_CPU[13*13*1+13*(2*j+m)+(2*k+n)];
    //                    somme += Layer2_Weights_CPU[26*6*i+1+6*(n+5*m)+2] * Layer2_Neurons_CPU[13*13*2+13*(2*j+m)+(2*k+n)];
    //                    somme += Layer2_Weights_CPU[26*6*i+1+6*(n+5*m)+3] * Layer2_Neurons_CPU[13*13*3+13*(2*j+m)+(2*k+n)];
    //                    somme += Layer2_Weights_CPU[26*6*i+1+6*(n+5*m)+4] * Layer2_Neurons_CPU[13*13*4+13*(2*j+m)+(2*k+n)];
    //                    somme += Layer2_Weights_CPU[26*6*i+1+6*(n+5*m)+5] * Layer2_Neurons_CPU[13*13*5+13*(2*j+m)+(2*k+n)];

    //                }
    //            Layer3_Neurons_CPU[5*5*i+5*j+k] =  (float)SIGMOID(somme);
    //        }

    int N = 50;
    int M = 5*5*6;
    int K = 5*5;

    convolutionTimer3 -= dtime();

    // Initialize first matrix
    float M1[52][152] = {{0}};
    for (int filter=0; filter < 50; filter++)
      for (int channel=0; channel < 6; channel++)
        for (int m=0; m < 5; m++)
          for (int n=0; n < 5; n++)
            M1[filter][25*channel+5*m+n] = Layer2_Weights_CPU[26*6*filter+1+6*(n+5*m)+channel];

    // Initialize second matrix
    float M2[152][28] = {{0}};
    for (int channel=0; channel < 6; channel++)
      for (int j=0; j < 5; j++)
        for (int k=0; k < 5; k++)
          for (int n=0; n < 5; n++)
            for (int m=0; m < 5; m++)
              M2[25*channel+5*m+n][5*j+k] = Layer2_Neurons_CPU[13*13*channel+13*(2*j+m)+2*k+n];

    // Zero result matrix
    float M3[52][28] = {{0}};

    // Perform matrix product
    //for (int a=0; a < N; a++)
    //  for (int b=0; b < K; b++)
    //    for (int c=0; c < M; c++)
    //      M3[a][b] += M1[a][c] * M2[c][b];

    for (int a=0; a < 52; a++) {
      for (int c=0; c < 152; c += 4) {
        float32x4_t A0 = vmovq_n_f32(M1[a][c+0]);
        float32x4_t A1 = vmovq_n_f32(M1[a][c+1]);
        float32x4_t A2 = vmovq_n_f32(M1[a][c+2]);
        float32x4_t A3 = vmovq_n_f32(M1[a][c+3]);

        for (int b=0; b < 28; b += 4)
        {
          //for (int j=b; j < b+4; j++)
          //  for (int k=c; k < c+4; k++)
          //    M3[a][j] += M1[a][k] * M2[k][j];

          float32x4_t B0 = vld1q_f32(&M2[c+0][b]);
          float32x4_t B1 = vld1q_f32(&M2[c+1][b]);
          float32x4_t B2 = vld1q_f32(&M2[c+2][b]);
          float32x4_t B3 = vld1q_f32(&M2[c+3][b]);

          float32x4_t C0 = vld1q_f32(&M3[a][b]);
          float32x4_t C1 = vmulq_f32(A0, B0);
          float32x4_t C2 = vmulq_f32(A1, B1);
          float32x4_t C3 = vmulq_f32(A2, B2);
          float32x4_t C4 = vmulq_f32(A3, B3);
          C0 =
            vaddq_f32(vaddq_f32(vaddq_f32(C0,C1),C2), vaddq_f32(C3,C4));
          vst1q_f32(&M3[a][b], C0);
        }
      }
    }
    convolutionTimer3 += dtime();

    sigmoidTimer3 -= dtime();
    // Write the result back to Layer3_Neurons_CPU
    for (int filter=0; filter < 50;filter++)
        for(int j=0;j<5;j++)
            for(int k=0;k<5;k++)
                Layer3_Neurons_CPU[5*5*filter+5*j+k] =
                  (float) SIGMOID(Layer2_Weights_CPU[26*6*filter] + M3[filter][5*j+k]);
    sigmoidTimer3 += dtime();
    layerTimer3 += dtime();
}

void calculateLayer4(float* Layer3_Neurons_CPU, float* Layer3_Weights_CPU, float* Layer4_Neurons_CPU){
    layerTimer4 -= dtime();
    int i, j, k, m;
    productTimer4 -= dtime();
    for( i=0;i<100;i++){
        int j = 0;
        float somme = Layer3_Weights_CPU[i*(1+50*25)];

        float32x4_t acc = vmovq_n_f32(0.0);
        for (j=0; j < 1248; j += 4) {
          float32x4_t tmp1 = vld1q_f32(&Layer3_Weights_CPU[i*(1+50*25)+1 + j]);
          float32x4_t tmp2 = vld1q_f32(&Layer3_Neurons_CPU[j]);
          acc = vaddq_f32(acc, vmulq_f32(tmp1, tmp2));
        }

        for (; j < 1250; j++) {
          float lhs = Layer3_Weights_CPU[i*(1+50*25)+1 + j];
          float rhs = Layer3_Neurons_CPU[j];
          somme += lhs * rhs;
        }

        Layer4_Neurons_CPU[i] = somme +
          vgetq_lane_f32(acc,0) +
          vgetq_lane_f32(acc,1) +
          vgetq_lane_f32(acc,2) +
          vgetq_lane_f32(acc,3);
    }
    productTimer4 += dtime();

    sigmoidTimer4 -= dtime();
    for (int i=0; i < 100; i++)
      Layer4_Neurons_CPU[i] = (float) SIGMOID(Layer4_Neurons_CPU[i]);
    sigmoidTimer4 += dtime();

    layerTimer4 += dtime();
}

void calculateLayer5(float* Layer4_Neurons_CPU, float* Layer4_Weights_CPU, double* Layer5_Neurons_CPU){
    float somme;
    layerTimer5 -= dtime();
    int i, j;
    for( i=0;i<10;i++){
        somme = Layer4_Weights_CPU[101*i];
        for( j=0;j<100;j++)
            somme += Layer4_Weights_CPU[1+101*i+j] * Layer4_Neurons_CPU[j];
        Layer5_Neurons_CPU[i] = SIGMOID(somme);
    }
    layerTimer5 += dtime();
}

