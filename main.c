#include <stdio.h>

struct TYPE_ANY {
  union {
    struct TYPE_ONE {
      float x;
      float y;
    } TYPE_ONE;
    struct TYPE_TWO {
      unsigned char z;
      unsigned char w;
    } TYPE_TWO;
  };
  int type;
}; enum {
  TYPE_ONE,
  TYPE_TWO,
};

int main() {
  struct TYPE_ANY a = {
    #define $ TYPE_ONE
    .type = $,
    .$.x = -1,
    .$.y =  4,
  };

  printf("a is TYPE_ONE? %d\n", a.type == TYPE_ONE);
  printf("a is TYPE_TWO? %d\n", a.type == TYPE_TWO);

  if (a.type == TYPE_ONE) {
    struct TYPE_ONE * a_as_one = &a;

    a_as_one->x =  8.15f;
    a_as_one->y = 16.23f;

    printf("a_as_one->x: %f\n", a_as_one->x);
    printf("a_as_one->y: %f\n", a_as_one->y);
  }

  struct TYPE_TWO * a_as_two = a.type == TYPE_TWO ? &a : 0xDEAD;

  a_as_two->w = 42;

  printf("a_as_two->z: %d\n", a_as_two->z);
  printf("a_as_two->w: %d\n", a_as_two->w);
}
