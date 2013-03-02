#ifndef VCC_CIPHERTEXT_H_
#define VCC_CIPHERTEXT_H_

#include <string>
#include <memory>

#include "types.h"
#include "util.h"

class CipherText {
 public:
  CipherText(std::string &text, LAlphabet stat):
    ciphertext_(text), letter_frequencies(stat) {};
  ~CipherText();
  std::string ciphertext() const;
  size_t length() const;
  size_t length(unsigned int key_length, unsigned int substring_index) const;
  LAlphabet frequencies();
  LAlphabet frequencies(unsigned int key_length, unsigned int substring_index);

 protected:
  std::string ciphertext_;
  LAlphabet letter_frequencies;

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
