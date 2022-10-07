#include <stdio.h>
#include <stdlib.h>

char *copy_substring(char *string, int start, int end) {
  char *substring = malloc((end - start) * sizeof(char));
  for (int i = start; i < end; i++) {
    substring[i - start] = string[i];
  }
  return substring;
}

int main() {
  char *string = "technology should have stayed in the dark age, oh to be a "
                 "hunter-gatherer and die of dysentry!";
  int start = 4;
  int end = 15;
  printf("%s", copy_substring(string, start, end));
}
