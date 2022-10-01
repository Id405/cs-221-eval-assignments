#include <stdio.h>
int not(int n) {
    return (n&0)==n;
}

main() {
    return not(1337);
}
