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

  LAlphabet frequencies;
  frequencies = ciphertext->frequencies();
  printf("Letter frequencies:\n");
  for (int x=0; x < ALPHABET_LEN; x++)
      printf(" %c) %ld\n", (x+'A'), frequencies[x]);

  return EXIT_SUCCESS;
}
