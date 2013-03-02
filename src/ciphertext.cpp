#include "ciphertext.h"

#include <assert.h>
#include <string>
#include <fstream>
#include <iostream>

#include "types.h"
#include "util.h"

CipherText::~CipherText()
{
  ;
}

std::string
CipherText::ciphertext() const
{
  return ciphertext_;
}

size_t
CipherText::length() const
{
  return ciphertext_.length();
}

size_t
CipherText::length(unsigned int key_length, unsigned int substring_index) const
{
  assert(key_length == 0 || substring_index < key_length);

  size_t len  = length() / key_length;
  size_t rest = length() % key_length;
  printf("(%u %u) [%lu] %lu | %lu\n", key_length, substring_index, ciphertext_.length(), len, rest);
  if (rest > 0 && substring_index < rest) len++;
  return len;
}

LAlphabet
CipherText::frequencies()
{
  return letter_frequencies;
}

LAlphabet
CipherText::frequencies(unsigned int key_length, unsigned int substring_index)
{
  assert(key_length == 0 || substring_index < key_length);

  LAlphabet alphabet;

  if (key_length == 0) key_length = 1;

  // Count letter frequencies
  alphabet.fill(0);
  for (size_t x=substring_index; x < ciphertext_.length(); x += key_length) {
    int letter = letter_index(ciphertext_[x]);
    if (letter != -1)
      alphabet[letter] += 1;
  }

  return alphabet;
}

CipherText *
CipherTextFactory::CipherTextFromStdin()
{
  char c;
  std::string text;
  LAlphabet stat;

  stat.fill(c);
  while (std::cin.get(c)) {
    int index = letter_index(c);
    if (index == -1)
      continue;

    text.push_back(c);

    // Count letter statistic
    stat[index] += 1;

    // Ngram finding
    // TODO

  }

  // Construct a CipherText object and return it
  return new CipherText(text, stat);
}
