#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(const std::string& source) {
  // identify all iterators to space characters
  auto space = find_all(source.begin(), source.end(), isspace);

  // generate tokens between consecutive space characters
  std::set<Token> tokens;
  std::transform(space.begin(), space.end() - 1, space.begin() + 1, 
                  std::inserter(tokens, tokens.end()),
                  [&source] (auto it1, auto it2) {
                    return Token { source, it1, it2};
                  }
  );

  // get rid of empty tokens
  std::erase_if(tokens, 
                [] (Token token) {
                  if (token.content.empty()) {
                    return true;
                  } else {
                    return false;
                  }
                }
                );

  return tokens;
}

namespace rv = std::ranges::views;

std::set<Mispelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  auto view = source | rv::filter([dictionary] (Token token) {
                                                  if (dictionary.contains(token.content)) {
                                                    return false;
                                                  } else {
                                                    return true;
                                                  }
  }) | rv::transform([dictionary] (Token token) -> Mispelling {
    auto view = dictionary | rv::filter([token] (std::string str) {
      return levenshtein(token.content, str) == 1;
    });
    std::set<std::string> suggestions(view.begin(), view.end());
    return Mispelling { token, suggestions };
  }) | rv::filter([] (Mispelling miss) {return !miss.suggestions.empty();});

  return std::set<Mispelling> (view.begin(), view.end());
};

/* Helper methods */

#include "utils.cpp"