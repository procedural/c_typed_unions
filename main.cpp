#include <stdio.h>

struct StructTypeOne {
  float x;
  float y;
};

struct StructTypeTwo {
  size_t z[100000];
  size_t w;
};

enum StructType {
  StructTypeOne = 1,
  StructTypeTwo = 2,
};

struct StructTypeAny {
  union {
    struct StructTypeOne StructTypeOne;
    struct StructTypeTwo StructTypeTwo;
  };
  enum StructType type;
};

int main() {
  struct StructTypeAny a = {};
  a.type            = StructTypeOne;
  a.StructTypeOne.x =-1;
  a.StructTypeOne.y = 4;

  printf("a is StructTypeOne? %d\n", a.type == StructTypeOne);
  printf("a is StructTypeTwo? %d\n", a.type == StructTypeTwo);

  if (a.type == StructTypeOne) {
    struct StructTypeOne * a_as_one = (struct StructTypeOne *)&a;

    a_as_one->x =  8.15f;
    a_as_one->y = 16.23f;

    printf("a_as_one->x: %f\n", a_as_one->x);
    printf("a_as_one->y: %f\n", a_as_one->y);
  }

  struct StructTypeTwo * a_as_two = a.type == StructTypeTwo ? (struct StructTypeTwo *)&a : (struct StructTypeTwo *)(void *)0x101010101010;

  a_as_two->w = 42;

  printf("a_as_two->z: %d\n", a_as_two->z);
  printf("a_as_two->w: %d\n", a_as_two->w);
}