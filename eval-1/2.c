// the divine teachings of the sacred text (https://code.jsoftware.com/wiki/Essays/Incunabulum) will reveal all truths.
#include <stdio.h>
typedef int I;
#define P printf
#define S sizeof
#define R return
#define N continue
#define B break
#define F(i,s,e) for(I i=s;i<e;i++)
I *find_divisor(I a[],I l){I r[2];F(i,0,l){F(j,0,l){if(i==j)N;
 if(a[i]%a[j]==0)R(I[]){a[j],a[i]};}}R(I[]){0,0};}
main(){I a[]={3,8,12,20};I* r=find_divisor(a,S(a)/S(*a));P("%d,%d\n",r[0],r[1]);}
