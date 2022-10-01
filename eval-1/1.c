// witness the POWER and MIGHT of WHITNEYC
#include <stdio.h>
typedef char C;typedef int I;
#define P printf
#define S scanf
#define R return
#define F(i,s,e) for(I i=s;i<e;i++)
C *choose_mover(I b){R 200*((b+22)/23)<260*((b+29)/30)?"Alice":"Bob";}
main(){F(n,1,30){P("%d: %s\n", n, choose_mover(n));}}
