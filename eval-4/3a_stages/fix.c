#include <stdio.h>

int f(int x, int y) {
  if (y == 0) { // so that 0^0 = 1
    return 1;
  }

  if (x == 0) {
    return 0;
  }

  int r = 1;
  while (y > 1) {
    if (y % 2 == 1) {
      r = x * r;
    }
    x = x * x;
    y = y / 2;
  }
  return r * x;
}

int main() {
  printf("| x | y | f(x, y)\n");
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 4; y++) {
      printf("| %d | %d | %d\n", x, y, f(x, y));
    }
  }
}
