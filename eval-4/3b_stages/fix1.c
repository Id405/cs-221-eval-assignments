#include <stdio.h> // NEW: include required libraries
#include <stdlib.h>

struct point2d {
  int x;
  int y;
};

int main(int argc,
         char *argv[]) { // NEW: change type of argc to int, and argv to *char[]
  int m = atoi(argv[1]);
  struct point2d *p = malloc(sizeof(struct point2d));
  p->x = atoi(argv[2]);
  p->y = atoi(argv[3]);
  struct point2d *z = malloc(sizeof(struct point2d));
  z->x = 0;
  z->y = z->y - (m * p->x);
  printf("x coord: %d\n", p->x);
  printf("y coord: %d\n", p->y);
  return 0;
}
