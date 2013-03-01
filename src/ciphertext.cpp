#include "ciphertext.h"

#include <string>
#include <fstream>
#include <iostream>

#include "types.h"

CipherText::~CipherText()
{
  ;
}

std::string
CipherText::ciphertext()
{
  return this->ciphertext_;
}

CipherText *
CipherTextFactory::CipherTextFromFilename(const char *filename)
{
  std::ifstream in(filename, std::ios::in);
  std::string text;

  if (!in)  // Something went wrong
    return NULL;

  // Load the entire file content into memory
  in.seekg(0, std::ios::end);
  text.resize(in.tellg());
  in.seekg(0, std::ios::beg);
  in.read(&text[0], text.size());
  in.close();

  // Construct a CipherText object and return it
  return new CipherText(text);
}

CipherText *
CipherTextFactory::CipherTextFromStdin()
{
  std::string text((std::istreambuf_iterator<char>(std::cin)),
                    std::istreambuf_iterator<char>());

  // Construct a CipherText object and return it
  return new CipherText(text);
}
