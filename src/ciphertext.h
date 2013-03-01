#ifndef VCC_CIPHERTEXT_H_
#define VCC_CIPHERTEXT_H_

#include <string>
#include <memory>

#include "util.h"

class CipherText {
 public:
  explicit CipherText(std::string &text): ciphertext_(text) {};
  ~CipherText();
  std::string ciphertext();

 protected:
  std::string ciphertext_;

 private:
  DISALLOW_COPY_AND_ASSIGN(CipherText);
};

class CipherTextFactory {
  public:
    static CipherText *CipherTextFromStdin();
    static CipherText *CipherTextFromFilename(const char *filename);
    //static CipherText *CipherTextFromFd(int fd);
    //static CipherText *CipherTextFromString(string &ciphertext);
};

#endif  // VCC_CIPHERTEXT_H_
