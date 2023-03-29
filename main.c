#include <stdio.h>
#include "vector.h"

int main() {
  vec_t(int) v;
  vec_init(v);
  vec_push(v, 1);
  printf("%d\n", vec_get(v, 0));

  vec_push(v, 2);
  vec_push(v, 3);
  vec_popb(v);
  vec_shrink(v);
  vec_insert(v, 1, 10);
  printf("%d\n", vec_get(v, 1));
}
