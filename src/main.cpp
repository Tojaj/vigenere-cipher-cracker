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

  printf("%lu\n", ciphertext->length(3,0));
  printf("%lu\n", ciphertext->length(3,1));
  printf("%lu\n", ciphertext->length(3,2));

  return EXIT_SUCCESS;
}
