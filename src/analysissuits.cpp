#include <algorithm>
#include <vector>
#include <array>

#include "analysissuits.h"
#include "util.h"

VigenereStreamAnalysis::VigenereStreamAnalysis()
{
  letter_frequencies_.fill(0);
}

void
VigenereStreamAnalysis::put(char letter)
{
  // Count letter statistic
  letter_frequencies_[letter_index(letter)] += 1;
  // Ngram finding
  ngramcounter_.put(letter);
}

void
VigenereStreamAnalysis::put_eof(std::string &text)
{
  ngramcounter_.find_longer_ngrams(text);
}

float
VigenereStatAnalysis::friedman_test(const LAlphabet letter_frequencies) {
  // http://en.wikipedia.org/wiki/Vigenere_cipher#Friedman_test
  const float k_r = 1.0 / 26.0;
  const float k_p = 0.067;
  float k_o;
  long long sum = 0L;
  long long len = 0L;
  float denominator;

  for (size_t x=0; x < ALPHABET_LEN; x++) {
    len += letter_frequencies[x];
    sum += letter_frequencies[x] * (letter_frequencies[x] - 1);
//    printf (" Sum: %10lld - %c: %ld\n", sum, (x+'A'), letter_frequencies[x]);
  }
  denominator = len * (len - 1);
  k_o = sum / denominator;
//  printf("Denominator: %f\n", denominator);
//  printf("k_r: %f\n", k_r);
//  printf("k_p: %f\n", k_p);
//  printf("k_o: %f\n", k_o);

  return (k_p - k_r) / (k_o - k_r);
}

typedef std::array<size_t, 2> Occurence;
typedef std::vector<Occurence> Occurences;
//static bool sort_by_first_item(const Occurence &a, const Occurence &b) { return a[0] >= b[0]; };

struct occurence_cmp {
  bool operator ()(Occurence const& a, Occurence const& b) const {
    return a[0] < b[0];
  }
};

PossibleLengths
VigenereStatAnalysis::kasisky_test(NgramCounter &ngramcounter)
{
  PossibleLengths lengths;
  PossibleLengths::iterator lengths_it;
  size_t min_map = ((NGRAMMAPS - 2) > 0) ? NGRAMMAPS-2 : 0;
  size_t take_only_longer_than = 4;

  // Build vector of possible lengths
  // Try to build it from ngrams that are:
  //   - longer than others
  //   - have more than take_only_longer_than ocurrences
  while (1) {
    size_t current_map = NGRAMMAPS-1;
    while (current_map >= min_map && lengths.size() < 10) {
      NgramMap *ngm = ngramcounter.ngrammap(current_map);
      NgramMap::iterator it = ngm->begin();
      for (; it != ngm->end(); it++) {
        size_t gcd;
        if (it->second.size() <= take_only_longer_than)
          continue;
        gcd = index_distances_gcd(it->second);
//        for (size_t x = 0; x < it->second.size(); x++)
//          printf("%zu ", it->second[x]);
//        printf("[%zu]\n", gcd);
        lengths.push_back(gcd);
      }
      current_map--;
    }

    // Check if we have enought of lenghts
    if (lengths.size() < 10 && take_only_longer_than > 1) {
      --take_only_longer_than;
      min_map = (min_map > 0) ? min_map-1 : 0;
    } else {
      break;
    }
  }

  if (lengths.size() == 0)
    return lengths;

  // Make vector of <number of occurences, length>
  std::sort(lengths.begin(), lengths.end());
  Occurence occurence;
  Occurences occurences;
  size_t prev_val = lengths[0];
  size_t prev_val_count = 1;
  for (size_t x=1; x < lengths.size(); x++) {
    if (lengths[x-1] == lengths[x]) {
      prev_val_count++;
    } else {
      occurence[0] = prev_val_count;
      occurence[1] = prev_val;
      occurences.push_back(occurence);
      prev_val = lengths[x];
      prev_val_count = 1;
    }
  }
  occurence[0] = prev_val_count;
  occurence[1] = prev_val;
  occurences.push_back(occurence);

  // Sort lengths by number of occurences
  //std::sort(occurences.begin(), occurences.end(), sort_by_first_item);
  std::sort(occurences.begin(), occurences.end(), occurence_cmp());
  lengths.clear();
  for (size_t x=0; x < occurences.size(); x++)
    lengths.push_back(occurences[x][1]);

  return lengths;
}
