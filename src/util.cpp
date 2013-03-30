#include "util.h"

size_t
binary_gcd(size_t u, size_t v)
{
  // Algorithm taken from:
  // http://en.wikipedia.org/wiki/Binary_GCD_algorithm

  int shift;

  /* GCD(0,v) == v; GCD(u,0) == u, GCD(0,0) == 0 */
  if (u == 0) return v;
  if (v == 0) return u;

  /* Let shift := lg K, where K is the greatest power of 2
        dividing both u and v. */
  for (shift = 0; ((u | v) & 1) == 0; ++shift) {
    u >>= 1;
    v >>= 1;
  }

  while ((u & 1) == 0)
    u >>= 1;

  /* From here on, u is always odd. */
  do {
    /* remove all factors of 2 in v -- they are not common */
    /*   note: v is not zero, so while will terminate */
    while ((v & 1) == 0)  /* Loop X */
      v >>= 1;

     /* Now u and v are both odd. Swap if necessary so u <= v,
        then set v = v - u (which is even). For bignums, the
        swapping is just pointer movement, and the subtraction
        can be done in-place. */
    if (u > v) {
      unsigned int t = v; v = u; u = t;}  // Swap u and v.
    v = v - u;                       // Here v >= u.
    } while (v != 0);

  /* restore common factors of 2 */
  return u << shift;
}

size_t
distances_gcd(const Distances &distances)
{
  if (distances.size() == 0) return 0;
  if (distances.size() == 1) return distances[0];

  size_t prev = binary_gcd(distances[0], distances[1]);
  for (size_t x = 2; x < distances.size(); x++)
    prev = binary_gcd(prev, distances[x]);
  return prev;
}

size_t
index_distances_gcd(const NgramIndexes &indexes)
{
  Distances distances;
  // Transform vector of indexes into the vector of distances
  for (size_t x=0; x < (indexes.size() - 1); x++)
    for (size_t y=x+1; y < indexes.size(); y++)
      distances.push_back(indexes[y] - indexes[x]);
  return distances_gcd(distances);
}
