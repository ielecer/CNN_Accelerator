#include "Pool.h"

void RunPool_soft(unsigned int CHin,unsigned int Hin,unsigned int Win,
		unsigned int Kx,unsigned int Ky,unsigned int mode,
		float feature_in[],float feature_out[]
	)//mode: 0:MEAN, 1:MIN, 2:MAX
{
	unsigned int Hout,Wout;
	Wout=Win/Kx;
	Hout=Hin/Ky;

	for(int c=0;c<CHin;c++)
		for(int i=0;i<Hout;i++)
			for(int j=0;j<Wout;j++)
			{
				float sum;
				if(mode==0)
					sum=0;
				else
					if(mode==1)
						sum=99999999999999999;
					else
						sum=-99999999999999999;
				for(int ii=0;ii<Ky;ii++)
					for(int jj=0;jj<Kx;jj++)
					{
						int h=i*Ky+ii;
						int w=j*Kx+jj;
						switch(mode)
						{
							case 0:{sum+=feature_in[h*CHin*Win+w*CHin+c];break;}
							case 1:{sum=min(sum,feature_in[h*CHin*Win+w*CHin+c]);break;}
							case 2:{sum=max(sum,feature_in[h*CHin*Win+w*CHin+c]);break;}
							default:break;
						}
					}
				if(mode==0)
					sum=sum/(Kx*Ky);
				feature_out[i*Wout*CHin+j*CHin+c]=sum;
			}
}
