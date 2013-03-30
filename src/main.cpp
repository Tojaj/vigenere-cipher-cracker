#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "ciphertext.h"
#include "analysissuits.h"
#include "cracker.h"

#include "util.h"

int
main()
{
  CipherText *ciphertext;
  ciphertext = CipherTextFactory::CipherTextFromStdin();
  VigenereStreamAnalysis *stats = ciphertext->stats();

  LAlphabet frequencies;
  frequencies = ciphertext->frequencies();

  float friedman = VigenereStatAnalysis::friedman_test(frequencies);
  PossibleLengths lens = VigenereStatAnalysis::kasisky_test(stats->ngramcounter_);
  size_t selected_len = lens.front();
  std::string key = VigenereCracker::crackit(ciphertext, selected_len);
  printf("%f;%zu;%zu;%s\n", friedman, selected_len, selected_len, key.c_str());

  delete ciphertext;

  return EXIT_SUCCESS;
}
