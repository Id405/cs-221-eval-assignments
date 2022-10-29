#include <stdio.h>
#include <stdlib.h>

struct point2d {
  int x;
  int y;
};

int main(int argc, char *argv[]) {
  if (argc < 3) { // validate we have the proper number of arguments supplied
    printf("provide three arguments in the format: slope, x, y");
    return 0;
  }
  int m = atoi(argv[1]);
  struct point2d *p = malloc(sizeof(struct point2d));
  p->x = atoi(argv[2]);
  p->y = atoi(argv[3]);
  struct point2d *z = malloc(sizeof(struct point2d));
  z->x = 0;
  z->y = p->y - (m * p->x);
  printf("x coord: %d\n", z->x);
  printf("y coord: %d\n", z->y);
  free(p); // free p and z
  free(z);
  return 0;
}
