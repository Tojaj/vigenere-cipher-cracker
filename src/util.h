#ifndef VCC_UTIL_H_
#define VCC_UTIL_H_

#include <stdlib.h>

#include "types.h"

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

static inline int
letter_index(char x)
{
  if (x >= 'A' && x <= 'Z')
    return (x - 'A');
  if (x >= 'a' && x <= 'z')
    return (x - 'a');
  return -1;
};

size_t distances_gcd(const Distances &distances);
size_t index_distances_gcd(const NgramIndexes &indexes);

#endif  // VCC_UTIL_H_
