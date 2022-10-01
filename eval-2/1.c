#include <stdio.h>
int conditional(int x, int y, int z) {
    return (x==0)*z | (x!=0)*y;
}

int main() {
    return conditional(1,0,139);
}
