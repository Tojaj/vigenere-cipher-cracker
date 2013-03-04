#ifndef VCC_NGRAMCOUNTER_H_
#define VCC_NGRAMCOUNTER_H_

#include <string>

#include "types.h"

class NgramCounter {
 public:
  NgramCounter();
  // Process another text letter
  void put(char letter);
  // Remove all ngrams with only one occurence
  void cleanup();
  // Try to find ngrams with len >3 (original text needed)
  void find_longer_ngrams();
  // Print whole content of current ngrammap
  void print_content();
  // Get ngrammap
  NgramMap ngrammap();

 protected:
  NgramMap ngrammap_;
  NgramMap ngrammap_4_;
  char trigram[4];
  size_t count;
};

#endif  // VCC_NGRAMCOUNTER_H_
