#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <string.h>

#define vector(type) struct { \
  type *data; \
  int size; \
  int length; \
}

#define vinit(vec) { \
  memset(&vec, 0, sizeof(vec)); \
  vec.data = malloc((++vec.size)*sizeof(*vec.data)); \
}

#define vpush(vec, v) { \
  if (vec.size == vec.length) \
    vec.data = realloc(vec.data, ++vec.size); \
  vec.data[vec.length++] = v; \
}

#define vpop(vec, i) { \
  if (i != vec.length-1) \
    memmove( \
      &vec.data[i], \
      &vec.data[i+1], \
      (vec.length-i-1)*sizeof(*vec.data) \
    ); \
  vec.length--; \
}

#define vpopb(vec) vpop(vec, vec.length-1)

#define vget(vec, i) vec.data[i]

#define vshrink(vec) { \
  void *ptr = realloc(vec.data, vec.length*sizeof(*vec.data)); \
  if (ptr != NULL) vec.data = ptr; \
  vec.size = vec.length; \
}

#define vfree(vec) free(vec.data)

#endif
