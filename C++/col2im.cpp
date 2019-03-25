#include <stdio.h>
#include <stdlib.h>

void col2im_cpu(int* data_col,
         int channels,  int height,  int width,
         int ksize,   int* data_im) 
{
    int c,h,w;
    int height_col = height - ksize + 1;
    int width_col = width  - ksize + 1;

    int channels_col = channels * ksize * ksize;
    for (c = 0; c < channels_col; ++c) {
        int w_offset = c % ksize;
        int h_offset = (c / ksize) % ksize;
        int c_im = c / ksize / ksize;
        for (h = 0; h < height_col; ++h) {
            for (w = 0; w < width_col; ++w) {
                int im_row = h_offset + h;
                int im_col = w_offset + w ;
                int col_index = channels_col*(w+h*width_col)+c;
                data_im[im_col + width*(im_row + height*c_im)] += data_col[col_index];
            }
        }
    }
}


int main(int argc, char* argv[]) {
        int *data_im=NULL;
        int *data_col=NULL;
        int channels=3,height=3,width=3;
        int ksize=2;
        int out_w,out_h;
        int workspace_size;
 
        out_w = width - ksize + 1;
        out_h = height- ksize  + 1;
        workspace_size = out_h * out_w * ksize * ksize * channels;
        
        
        int inputs = height * width * channels;
       
        
        data_im = (int*)malloc(inputs * sizeof(int));
        if (!data_im) {
                printf("malloc error\n");
                exit(EXIT_FAILURE);
        }
 

 
        data_col = (int*)malloc(workspace_size * sizeof(int));
        if (!data_col) {
                printf("malloc error\n");
                exit(EXIT_FAILURE);
        }
 
        //init image
        //for (int i=0; i<inputs; i++) data_im[i] = i;
        //data_col[0] = {0  ,1 , 3  ,4  ,9,  10 ,12, 13,18 ,19 ,21 ,22, 1 , 2 , 4,  5 , 10 ,11 ,13 ,14 ,19, 20 ,22 ,23 ,3 , 4,  6,  7 , 12 ,13 ,15 ,16, 21, 22 ,24 ,25 ,4  ,5,  7  ,8 , 13 ,14 ,16 ,17 ,22, 23, 25, 26};
        for (int i=0; i<inputs; i++) data_im[i] = 0;
		data_col[0] = 0;
        data_col[1] = 1;
        data_col[2] = 3;
        data_col[3] = 4;
        data_col[4] = 9;
        data_col[5] = 10;
        data_col[6] = 12;
        data_col[7] = 13;
        data_col[8] = 18;
        data_col[9] = 19;
        data_col[10] = 21;
        data_col[11] = 22;
		    data_col[12] = 1;
		    data_col[13] = 2;
		    data_col[14] = 4;
		    data_col[15] = 5;
		    data_col[16] = 10;
		    data_col[17] = 11;
		    data_col[18] = 13;
		    data_col[19] =14;
		    data_col[20] = 19;
	        data_col[21] = 20;
	        data_col[22] = 22;
	        data_col[23] = 23;
	            data_col[24] = 3;
			    data_col[25] = 4;
			    data_col[26] =6;
			    data_col[27] = 7;
			    data_col[28] = 12;
			    data_col[29] =13;
			    data_col[30] = 15;
		        data_col[31] = 16;
		        data_col[32] = 21;
		        data_col[33] = 22;
				data_col[34] = 24;
			    data_col[35] = 25;
			    
			    data_col[36] = 4;
			    data_col[37] = 5;
			    data_col[38] = 7;
			    data_col[39] =8;
			    data_col[40] = 13;
			    data_col[41] = 14;
			    data_col[42] = 16;
			    data_col[43] = 17;
			    data_col[44] = 22;
			    data_col[45] = 23;
			    data_col[46] = 25;
			    data_col[47] = 26;
			    
		col2im_cpu(data_col, channels, height, width, ksize,  data_im);
 
       
 
        printf("\ndata_col:\n");
        for (int i=0; i<workspace_size; i++) {
                printf("%-3d", data_col[i]);
                //if( (i+1) % 4 == 0) printf("\n");
        }
        printf("\n");
        
         printf("data_im:\n");
        for (int i=0; i<inputs; i++) {
                printf("%-3d", data_im[i]);
                //if( (i+1) % 4 == 0) printf("\n");
        }
 
        free(data_im);
        free(data_col);
 
        exit(EXIT_SUCCESS);
}













