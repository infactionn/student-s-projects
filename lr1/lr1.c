
/* Include Files */ 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data1.h"


#define PI 3.141592653589793
#define max_size 20//filter's order
#define delay 20//otschet ot nylya dlya viborki okna

int len = 100;//len if cycle
int N = 100;//len of viborka

float input_data[100] = {A_ARRAY};//vxodnie onscheti

float time_Rect[100];//time window rectangle
float time_Bartlett[100];//time window Bartlett
float time_Hann[100];//time window Hann

float output_data_Rect[100];// output of rectangle filter (time)
float output_data_Bartlett[100];// output of Bartlett filter (time)
float output_data_Hann[100];// output of Hann filter (time)

float out_f1r[100];//real spectrum out signal for rect
float out_f1i[100];//imag spectrum out signal for rect


float out_f2r[100];//real spectrum out signal for Bartlett
float out_f2i[100];//imag spectrum out signal for Bartlett

float out_f3r[100];//real spectrum out signal for Hann
float out_f3i[100];//imag spectrum out signal for Hann


float Xr_in[100];//real input
float Xi_in[100];//image input


float Xr_w1[100];//real window 1
float Xr_w2[100];//real window 2
float Xr_w3[100];//real window 3

float Xi_w1[100];//image window 1
float Xi_w2[100];//image window 2
float Xi_w3[100];//image window 3


float input_spectr[100];
float window1_spectr[100];
float window2_spectr[100];
float window3_spectr[100];

float out_f1[100];//spectrum out signal for rect
float out_f2[100];//spectrum out signal for Bartlett
float out_f3[100];//spectrum out signal for Hann

void gen_Rect(){
int i;
for (i=0; i < N;i++){
    if (i >=delay && i <max_size+delay){
      time_Rect[i]=1;
    }
    else{
        time_Rect[i] = 0;
    }
} 

}

void gen_Bartlett(){
int i;
for (i=0; i < max_size;i++){
    time_Bartlett[i]=(max_size-2*fabs(i-max_size/2))/max_size;
}

for (i=0; i < N;i++){
    if (i >=delay && i <delay+max_size){
    time_Bartlett[i]=time_Bartlett[i-delay];
    }
}

for (i=0; i < N;i++){
    if (i <=delay || i >delay+max_size){
    time_Bartlett[i]=0;
    }
}
}

void gen_Hann(){
int i;
for (i=0; i < N;i++){
    if (i >=delay && i <=max_size+delay){
      time_Hann[i]=0.5-0.5*cos(2*PI*i/max_size);
    }
    else{
        time_Hann[i]=0;
    }
} 

}

void do_window1(){
    int i;
    for (i=delay;i<delay+max_size;i++){
        output_data_Rect[i] = input_data[i] * time_Rect[i];
        
    }
}

void do_window2(){
    int i;
    for (i=delay;i<delay+max_size;i++){
        output_data_Bartlett[i] = input_data[i] * time_Bartlett[i];
        
    }
}

void do_window3(){
    int i;
    for (i=delay;i<delay+max_size;i++){
        output_data_Hann[i] = input_data[i] * time_Hann[i];
        
    }
}
void DFT(){


int k,n=0;

for (k = 0; k < N; k++) {
        Xr_w1[k] = 0;
        Xi_w1[k] = 0;
        
        Xr_w2[k] = 0;
        Xi_w2[k] = 0;
        
        Xr_w3[k] = 0;
        Xi_w3[k] = 0;

    Xr_in[k] = 0;
        Xi_in[k] = 0;

    for (n = 0; n < N; n++) {
      Xr_in[k]= (Xr_in[k] + input_data[n] * cos(2 * PI * k * n / N));//spectrum input data
            Xi_in[k]= (Xi_in[k] - input_data[n] * sin(2 * PI * k * n / N));//
      
        } 
    input_spectr[k] = sqrt(Xr_in[k]*Xr_in[k]+Xi_in[k]*Xi_in[k]);
    

        for (n = 0; n < len; n++) {//1st window
            Xr_w1[k]= (Xr_w1[k] + time_Rect[n] * cos(2 * PI * k * n / N));//spectrum 1st window
            Xi_w1[k]= (Xi_w1[k] - time_Rect[n] * sin(2 * PI * k * n / N));//  
        } 
        window1_spectr[k]=sqrt( Xr_w1[k]* Xr_w1[k]+Xi_w1[k]*Xi_w1[k]);
for (n = 0; n < len; n++) {//2nd window
            Xr_w2[k]= (Xr_w2[k] + time_Bartlett[n] * cos(2 * PI * k * n / N));//spectrum 2nd window
            Xi_w2[k]= (Xi_w2[k] - time_Bartlett[n] * sin(2 * PI * k * n / N));//  
        } 
        window2_spectr[k]=sqrt( Xr_w2[k]* Xr_w2[k]+Xi_w2[k]*Xi_w2[k]);
        
        for (n = 0; n < len; n++) {//3rd window
            Xr_w3[k]= (Xr_w3[k] + time_Hann[n] * cos(2 * PI * k * n / N));//spectrum 3rd window
            Xi_w3[k]= (Xi_w3[k] - time_Hann[n] * sin(2 * PI * k * n / N));//  
        } 
        window3_spectr[k]=sqrt( Xr_w3[k]* Xr_w3[k]+Xi_w3[k]*Xi_w3[k]);

        for (n = 0; n < N; n++) {//spectrum output signals
      out_f1r[k]= (out_f1r[k] + output_data_Rect[n] * cos(2 * PI * k * n / N));//spectrum 1st output
            out_f1i[k]= (out_f1i[k] - output_data_Rect[n] * sin(2 * PI * k * n / N));//
            
            out_f2r[k]= (out_f2r[k] + output_data_Bartlett[n] * cos(2 * PI * k * n / N));//spectrum 2nd output
            out_f2i[k]= (out_f2i[k] - output_data_Bartlett[n] * sin(2 * PI * k * n / N));//
            
            out_f3r[k]= (out_f3r[k] + output_data_Hann[n] * cos(2 * PI * k * n / N));//spectrum 3rd output
            out_f3i[k]= (out_f3i[k] - output_data_Hann[n] * sin(2 * PI * k * n / N));//
      
        } 
    out_f1[k] = sqrt(out_f1r[k]*out_f1r[k]+out_f1i[k]*out_f1i[k]);//abs 1st out
    out_f2[k] = sqrt(out_f2r[k]*out_f2r[k]+out_f2i[k]*out_f2i[k]);//abs 2nd out
    out_f3[k] = sqrt(out_f3r[k]*out_f3r[k]+out_f3i[k]*out_f3i[k]);//abs 3rd out
    }


}




void calculate(){
    
gen_Rect();//Window
do_window1();

gen_Bartlett();//Bartlett
do_window2();

gen_Hann();//Hann
do_window3();

DFT();

}



void main()
{
calculate();

}