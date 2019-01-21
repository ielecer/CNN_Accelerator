#include <stdio.h>
#include "matmul.h"

#define ROW 3
#define COLUMN 3
#define LENGTH (ROW * COLUMN)

int main(void) {
	int data_in[LENGTH] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int data_out[ROW][COLUMN];

	// How to define a pointer of 2D array:
	// https://zhidao.baidu.com/question/161985206.html.
	mat_trans(data_in, data_out, ROW, COLUMN);

	matmul_2D_0();

	matmul_2D_1();

	return 0;
}