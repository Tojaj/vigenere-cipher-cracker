#ifndef VCC_NGRAMCOUNTER_H_
#define VCC_NGRAMCOUNTER_H_

#include <string>

#include "types.h"

const static int NGRAMMAPS = 5;

class NgramCounter {
 public:
  NgramCounter();
  // Process another text letter
  void put(char letter);
  // Try to find ngrams with len >3 (original text needed)
  void find_longer_ngrams(std::string &text);
  // Print whole content of current ngrammap
  void print_content();
  // Get ngrammap
  NgramMap *ngrammap(int id);

 protected:
  // Remove all ngrams with only one occurence
  void cleanup(NgramMap &map);

  NgramMap ngrammaps_[NGRAMMAPS]; // 0 - 3grams, 1 - 4grams, ...
  char trigram[4];
  size_t count;
};

#endif  // VCC_NGRAMCOUNTER_H_
