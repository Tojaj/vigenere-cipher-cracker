#ifndef VCC_CRACKER_H_
#define VCC_CRACKER_H_

#include <string>

#include "types.h"
#include "ciphertext.h"

class VigenereCracker {
 public:
  static std::string crackit(CipherText *text, size_t key_len);
};

#endif  // VCC_CRACKER_H_
