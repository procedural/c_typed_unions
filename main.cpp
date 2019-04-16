#include <stdio.h>

struct StructTypeAny {
  union {
    struct StructTypeOne {
      float x;
      float y;
    } StructTypeOne;
    struct StructTypeTwo {
      unsigned char z;
      unsigned char w;
    } StructTypeTwo;
  };
  int type;
};
enum {
  StructTypeOne = 0,
  StructTypeTwo = 1,
};

int main() {
  struct StructTypeAny a = {
    #define $ StructTypeOne
    .type = $,
    .$.x = -1,
    .$.y =  4,
  };

  printf("a is StructTypeOne? %d\n", a.type == StructTypeOne);
  printf("a is StructTypeTwo? %d\n", a.type == StructTypeTwo);

  if (a.type == StructTypeOne) {
    struct StructTypeOne * a_as_one = &a;

    a_as_one->x =  8.15f;
    a_as_one->y = 16.23f;

    printf("a_as_one->x: %f\n", a_as_one->x);
    printf("a_as_one->y: %f\n", a_as_one->y);
  }

  struct StructTypeTwo * a_as_two = a.type == StructTypeTwo ? &a : 0xBAD;

  a_as_two->w = 42;

  printf("a_as_two->z: %d\n", a_as_two->z);
  printf("a_as_two->w: %d\n", a_as_two->w);
}