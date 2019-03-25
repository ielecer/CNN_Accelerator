#include "sd.h"

static FATFS fatfs;

int SD_Init()
{
	FRESULT rc;
	rc = f_mount(&fatfs, "", 0);
	if(rc)
	{
		xil_printf("Error : f_mount returned %d\r\n.", rc);
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}

int LoadWeight(char *filename,int dat_length,float *dst)
{
	FIL FP;
	FRESULT result;//0: success
	UINT bw;

	result = f_open(&FP, filename, FA_READ);
	if (result)
	{
		xil_printf("Can't Open %s\r\n", filename);
		return XST_FAILURE;
	}

	result = f_read(&FP, dst, dat_length*sizeof(float) , &bw);
	if (result)
	{
		xil_printf("Can't read %s!\r\n", filename);
		return XST_FAILURE;
	}

	f_close(&FP);
	return XST_SUCCESS;
}

int rdMNISTs28_test(u32 num, float img[28][28][1], int *label)
{
	FIL fil;
	FRESULT rc;
	UINT bw;

	char imagefile[] = "Tsimgs.x3";
	char labelfile[] = "Tslbls.x1";
	rc = f_open(&fil, imagefile, FA_READ);
	if (rc)
	{
		xil_printf("Error %d: Can't Open %s!\r\n", rc, imagefile);
		return XST_FAILURE;
	}
	rc = f_lseek(&fil, num * 784 + 16);
	if (rc)
	{
		xil_printf("Error %d: Can't seek %s!\r\n", rc, imagefile);
		return XST_FAILURE;
	}
	u8 picture[28][28];
	int j,k;
	for (j = 0; j < 28; j++)
	{
		rc = f_read(&fil, picture[j], 28, &bw);
		if (rc)
		{
			xil_printf("Error %d: Can't read %s!\r\n", rc, imagefile);
			return XST_FAILURE;
		}
		for (k = 0; k < 28; k++)
		{
			img[j][k][0] = picture[j][k]/255.0;
		}
	}
	rc = f_close(&fil);
	if (rc)
	{
		xil_printf("Error %d: Can't close %s!\r\n", rc, imagefile);
		return XST_FAILURE;
	}
	rc = f_open(&fil, labelfile, FA_READ);
	if (rc)
	{
		xil_printf("Error %d: Can't Open %s!\r\n", rc, imagefile);
		return XST_FAILURE;
	}
	rc = f_lseek(&fil, num + 8);
	if (rc)
	{
		xil_printf("Error %d: Can't seek %s!\r\n", rc, imagefile);
		return XST_FAILURE;
	}
	u8 rtn;
	rc = f_read(&fil, &rtn, 1, &bw);
	if (rc)
	{
		xil_printf("Error %d: Can't read %s!\r\n", rc, imagefile);
		return XST_FAILURE;
	}
	*label = rtn;

	rc = f_close(&fil);
	if (rc)
	{
		xil_printf("Error %d: Can't close %s!\r\n", rc, imagefile);
		return XST_FAILURE;
	}
	//xil_printf("Read MNIST succeed!\r\n");
	return XST_SUCCESS;

}

