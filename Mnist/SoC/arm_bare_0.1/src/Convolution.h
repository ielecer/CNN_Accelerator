#ifndef SRC_CONVOLUTION_H_
#define SRC_CONVOLUTION_H_

#include <stdio.h>
#include "xil_printf.h"

void RunConv_soft(unsigned int CHin,unsigned int Hin,unsigned int Win,unsigned int CHout,
		unsigned int Kx,unsigned int Ky,unsigned int Sx,unsigned int Sy,unsigned int mode,unsigned int relu_en,
		float feature_in[],float W[],float bias[],float feature_out[]);

#endif
