#include <cmath>

#include "cracker.h"

static const float EN_COINCIDENCE = 0.065;

static inline size_t
detect_alphabet_shift(LAlphabet freqs, size_t len)
{
  float the_best_deviation = 100.0;
  size_t the_best_shift = 0;

  for (size_t shift=0; shift < ALPHABET_LEN; shift++) {
    float deviation, sum = 0.0;
    for (size_t letter=0; letter < ALPHABET_LEN; letter++)
      sum += ((LETTER_FREQUENCY[letter] / 100.0) * freqs[(letter+shift) % ALPHABET_LEN]) / len;
    deviation = std::abs((float) EN_COINCIDENCE - sum);
    if (deviation < the_best_deviation) {
      the_best_deviation = deviation;
      the_best_shift = shift;
    }
  }

  return the_best_shift;
}

std::string
VigenereCracker::crackit(CipherText *text, size_t key_len)
{
  std::string key;
  for (size_t n=0; n < key_len; n++) {
    size_t len = text->length(key_len, n);
    LAlphabet freqs = text->frequencies(key_len, n);
    key.push_back((char) detect_alphabet_shift(freqs, len) + 'a');
  }

  return key;
}
