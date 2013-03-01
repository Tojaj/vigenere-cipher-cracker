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
  return EXIT_SUCCESS;
}
