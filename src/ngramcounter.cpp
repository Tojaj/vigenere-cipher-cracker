#include "ngramcounter.h"

#include <algorithm>
#include <array>
#include <string>

NgramCounter::NgramCounter()
{
  trigram[0] = trigram[1] = trigram[2] = trigram[3] = '\0';
  count = 0;
}

void
NgramCounter::put(char letter)
{
  // Shift letter into the trigram buffer
  trigram[0] = trigram[1];
  trigram[1] = trigram[2];
  trigram[2] = letter;

  ++count;
  if (count < 3) return;

  ngrammaps_[0][std::string(trigram)].push_back(count-3);
}

void
NgramCounter::cleanup(NgramMap &map)
{
  NgramMap::iterator it = map.begin();
  while (it != map.end()) {
    if (it->second.size() <= 1)
      map.erase(it++);
    else
      ++it;
  }
}

void
NgramCounter::find_longer_ngrams(std::string &text)
{
  cleanup(ngrammaps_[0]);

  for (int nm_id = 1; nm_id < NGRAMMAPS; nm_id++) {
    NgramIndexes merged_indexes;
    NgramMap::iterator it;

    // Make vector of all ngrams
    it = ngrammaps_[nm_id-1].begin();
    while (it != ngrammaps_[nm_id-1].end()) {
      merged_indexes.insert(merged_indexes.end(),
                            it->second.begin(),
                            it->second.end());
      it++;
    }

    // Inspect indexes and identify ngrams with len+1
    std::sort(merged_indexes.begin(), merged_indexes.end());

    NgramIndexes longer_ngrams;
    for (size_t x = 1; x < merged_indexes.size(); x++) {
      if ((merged_indexes[x-1] + 1) == merged_indexes[x])
        longer_ngrams.push_back(merged_indexes[x-1]);
    }
/*
    printf("Longer ngram sequences:\n");
    for (size_t x = 0; x < longer_ngrams.size(); x++)
      printf(" %zu\n", longer_ngrams[x]);
*/
    // TODO create new ngrammap
    for (size_t x = 0; x < longer_ngrams.size(); x++) {
      std::string ngram = text.substr(longer_ngrams[x], (3 + nm_id));
      ngrammaps_[nm_id][ngram].push_back(longer_ngrams[x]);
    }

    // Remove ngrams that had only one occurence
    cleanup(ngrammaps_[nm_id]);
/*
    // Remove short ngrams that are infact only substrings of longer ngrams
    it = ngrammaps_[nm_id-1].begin();
    while (it != ngrammaps_[nm_id-1].end()) {
      NgramIndexes *indexes = it->second;
      NgramIndexes::iterator iit = indexes->begin();
      for (; iit != indexes->end(); iit++) {
        if (*iit)
      }
    }
*/
  }
}

void
NgramCounter::print_content()
{
  NgramMap::iterator it;
  for (int x=0; x < NGRAMMAPS; x++) {
    printf("%d-grams:\n", x+3);
    for (it = ngrammaps_[x].begin(); it != ngrammaps_[x].end(); ++it) {
      //NgramIndexes::size_type len = it->second.size();
      auto len = it->second.size();
      auto x = len;
      printf(" %s)", it->first.c_str());
      for (x = 0; x < len; x++)
        printf(" %zu", it->second[x]);
      putchar('\n');
    }
  }
}

NgramMap *
NgramCounter::ngrammap(int id)
{
  return &(ngrammaps_[id]);
}
