#include <stdio.h>
#include <malloc.h>

#define	M	20
#define	Time	1
#define	dx	0.1
#define	dt	0.01
#define	D 	0.1

void DHB2(float *T, float *dT) {
	int i;
	float c,l,r;
	for ( i = 0 ; i < M ; i++ ){
	c = *(T+i);
	l = (i==0) ? 100 : *(T+i-1);
	r = (i==M-1) ? 25 : *(T+i+1);
	*(dT+i) = D*(l-2*c+r)/(dx*dx);
	}
}

int main()
{
	// Khai bao bien
	int i;
	float t=0,*T, *dT;
	T = (float *) malloc ((M)*sizeof(float));
	dT= (float *) malloc ((M)*sizeof(float));
	// Khoi tao
	for (i=0; i<M; i++) *(T+i) = 25.0;
	
		while (t<Time)
		{
			DHB2(T, dT);
			for ( i = 0 ; i < M ; i++ )
			*(T+i) = *(T+i) + *(dT+i)*dt;
			t=t+dt;
		}
	
	

	for (i=0; i<M; i++) printf("%f \n",*(T+i));

	return 0;
}
