#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <string.h>

#define vec_t(type) struct { \
  type *data; \
  int size; \
  int length; \
}

#define vec_init(vec) { \
  memset(&vec, 0, sizeof(vec)); \
  vec.data = malloc((++vec.size)*sizeof(*vec.data)); \
}

#define vec_push(vec, v) { \
  if (vec.size == vec.length) \
    vec.data = realloc(vec.data, (++vec.size)*sizeof(*vec.data)); \
  vec.data[vec.length++] = v; \
}

#define vec_pop(vec, i) { \
  if (i != vec.length-1) \
    memmove( \
      &vec.data[i], \
      &vec.data[i+1], \
      (vec.length-i-1)*sizeof(*vec.data) \
    ); \
  vec.length--; \
}

#define vec_popb(vec) vec_pop(vec, vec.length-1)

#define vec_get(vec, i) vec.data[i]

#define vec_shrink(vec) { \
  void *ptr = realloc(vec.data, vec.length*sizeof(*vec.data)); \
  if (ptr != NULL) vec.data = ptr; \
  vec.size = vec.length; \
}

#define vec_free(vec) free(vec.data)

#endif
