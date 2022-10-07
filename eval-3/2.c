#include <stdio.h>
#include <stdlib.h>

// **results_a/**results_b are pointers to pointers to the results arrays
// on run, the pointer will be modified to point at the result array, the
// function will return the size of the result array, which can be
// interpreted as the number of pairs found.
int divisors(int *array, int length, int **results_a, int **results_b) {
  int results_count = 0;
  int *results_a_temp = calloc(sizeof(int), sizeof(int));
  int *results_b_temp = calloc(sizeof(int), sizeof(int));

  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length; j++) {
      if (i == j) {
        continue;
      }

      if (array[j] % array[i] == 0) {
        int duplicate = 0;
        for (int k = 0; k < results_count; k++) {
          if (results_a_temp[i] == array[i] && results_b_temp[i] == array[j]) {
            duplicate = 1;
          }
        }
        if (duplicate) {
          continue;
        }

        results_count++;
        if (results_count != 1) {
          results_a_temp = realloc(results_a_temp, results_count * sizeof(int));
          results_b_temp = realloc(results_b_temp, results_count * sizeof(int));
        }

        results_a_temp[results_count - 1] = array[i];
        results_b_temp[results_count - 1] = array[j];
      }
    }
  }

  *results_a = realloc(results_a_temp, results_count * sizeof(int));
  *results_b = realloc(results_b_temp, results_count * sizeof(int));
  return results_count;
}

int main() {
  int array[] = {5, 10, 8, 2, 9, 3, 21, 11, 13};
  int *results_a, *results_b;
  int results_length = divisors(array, 9, &results_a, &results_b);
  for (int i = 0; i < results_length; i++) {
    printf("%d, %d\n", results_a[i], results_b[i]);
  }
}
