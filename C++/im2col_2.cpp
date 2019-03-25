#include <stdio.h>
#include <stdlib.h>
void im2col_cpu(int* data_im, int channels, int height, int width,                         /////data_im,data_col改回去float 
                int ksize,  int* data_col)
{
   int c,h,w;
 
   int height_col = height- ksize  + 1;
   int width_col  =  width - ksize + 1;

   int channels_col = channels * ksize * ksize;
 
 

 for (c = 0; c < channels_col; ++c) {
	int w_offset = c % ksize;
	int h_offset = (c / ksize) % ksize;
	int c_im = c / ksize / ksize;
 

		 for (h = 0; h < height_col; ++h) {
		 for (w = 0; w < width_col; ++w) {
				int im_row = h_offset + h ;
				int im_col = w_offset + w ;
				int col_index = channels_col*(w+h*width_col)+c;                             /////////自己改的 
				data_col[col_index] = data_im[im_col + width*(im_row + height*c_im)];  
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
 
        int inputs = height * width * channels;
        data_im = (int*)malloc(inputs * sizeof(int));
        if (!data_im) {
                printf("malloc error\n");
                exit(EXIT_FAILURE);
        }
 
        out_w = width - ksize + 1;
        out_h = height- ksize  + 1;
        workspace_size = out_h * out_w * ksize * ksize * channels;
 
        data_col = (int*)malloc(workspace_size * sizeof(int));
        if (!data_col) {
                printf("malloc error\n");
                exit(EXIT_FAILURE);
        }
 
        //init image
        for (int i=0; i<inputs; i++) data_im[i] = i;
 
        im2col_cpu(data_im, channels, height, width, ksize,  data_col);
 
        printf("data_im:\n");
        for (int i=0; i<inputs; i++) {
                printf("%-3d", data_im[i]);
                //if( (i+1) % 4 == 0) printf("\n");
        }
 
        printf("\ndata_col:\n");
        for (int i=0; i<workspace_size; i++) {
                printf("%-3d", data_col[i]);
                //if( (i+1) % 4 == 0) printf("\n");
        }
        printf("\n");
 
        free(data_im);
        free(data_col);
 
        exit(EXIT_SUCCESS);
}

