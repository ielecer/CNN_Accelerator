/*
 * https://www.xilinx.com/support/answers/19592.html
 * Function Size Limitations
 * -------------- ------- ------------------
 * printf() 51788 None, full featured
 * iprintf() 18294 No floating point, reentrant
 * xil_printf() 2953 No floating point, not reentrant(single thread only), no longlong(64 bit)
 * putnum() 284 Integer to HEX only, no other formats
 * print() 185 No numbers output, just strings
 * All of these functions can be prototyped by including <stdio.h>
 */

#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xtime_l.h"
#include "xil_cache.h"
#include "Convolution.h"
#include "Pool.h"
#include "sd.h"

//Weight of Conv1
float image[28][28][1];
float W_conv1[3][3][1][16];
float b_conv1[16];
float h_conv1[28][28][16];
float h_pool1[14][14][16];

//Weight of Conv2
float W_conv2[3][3][16][32];
float b_conv2[32];
float h_conv2[14][14][32];
float h_pool2[7][7][32];

//Weight of FC1
float W_fc1[7*7*32][128];
float b_fc1[128];
float h_fc1[128];

//Weight of FC2
float W_fc2[128][10];
float b_fc2[10];
float h_fc2[10];

int main(int argc, char **argv)
{
    init_platform();
    Xil_DCacheDisable();

    XConv xconv;
	if(XConv_Initialize(&xconv,XPAR_CONV_0_DEVICE_ID)!=XST_SUCCESS)
		xil_printf("XConv device not found\r\n");

	XPool xpool;
	if(XPool_Initialize(&xpool,XPAR_POOL_0_DEVICE_ID)!=XST_SUCCESS)
		xil_printf("XPool device not found\r\n");


    print("Hello World!\n");
	SD_Init();

    LoadWeight("W_conv1.bin", 3*3*1*16, W_conv1[0][0][0]);
	LoadWeight("b_conv1.bin", 16, b_conv1);

	LoadWeight("W_conv2.bin", 3*3*16*32, W_conv2[0][0][0]);
	LoadWeight("b_conv2.bin", 32, b_conv2);

	LoadWeight("W_fc1.bin", 7*7*32*128, W_fc1[0]);
	LoadWeight("b_fc1.bin", 128, b_fc1);

	LoadWeight("W_fc2.bin", 128*10, W_fc2[0]);
	LoadWeight("b_fc2.bin", 10, b_fc2);

#if 1
	u64 Xtime_1, Xtime_2, Xtime_3, Xtime_4;
	float Aver_time;

	XTime_StartTimer();
	XTime_GetTime(&Xtime_1);
	XTime_GetTime(&Xtime_3);
	Xtime_4 = Xtime_3 - Xtime_1;
	XTime_GetTime(&Xtime_1);

	// ------------------------------------------------------------------------------------------------
	// Design under test (DUT): CNN forward propagation
	// ------------------------------------------------------------------------------------------------
	for(int i = 0; i < 100; i++)
	{
		int label;
		rdMNISTs28_test(i, image, &label);

//		for(int j=0;j<28*28;j++)
//		{
//			unsigned char tp=inbyte();
//			image[j/28][j%28][0]= (tp*1.0)/255;
//			xil_printf("Getchar=%x\r\n",tp);
//		}

		//Conv1
		RunConv(&xconv,1,28,28,16,//CHin,Hin,Win,CHout
				3,3,1,1,1,1,//Kx,Ky,Sx,Sy,mode,relu_en
				image[0][0],W_conv1[0][0][0],b_conv1,h_conv1[0][0]);//feature_in,W,bias,feature_out
		RunPool(&xpool,16,28,28,//CHin,Hin,Win
				2,2,2,//Kx,Ky,mode
				h_conv1[0][0],h_pool1[0][0]);//feature_in,feature_out

		//Conv2
		RunConv(&xconv,16,14,14,32,//CHin,Hin,Win,CHout
				3,3,1,1,1,1,//Kx,Ky,Sx,Sy,mode,relu_en
				h_pool1[0][0],W_conv2[0][0][0],b_conv2,h_conv2[0][0]);//feature_in,W,bias,feature_out
		RunPool(&xpool,32,14,14,//CHin,Hin,Win
				2,2,2,//Kx,Ky,mode
				h_conv2[0][0],h_pool2[0][0]);//feature_in,feature_out

		//FC1
		RunConv(&xconv,32,7,7,128,//CHin,Hin,Win,CHout
				7,7,1,1,0,1,//Kx,Ky,Sx,Sy,mode,relu_en
				h_pool2[0][0],W_fc1[0],b_fc1,h_fc1);//feature_in,W,bias,feature_out

		//FC2
		RunConv(&xconv,128,1,1,10,//CHin,Hin,Win,CHout
				1,1,1,1,0,1,//Kx,Ky,Sx,Sy,mode,relu_en
				h_fc1,W_fc2[0],b_fc2,h_fc2);//feature_in,W,bias,feature_out


		float max = -10000;
		int num = 0;
		for(int m = 0; m < 10; m++)
		{
			if(h_fc2[m] > max)
			{
				max = h_fc2[m];
				num = m;
			}
//			sprintf(str, "h_fc2[%d]=%f\r\n", m, h_fc2[m]);
//	    	xil_printf(str);
		}

//		xil_printf("%c", num);
		xil_printf("predicted = %d, label = %d\t\t", num, label);

		if ((i + 1) % 5 == 0)
			print("\n");
	}
	// ------------------------------------------------------------------------------------------------

	XTime_GetTime(&Xtime_2);
	Xtime_2 = Xtime_2 - Xtime_1 - Xtime_4;
//	xil_printf("Xtime_2: 0x%08x\t 0x%08x\n\r", Xtime_2, (Xtime_2 >> 32));
	Aver_time = ((float) Xtime_2) / XIOU_SCNTRS_FREQ / 100;	// Get average computation time
	printf("Average computation time: %f seconds\n\r", Aver_time);
	print("Goodbye!\n\r");
#endif

    cleanup_platform();
    return 0;
}
