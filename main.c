
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include "timers_b.h"

#define IMGWIDTH 29
#define IMGHEIGHT 29
#define tour 10000

#define SIGMOID(x) (1.7159*tanh(0.66666667*(x)))
#define DSIGMOID(S) (0.66666667/1.7159*(1.7159+(S))*(1.7159-(S)))

void calculateLayer1(float* input, float* Layer1_Neurons_CPU);
void calculateLayer2(float* Layer1_Neurons_CPU, float* Layer1_Weights_CPU, float* Layer2_Neurons_CPU);
void calculateLayer3(float* Layer2_Neurons_CPU, float* Layer2_Weights_CPU, float* Layer3_Neurons_CPU);
void calculateLayer4(float* Layer3_Neurons_CPU, float* Layer3_Weights_CPU, float* Layer4_Neurons_CPU);
void calculateLayer5(float* Layer4_Neurons_CPU, float* Layer4_Weights_CPU, double* Layer5_Neurons_CPU);

void InitHostMem(float *Layer1_Weights_CPU,float *Layer2_Weights_CPU, float *Layer3_Weights_CPU,float *Layer4_Weights_CPU);

static uint64_t myTimer1 = 0;
static uint64_t myTimer2 = 0;
static uint64_t myTimer3 = 0;
static uint64_t myTimer4 = 0;
static uint64_t myTimer5 = 0;

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

    uint64_t global_timer = -(uint64_t)(i64cycle());

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

    global_timer += (uint64_t)(i64cycle());

    printf("total: %.4f\n", (float)global_timer / (float)ITER);
    printf("layer 1: %.4f\n", (float)myTimer1 / (float)ITER);
    printf("layer 2: %.4f\n", (float)myTimer2 / (float)ITER);
    printf("layer 3: %.4f\n", (float)myTimer3 / (float)ITER);
    printf("layer 4: %.4f\n", (float)myTimer4 / (float)ITER);
    printf("layer 5: %.4f\n", (float)myTimer5 / (float)ITER);

    return 0;
}




void calculateLayer1(float* input, float* Layer1_Neurons_CPU){
    myTimer1 -= (uint64_t)(i64cycle());
    memcpy(Layer1_Neurons_CPU, input, IMGWIDTH*IMGHEIGHT*sizeof(float));
    myTimer1 += (uint64_t)(i64cycle());
}

void calculateLayer2(float* Layer1_Neurons_CPU, float* Layer1_Weights_CPU, float* Layer2_Neurons_CPU){
    float somme;
    myTimer2 -= (uint64_t)(i64cycle());
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
    myTimer2 += (uint64_t)(i64cycle());
}

void calculateLayer3(float* Layer2_Neurons_CPU, float* Layer2_Weights_CPU, float* Layer3_Neurons_CPU){
    float somme;
    myTimer3 -= (uint64_t)(i64cycle());
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

    // Initialize first matrix
    float M1[50][5*5*6];
    for (int filter=0; filter < 50; filter++)
      for (int channel=0; channel < 6; channel++)
        for (int m=0; m < 5; m++)
          for (int n=0; n < 5; n++)
            M1[filter][25*channel+5*m+n] = Layer2_Weights_CPU[26*6*filter+1+6*(n+5*m)+channel];

    // Initialize second matrix
    float M2[5*5*6][5*5];
    for (int channel=0; channel < 6; channel++)
      for (int j=0; j < 5; j++)
        for (int k=0; k < 5; k++)
          for (int n=0; n < 5; n++)
            for (int m=0; m < 5; m++)
              M2[25*channel+5*m+n][5*j+k] = Layer2_Neurons_CPU[13*13*channel+13*(2*j+m)+2*k+n];

    // Zero result matrix
    float M3[50][5*5];
    for (int a=0; a < N; a++)
      for (int b=0; b < K; b++)
        M3[a][b] = 0.0;

    // Perform matrix product
    for (int a=0; a < N; a++)
      for (int c=0; c < M; c++)
        for (int b=0; b < K; b++)
          M3[a][b] += M1[a][c] * M2[c][b];

    // Write the result back to Layer3_Neurons_CPU
    for (int filter=0; filter < 50;filter++)
        for(int j=0;j<5;j++)
            for(int k=0;k<5;k++)
                Layer3_Neurons_CPU[5*5*filter+5*j+k] =
                  (float) SIGMOID(Layer2_Weights_CPU[26*6*filter] + M3[filter][5*j+k]);
    myTimer3 += (uint64_t)(i64cycle());
}

void calculateLayer4(float* Layer3_Neurons_CPU, float* Layer3_Weights_CPU, float* Layer4_Neurons_CPU){
    float somme;
    myTimer4 -= (uint64_t)(i64cycle());
    int i, j, k, m;
    for( i=0;i<100;i++){
        somme = Layer3_Weights_CPU[i*(1+50*25)];
        for( j=0;j<1250;j++)
            somme += Layer3_Weights_CPU[i*(1+50*25)+1 + j] * Layer3_Neurons_CPU[j];

        Layer4_Neurons_CPU[i] = (float) SIGMOID(somme);
    }

    myTimer4 += (uint64_t)(i64cycle());
}

void calculateLayer5(float* Layer4_Neurons_CPU, float* Layer4_Weights_CPU, double* Layer5_Neurons_CPU){
    float somme;
    myTimer5 -= (uint64_t)(i64cycle());
    int i, j;
    for( i=0;i<10;i++){
        somme = Layer4_Weights_CPU[101*i];
        for( j=0;j<100;j++)
            somme += Layer4_Weights_CPU[1+101*i+j] * Layer4_Neurons_CPU[j];
        Layer5_Neurons_CPU[i] = SIGMOID(somme);
    }
    myTimer5 += (uint64_t)(i64cycle());
}

