#ifndef VCC_ANALYSISSUITS_H_
#define VCC_ANALYSISSUITS_H_

#include "types.h"
#include "ngramcounter.h"

class VigenereStreamAnalysis {
 public:
  VigenereStreamAnalysis();
  // Process another text letter
  void put(char letter);
  // No more input - Calculate results
  void put_eof(std::string &text);
  LAlphabet letter_frequencies_;
  NgramCounter ngramcounter_;
};

class VigenereStatAnalysis {
 public:
  static float friedman_test(const LAlphabet letter_frequencies);
  static PossibleLengths kasisky_test(NgramCounter &ngramcounter);
};

#endif  // VCC_ANALYSISSUITS_H_
