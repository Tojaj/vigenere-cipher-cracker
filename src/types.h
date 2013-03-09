#ifndef VCC_TYPES_H_
#define VCC_TYPES_H_

#include <string>
#include <vector>
#include <map>
#include <array>

static const size_t ALPHABET_LEN = 26;

typedef std::array<float, ALPHABET_LEN> FAlphabet;
typedef std::array<long,  ALPHABET_LEN> LAlphabet;

static const float LETTER_FREQUENCY[] = {
    8.167,  // a
    1.492,  // b
    2.782,  // c
    4.253,  // d
    12.702, // e
    2.228,  // f
    2.015,  // g
    6.094,  // h
    6.966,  // i
    0.153,  // j
    0.772,  // k
    4.025,  // l
    2.406,  // m
    6.749,  // n
    7.507,  // o
    1.929,  // p
    0.095,  // q
    5.987,  // r
    6.327,  // s
    9.056,  // t
    2.758,  // u
    0.978,  // v
    2.360,  // w
    0.150,  // x
    1.974,  // y
    0.074,  // z
  };

typedef std::vector<size_t> Distances;
typedef std::vector<size_t> PossibleLengths;
typedef std::vector<size_t> NgramLengths;
typedef std::vector<size_t> NgramIndexes;
typedef std::map<std::string, NgramIndexes> NgramMap;

#endif  // VCC_TYPES_H_
