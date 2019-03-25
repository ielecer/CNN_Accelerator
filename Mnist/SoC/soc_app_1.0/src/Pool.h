#ifndef SRC_POOL_H_
#define SRC_POOL_H_

#include <stdio.h>
#include "xpool.h"
#include "xil_printf.h"

#define max(a,b) ((a>b)?a:b)
#define min(a,b) ((a>b)?b:a)

void RunPool(XPool *InstancePtr,unsigned int CHin,unsigned int Hin,unsigned int Win,
		unsigned int Kx,unsigned int Ky,unsigned int mode,
		float feature_in[],float feature_out[]
	);//mode: 0:MEAN, 1:MIN, 2:MAX

void RunPool_soft(unsigned int CHin,unsigned int Hin,unsigned int Win,
		unsigned int Kx,unsigned int Ky,unsigned int mode,
		float feature_in[],float feature_out[]
	);//mode: 0:MEAN, 1:MIN, 2:MAX

#endif /* SRC_POOL_H_ */
