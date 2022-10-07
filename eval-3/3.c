#include <stdio.h>

char *find_string(char *string, char *search_pattern) {
  int i = 0;
  while (string[i] != '\0') {
    int j = 0;
    while (string[i + j] == search_pattern[j]) {
      if (search_pattern[j + 1] == '\0') {
        return string + i;
      }
      j++;
    }
    i++;
  }
  return string + i;
}

int main() {
  char *string = "hello I am a string";
  char *search_pattern = "I am a string";
  printf("%s, %s: %s\n", string, search_pattern,
         find_string(string, search_pattern));

  string = "I do not contain the search pattern";
  search_pattern = "not in string";
  printf("%s, %s: %s\n", string, search_pattern,
         find_string(string, search_pattern));

  string = "shorter than search pattern";
  search_pattern = "I am much much much longer than the string";
  printf("%s, %s: %s\n", string, search_pattern,
         find_string(string, search_pattern));
}
