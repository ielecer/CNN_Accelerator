#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xil_printf.h"
#include "sleep.h"
#include "xil_cache.h"
#include "Convolution.h"

#define IN_WIDTH 75
#define IN_HEIGHT 10
#define IN_CH 10

#define KERNEL_WIDTH 3
#define KERNEL_HEIGHT 5
#define X_STRIDE 1
#define Y_STRIDE 1

#define RELU_EN  0
#define MODE     0          //0:VALID, 1:SAME
#define X_PADDING (MODE?(KERNEL_WIDTH-1)/2:0)
#define Y_PADDING (MODE?(KERNEL_HEIGHT-1)/2:0)

#define OUT_CH 1
#define OUT_WIDTH ((IN_WIDTH+2*X_PADDING-KERNEL_WIDTH)/X_STRIDE+1)
#define OUT_HEIGHT ((IN_HEIGHT+2*Y_PADDING-KERNEL_HEIGHT)/Y_STRIDE+1)

float feature_in[IN_HEIGHT][IN_WIDTH][IN_CH];
float W[KERNEL_HEIGHT][KERNEL_WIDTH][IN_CH][OUT_CH];
float bias[OUT_CH];
float feature_out[OUT_HEIGHT][OUT_WIDTH][OUT_CH];
float feature_out_soft[OUT_HEIGHT][OUT_WIDTH][OUT_CH];

#define abs(x) ((x>0)?x:-x)

int main()
{
    init_platform();
    Xil_DCacheDisable();
    char str[50];

    xil_printf("Hello World\r\n");

    XConv xconv;
    if(XConv_Initialize(&xconv,XPAR_CONV_0_DEVICE_ID)!=XST_SUCCESS)
    	xil_printf("XConv device not found\r\n");

	for(int i=0;i<IN_HEIGHT;i++)
		for(int j=0;j<IN_WIDTH;j++)
			for(int cin=0;cin<IN_CH;cin++)
				feature_in[i][j][cin]=(i*IN_WIDTH+j)*1;

	for(int i=0;i<KERNEL_HEIGHT;i++)
		for(int j=0;j<KERNEL_WIDTH;j++)
			for(int cin=0;cin<IN_CH;cin++)
				for(int cout=0;cout<OUT_CH;cout++)
					W[i][j][cin][cout]=(i*KERNEL_WIDTH+j)*1;

	for(int cout=0;cout<OUT_CH;cout++)
		bias[cout]=cout;

	RunConv(&xconv,IN_CH,IN_HEIGHT,IN_WIDTH,OUT_CH,
			KERNEL_WIDTH,KERNEL_HEIGHT,X_STRIDE,Y_STRIDE,MODE,RELU_EN,
			feature_in[0][0],W[0][0][0],bias,feature_out[0][0]);

	RunConv_soft(IN_CH,IN_HEIGHT,IN_WIDTH,OUT_CH,
			KERNEL_WIDTH,KERNEL_HEIGHT,X_STRIDE,Y_STRIDE,MODE,RELU_EN,
			feature_in[0][0],W[0][0][0],bias,feature_out_soft[0][0]);

	for(int i=0;i<OUT_HEIGHT;i++)
		for(int j=0;j<OUT_WIDTH;j++)
			for(int cout=0;cout<OUT_CH;cout++)
			{
				//if(abs(feature_out[i][j][cout]-feature_out_soft[i][j][cout])>0.0001*feature_out_soft[i][j][cout] )
				{
					sprintf(str,"feature_out     [%d][%d][%d]=%f\r\n",i,j,cout,feature_out[i][j][cout]);
					xil_printf(str);
					sprintf(str,"feature_out_soft[%d][%d][%d]=%f\r\n",i,j,cout,feature_out_soft[i][j][cout]);
					xil_printf(str);
				}
			}

	printf("1234\n");

//	for(int i=0;i<IN_HEIGHT;i++)
//	{
//		for(int j=0;j<IN_WIDTH;j++)
//		{
//			sprintf(str,"%f  ",feature_in[i][j][0]);
//			xil_printf(str);
//		}
//		xil_printf("\r\n");
//	}
//
//	for(int i=0;i<KERNEL_HEIGHT;i++)
//	{
//		for(int j=0;j<KERNEL_WIDTH;j++)
//		{
//			sprintf(str,"%4f  ",W[i][j][0][0]);
//			xil_printf(str);
//		}
//		xil_printf("\r\n");
//	}

    cleanup_platform();
    return 0;
}
