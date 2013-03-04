#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "ciphertext.h"

int
main()
{
  CipherText *ciphertext;
  printf("Hello world!\n");
  ciphertext = CipherTextFactory::CipherTextFromStdin();
  std::cout << ciphertext->ciphertext();

  LAlphabet frequencies;
  frequencies = ciphertext->frequencies();
  for (int x=0; x < ALPHABET_LEN; x++)
      printf(" %c) %ld\n", (x+'A'), frequencies[x]);

  return EXIT_SUCCESS;
}
