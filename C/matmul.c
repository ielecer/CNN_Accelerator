#include <stdio.h>
#include "matmul.h"

// 2D matrix input in the form of 2D.
void matmul_2D_0(void) {
    int a[2][2] = {{1, 2}, {3, 4}};
	int b[2][2] = {{1, 2}, {3, 4}};
	int c[2][2] = {{0, 0}, {0, 0}};

    for(char i = 0; i < 2; i++) {
        for(char j = 0; j < 2; j++) {
            for(char k = 0; k < 2; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    for(char i = 0; i < 2; i++) {
		for(char j = 0; j < 2; j++) {
			printf("%d ", c[i][j]);
		}
		printf("\n");
	}
}

// How to define a pointer of 2D array:
// https://zhidao.baidu.com/question/161985206.html.
void mat_trans(int *data_in, int (*data_out)[2], char row, char column) {

    // Transform 1D array to 2D array/matrix.
    for(char i = 0; i < row; i++) {
        for(char j = 0; j < column; j++) {
            data_out[i][j] = data_in[i * row + j];
            data_out[i][j] = data_in[i * column + j];
        }
    }

    for(char i = 0; i < row; i++) {
        for(char j = 0; j < column; j++) {
            printf("%d ", data_out[i][j]);
        }
        printf("\n");
    }
}

// TODO: add mat_trans().
// 2D matrix input but in the form of 1D.
void matmul_2D_1(void) {
    char row = 2, column = 2;
    int a_1D[4] =  {1, 2, 3, 4};
    int b_1D[4] =  {1, 2, 3, 4};

    int a_2D[2][2];
    int b_2D[2][2];
    int c_2D[2][2] = {0, 0, 0, 0};

    mat_trans(a_1D, a_2D, 2, 2);
    mat_trans(b_1D, b_2D, 2, 2);

    // Calculate multiplication of 2D matrices.
    for(char i = 0; i < 2; i++) {
        for(char j = 0; j < 2; j++) {
            for(char k = 0; k < 2; k++) {
                c_2D[i][j] += a_2D[i][k] * b_2D[k][j];
            }
        }
    }

    for(char i = 0; i < 2; i++) {
        for(char j = 0; j < 2; j++) {
            printf("%d ", c_2D[i][j]);
        }
        printf("\n");
    }
}