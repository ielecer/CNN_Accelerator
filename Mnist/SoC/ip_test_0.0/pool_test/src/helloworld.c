#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "xil_printf.h"
#include "sleep.h"
#include "xil_cache.h"
#include "Pool.h"

#define MODE 	0	//mode: 0:MEAN, 1:MIN, 2:MAX
#define IN_WIDTH 99
#define IN_HEIGHT 66
#define IN_CH 81

#define KERNEL_WIDTH 3
#define KERNEL_HEIGHT 2

#define OUT_WIDTH (IN_WIDTH/KERNEL_WIDTH)
#define OUT_HEIGHT (IN_HEIGHT/KERNEL_HEIGHT)

float feature_in[IN_HEIGHT][IN_WIDTH][IN_CH];
float feature_out[OUT_HEIGHT][OUT_WIDTH][IN_CH];
float feature_out_soft[OUT_HEIGHT][OUT_WIDTH][IN_CH];

#define abs(x) ((x>0)?x:-x)

int main()
{
	init_platform();
	Xil_DCacheDisable();
	char str[50];

	print("Hello World\r\n");

	XPool xpool;
	if(XPool_Initialize(&xpool,XPAR_POOL_0_DEVICE_ID)!=XST_SUCCESS)
		xil_printf("XPool device not found\r\n");

	for(int i=0;i<IN_HEIGHT;i++)
		for(int j=0;j<IN_WIDTH;j++)
			for(int cin=0;cin<IN_CH;cin++)
				feature_in[i][j][cin]=(i*IN_WIDTH+j)*1;

	RunPool(&xpool,IN_CH,IN_HEIGHT,IN_WIDTH,
			KERNEL_WIDTH,KERNEL_HEIGHT,MODE,
			feature_in[0][0],feature_out[0][0]
		);

	RunPool_soft(IN_CH,IN_HEIGHT,IN_WIDTH,
			KERNEL_WIDTH,KERNEL_HEIGHT,MODE,
			feature_in[0][0],feature_out_soft[0][0]
		);//mode: 0:MEAN, 1:MIN, 2:MAX

	for(int i=0;i<OUT_HEIGHT;i++)
		for(int j=0;j<OUT_WIDTH;j++)
			for(int cout=0;cout<IN_CH;cout++)
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

	cleanup_platform();
	return 0;
}
