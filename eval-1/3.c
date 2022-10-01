// good luck
#include <stdio.h>
#include <math.h>
typedef int I;
#define P printf
#define R return
#define W while(1)
#define F(i,s,e) for(I i=s;i<e;i++)
I powers(I n){I r=0,b=2;W{I a=(I)(log(n-1)/log(b))-1;if(a<=0)R(r);r+=a;b++;}}
main(){F(n,2,30){P("%d: %d\n",n,powers(n));}}
