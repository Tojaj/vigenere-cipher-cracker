#ifndef VCC_CIPHERTEXT_H_
#define VCC_CIPHERTEXT_H_

#include <string>
#include <memory>

#include "types.h"
#include "util.h"
#include "analysissuits.h"

static const unsigned long MAX_ANALYZED_INPUT_LEN = 150000;

class CipherText {
 public:
  CipherText(std::string &text, VigenereStreamAnalysis *stats):
    ciphertext_(text), stats_(stats) {};
  ~CipherText();
  std::string ciphertext() const;
  size_t length() const;
  size_t length(unsigned int key_length, unsigned int substring_index) const;
  LAlphabet frequencies();
  LAlphabet frequencies(unsigned int key_length, unsigned int substring_index);
  VigenereStreamAnalysis *stats();

 protected:
  std::string ciphertext_;
  VigenereStreamAnalysis *stats_;

 private:
  DISALLOW_COPY_AND_ASSIGN(CipherText);
};

class CipherTextFactory {
 public:
  static CipherText *CipherTextFromStdin();
  //static CipherText *CipherTextFromFilename(const char *filename);
  //static CipherText *CipherTextFromFd(int fd);
  //static CipherText *CipherTextFromString(string &ciphertext);
};

#endif  // VCC_CIPHERTEXT_H_
