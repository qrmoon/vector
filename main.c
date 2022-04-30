#include <stdio.h>
#include "vector.h"

int main() {
  vector(int) v;
  vinit(v);
  vpush(v, 1);
  printf("%d\n", vget(v, 0));

  vpush(v, 2);
  vpush(v, 3);
  vpopb(v);
  vshrink(v);
  printf("%d\n", vget(v, 1));
}
