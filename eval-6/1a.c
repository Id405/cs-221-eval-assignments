#include <stdint.h>
#include <stdio.h>

// the tail call modified function
uint32_t decaying_sum_t(uint16_t *values, uint16_t length, uint16_t decay,
                        uint32_t value) {
  if (length == 0) {
    return value;
  }
  return decaying_sum_t(values, length - 1, decay,
                        value / decay + values[length - 1]);
}

uint32_t decaying_sum_tail_recursive(uint16_t *values, uint16_t length,
                                     uint16_t decay) {
  return decaying_sum_t(values, length, decay, 0);
}

// the original function for testing purposes
uint32_t decaying_sum(uint16_t *values, uint16_t length, uint16_t decay) {
  if (length <= 0) {
    return 0;
  }
  uint32_t rest = decaying_sum(&values[1], length - 1, decay);
  uint32_t decayed = rest / decay;
  return values[0] + decayed;
}

// test to see if the functions produce the same output on a set of values
int main() {
  uint16_t values[6] = {27, 3, 13, 95, 0, 32};
  uint16_t length = 6;
  uint16_t decay = 5;

  printf("%d\n", decaying_sum(values, length, decay));
  printf("%d\n", decaying_sum_tail_recursive(values, length, decay));
}
