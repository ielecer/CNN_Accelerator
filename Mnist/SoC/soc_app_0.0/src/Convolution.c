#include "Convolution.h"

void RunConv(XConv *InstancePtr,unsigned int CHin,unsigned int Hin,unsigned int Win,unsigned int CHout,
		unsigned int Kx,unsigned int Ky,unsigned int Sx,unsigned int Sy,unsigned int mode,unsigned int relu_en,
		float feature_in[],float W[],float bias[],float feature_out[])
{
	XConv_Set_CHin_V(InstancePtr,CHin);
	XConv_Set_Hin_V(InstancePtr,Hin);
	XConv_Set_Win_V(InstancePtr,Win);
	XConv_Set_CHout_V(InstancePtr,CHout);
	XConv_Set_Kx_V(InstancePtr,Kx);
	XConv_Set_Ky_V(InstancePtr,Ky);
	XConv_Set_Sx_V(InstancePtr,Sx);
	XConv_Set_Sy_V(InstancePtr,Sy);
	XConv_Set_mode_V(InstancePtr,mode);
	XConv_Set_relu_en_V(InstancePtr,relu_en);
	XConv_Set_feature_in(InstancePtr,(unsigned int)feature_in);
	XConv_Set_W(InstancePtr,(unsigned int)W);
	XConv_Set_bias(InstancePtr,(unsigned int)bias);
	XConv_Set_feature_out(InstancePtr,(unsigned int)feature_out);

	XConv_Start(InstancePtr);
	while(!XConv_IsDone(InstancePtr));
}

void RunConv_soft(unsigned int CHin,unsigned int Hin,unsigned int Win,unsigned int CHout,
		unsigned int Kx,unsigned int Ky,unsigned int Sx,unsigned int Sy,unsigned int mode,unsigned int relu_en,
		float feature_in[],float W[],float bias[],float feature_out[])
{
	int out_width;
    int out_height;

    int pad_x,pad_y;
	if(mode==0)
	{
		pad_x=0;pad_y=0;
	}
	else
	{
		pad_x=(Kx-1)/2;pad_y=(Ky-1)/2;
	}

    out_width=((Win+2*pad_x-Kx)/Sx+1);
    out_height=((Hin+2*pad_y-Ky)/Sy+1);

	//printf("Conv:out_width=%d,out_height=%d\n",out_width,out_height);

	for(int i=0;i<CHout;i++)
		for(int j=0;j<out_height;j++)
			for(int k=0;k<out_width;k++)
			{
				float result=bias[i];
				for(int ki=0;ki<Kx;ki++)
					for(int kj=0;kj<Ky;kj++)
						for(int chi=0;chi<CHin;chi++)
						{
							float data;
							int axis_h=Sy*j+kj-pad_y;
							int axis_w=Sx*k+ki-pad_x;
							if( (axis_h<0) || (axis_h>=Hin) || (axis_w<0) || (axis_w>=Win) )//padding 0
								data=0;
							else
								data=feature_in[axis_h*CHin*Win+axis_w*CHin+chi];
							result+=data*W[kj*CHout*CHin*Kx+ki*CHout*CHin+chi*CHout+i];
						}
				if(relu_en && result<0)
					result=0;
				feature_out[j*CHout*out_width+k*CHout+i]=result;
			}
}
