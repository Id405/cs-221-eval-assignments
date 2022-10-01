// :^)
#include <stdio.h>
typedef int I;
#define R return
#define P printf
#define W while
#define F(i,s,e) for(I i=s;i<e;i++)
I f(I n){I p=0,c=1;W(n-->1){I t=p;p=c;c+=t;}R(c);}
main(){F(n,1,30){P("%d\n", f(n));}}
