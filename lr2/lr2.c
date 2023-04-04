#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#define PI 3.141592653589793
#define LENGTH 64


void dataInput() {
  return;
}

void dataOutput() {
  return;
}

void prepareDataToInput(int* in, float* out, int LENGTHBuffer) {
  int i;
  for(i = 0; i < LENGTHBuffer; i++) {
    out[i] = 0 + in[i];
  }
}

void prepareDataToOutput(float* in, int* out, int LENGTHBuffer) {
  int i;
  for(i = 0; i < LENGTHBuffer; i++) {
    out[i] = (int)in[i];
  }
}

void transpon(float *arr, float* transpon_matrix)
{
    int m = LENGTH/8;
    int n = m;
	int i = 0;
	int j = 0;

    for (i = 0; i < m; ++i )
    {
       for (j = 0; j < n; ++j )
       {
          // Index in the original matrix.
          int index1 = i*n+j;

          // Index in the transpose matrix.
          int index2 = j*m+i;

          transpon_matrix[index2] = arr[index1];
       }
    }


}
void multiply(float *arr1, float *arr2, float *after_multyply) {
    int i, j, k;
    int tempLENGTH = LENGTH/8;
    for (i = 0; i < tempLENGTH; i++) {
        for (j = 0; j < tempLENGTH; j++) {
            after_multyply[i * tempLENGTH + j] = 0;
            for (k = 0; k < tempLENGTH; k++) {
                after_multyply[i * tempLENGTH + j] += arr1[i * tempLENGTH + k] * arr2[k * tempLENGTH + j];   
            }   
        }
    }   
}
void dct(float *arr){
    int row;
    int col;
    int tempLENGTH = LENGTH/8;
    for(row = 0; row < tempLENGTH; row++) {
        for(col = 0; col < tempLENGTH; col++) {
            if(row == 0) {
                arr[row * tempLENGTH + col] = 1 / sqrt(tempLENGTH);
                arr[row * tempLENGTH + col] *= cos((2 * col + 1) * row * PI / (2 * tempLENGTH));
            } else {
                arr[row * tempLENGTH + col] = sqrt(2.0 / tempLENGTH);
                arr[row * tempLENGTH + col] *= cos((2 * col + 1) * row * PI / (2 * tempLENGTH));
            }
        }
    }   
}

void shakal(float* arr, int shift){
    int i = shift;
    for (i = shift; i<LENGTH; i++){

        arr[i]=0;
    }


}

void IDCT(float *transpon_matrix, float *P_DCT, float *dct_matrix, float * out){

   float temp[64];
   multiply(transpon_matrix,P_DCT, temp);// DCT^T  * P_DCT
   multiply(temp, dct_matrix,out);
}

void DCT(float* bits, float* dct_matrix,float* transpon_matrix, float* DCTxP, float* P_DCT, int shift){
   
   dct(dct_matrix);//DCT
   shakal(dct_matrix, shift);//DCT shakal
   multiply(dct_matrix, bits,DCTxP);//DCT * P
   
   transpon(dct_matrix,transpon_matrix);//DCT ^ T
   multiply(DCTxP,transpon_matrix, P_DCT);// DCT ^ T  * DCT * P

}

int main()
{

   
   
   int shift = 32; // ?????? shift ???????? ????????, ????????? ???? ? ??????? dct
   int inputArr[LENGTH];
   int outputArr[LENGTH];

	
   float out[LENGTH];
   float bits1d[LENGTH];
   float dct_matrix[LENGTH];//DCT
   float transpon_matrix[LENGTH];
   float DCTxP[LENGTH];//DCT * P
   float P_DCT[LENGTH];//PDCT  
   float dct_tranps[LENGTH];

   //int LENGTH_all = 320*320;
   //float bits_all[320*320];//P    102 400 elements
   int block=0;

   for (block=0; block<40*40; block++){ 

   dataInput();

   //print_arr(bits1d,LENGTH);
   //printf("\n");


   ///DCT begin
   DCT(bits1d, dct_matrix,transpon_matrix, DCTxP, P_DCT,shift);
   
   //printf("\n");
   
   
   ///IDCT begin
   
   IDCT(transpon_matrix, P_DCT, dct_matrix, out);
    //print_arr(out,  LENGTH);
	dataOutput();
	

   }
    return 0;

}

