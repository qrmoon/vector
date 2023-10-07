#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define vec_t(type) struct { \
  type *data; \
  size_t size; \
  size_t length; \
  bool log_growth; \
  bool auto_shrink; \
}

#define vec_init(vec) { \
  memset(&vec, 0, sizeof(vec)); \
  (vec).data = malloc((++(vec).size)*sizeof(*(vec).data)); \
  (vec).log_growth = true; \
  (vec).auto_shrink = true; \
}

#define vec_push(vec, v) { \
  size_t size = (vec).log_growth ? (vec).size * 2 : (vec).size + 1; \
  void *ptr = (vec).data; \
  if ((vec).size == (vec).length) \
    ptr = realloc((vec).data, size * sizeof(*(vec).data)); \
  if (ptr) { \
    (vec).data = ptr; \
    (vec).size = size; \
    (vec).data[(vec).length++] = v; \
  } \
}

#define vec_insert(vec, i, v) { \
  size_t size = (vec).log_growth ? (vec).size * 2 : (vec).size + 1; \
  void *ptr = (vec).data; \
  if ((vec).size == (vec).length) \
    ptr = realloc((vec).data, (++(vec).size)*sizeof(*(vec).data)); \
  if (ptr) { \
    (vec).data = ptr; \
    (vec).size = size; \
    memmove((vec).data+i+1, (vec).data+i, (vec).size-i); \
    (vec).data[i] = v; \
    (vec).length++; \
  } \
}

#define vec_pop(vec, i) { \
  if ((i) != (vec).length-1) \
    memmove( \
      &(vec).data[(i)], \
      &(vec).data[(i)+1], \
      ((vec).length-(i)-1)*sizeof(*(vec).data) \
    ); \
  (vec).length--; \
  if ((vec).auto_shrink) vec_shrink(vec); \
}

#define vec_popb(vec) vec_pop(vec, (vec).length-1)

#define vec_get(vec, i) (vec).data[i]

#define vec_shrink(vec) { \
  /* for logarithmic grows, use */ \
  /* the smallest multiple of 2 */ \
  /* larger than vec.length */ \
  size_t size = \
    (vec).log_growth ? (int)pow(2, log2(vec.length)) : (vec).length; \
  if ((vec).size != size) { \
    void *ptr = realloc((vec).data, size*sizeof(*(vec).data)); \
    if (ptr != NULL) { \
      (vec).data = ptr; \
      (vec).size = size; \
    } \
  } \
}

#define vec_free(vec) free((vec).data)

#endif
