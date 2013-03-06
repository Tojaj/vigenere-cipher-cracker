#include "ngramcounter.h"

#include <algorithm>
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

  ngrammap_[std::string(trigram)].push_back(count-3);
}

void
NgramCounter::cleanup()
{
  NgramMap::iterator it = ngrammap_.begin();
  while (it != ngrammap_.end()) {
    if (it->second.size() <= 1)
      ngrammap_.erase(it++);
    else
      ++it;
  }
}

void
NgramCounter::find_longer_ngrams()
{
  NgramIndexes merged_indexes;
  NgramMap ngrammap;
  NgramMap::iterator it;

  cleanup();

  // Make vector of all ngrams
  it = ngrammap_.begin();
  while (it != ngrammap_.end()) {
    merged_indexes.insert(merged_indexes.end(),
                          it->second.begin(),
                          it->second.end());
    it++;
  }

  // Inspect indexes and identify longer ngrams
  std::sort(merged_indexes.begin(), merged_indexes.end());

  typedef std::vector<size_t[2]> NgramSequences;
  NgramSequences sequences;
  long long seq_begin = -1;
  for (size_t x = 1; x < merged_indexes.size(); x++) {
    printf("%d\n", merged_indexes[x]);
    if ((merged_indexes[x-1] + 1) == merged_indexes[x]) {
      if (seq_begin == -1) seq_begin = (x-1);
    } else {
      if (seq_begin != -1) {
        sequences.push_back({ seq_begin, (x-1) });
        seq_begin = -1;
      }
    }
  }

  for (size_t x = 0; x < sequences.size(); x++) {
    printf(" %zu %zu\n", sequences[x][0], sequences[x][1]);
  }
}

void
NgramCounter::print_content()
{
  NgramMap::iterator it;
  for (it = ngrammap_.begin(); it != ngrammap_.end(); ++it) {
    //NgramIndexes::size_type len = it->second.size();
    auto len = it->second.size();
    auto x = len;
    printf("%s)", it->first.c_str());
    for (x = 0; x < len; x++)
      printf(" %zu", it->second[x]);
    putchar('\n');
  }
}

NgramMap
NgramCounter::ngrammap()
{
  return ngrammap_;
}
