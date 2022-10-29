#include <stdio.h>
#include <stdlib.h>

struct point2d {
  int x;
  int y;
};

int main(int argc, char *argv[]) {
  int m = atoi(argv[1]);
  struct point2d *p = malloc(sizeof(struct point2d));
  p->x = atoi(argv[2]);
  p->y = atoi(argv[3]);
  struct point2d *z = malloc(sizeof(struct point2d));
  z->x = 0;
  // while we are here lets make the assumption that the intended variable was
  // p->y as this makes z mathematically the y intercept of a line crossing the
  // point p with the slope m.
  z->y = p->y - (m * p->x);
  printf("x coord: %d\n", z->x); // print z instead of p
  printf("y coord: %d\n", z->y);
  return 0;
}
