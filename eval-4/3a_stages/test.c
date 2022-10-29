#include <stdio.h>

int f(int x, int y) {
  int r = 1;
  while (y > 1) {     // loop for floor(log2(y)) + 1 iterations
    if (y % 2 == 1) { // branches if y is odd
      r = x * r;      // then r is x^(number of odd numbers encountered)
    }
    x = x * x; // then x is 2^(floor(log2(y)) + 1)
    y = y / 2; // y is halved each iteration
  }
  return r * x; // r * x = x^(floor(log2(y)) + 1) * x^(number of odd numbers
                // encountered)
}

int main() {
  printf("| x | y | f(x, y)\n");
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 4; y++) {
      printf("| %d | %d | %d\n", x, y, f(x, y));
    }
  }
}
