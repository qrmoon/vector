#ifndef VECTOR_H
#define VECTOR_H

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
  (vec).size = 0; \
  (vec).length = 0; \
  (vec).data = malloc((++(vec).size)*sizeof(*(vec).data)); \
  (vec).log_growth = true; \
  (vec).auto_shrink = false; \
}

#define vec_push(vec, v) { \
  size_t size = (vec).size; \
  if ((vec).length + 1 > size) { \
    if ((vec).log_growth) \
      size *= 2; \
    else size++; \
  } \
  void *ptr = (vec).data; \
  if (size != (vec).size) \
    ptr = realloc((vec).data, size * sizeof(*(vec).data)); \
  if (ptr) { \
    (vec).data = ptr; \
    (vec).size = size; \
    (vec).data[(vec).length++] = v; \
  } \
}

#define vec_insert(vec, i, v) { \
  size_t size = (vec).size; \
  if ((vec).length + 1 > size) { \
    if ((vec).log_growth) \
      size *= 2; \
    else size++; \
  } \
  void *ptr = (vec).data; \
  if (size != (vec).size) \
    ptr = realloc((vec).data, size * sizeof(*(vec).data)); \
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
  size_t size = (vec).size; \
  if ((vec).log_growth && (vec).length <= size / 2) \
    size /= 2; \
  else if (!(vec).log_growth && (vec).length < size) \
    size--; \
  if ((vec).size != size) { \
    void *ptr = realloc((vec).data, size * sizeof(*(vec).data)); \
    if (ptr != NULL) { \
      (vec).data = ptr; \
      (vec).size = size; \
    } \
  } \
}

#define vec_free(vec) free((vec).data)

#endif
