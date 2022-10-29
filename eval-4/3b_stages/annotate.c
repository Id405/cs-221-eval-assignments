#include <stdio.h>
#include <stdlib.h>

struct point2d {
  int x;
  int y;
};

int main(int argc, char *argv[]) {
  int m = atoi(argv[1]); // store the first argument passed to the program as an
                         // int in the variable "m"
  struct point2d *p = malloc(sizeof(struct point2d)); // allocate a point2d "p"
  p->x = atoi(
      argv[2]); // set the x coordinate of the point2d to the second argument
  p->y = atoi(
      argv[3]); // set the y coordinate of the point2d to the third argument
  struct point2d *z =
      malloc(sizeof(struct point2d)); // allocate another point2d "z"
  z->x = 0;                           // set the x coordinate of z to 0
  // set the y coordinate of z to be itself subtracted
  // from m multiplied by the x coordinate of "p".
  // however, before this, the y coordinate of z is uninitialized and, z is left
  // unused in the rest of the program
  z->y = z->y - (m * p->x);
  printf("x coord: %d\n", p->x); // print the x and y coordinates of p
  printf("y coord: %d\n", p->y);
  return 0; // note: p and z are not freed
}
