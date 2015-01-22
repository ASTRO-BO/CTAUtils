#include "common_string.h"

namespace CTAUtils {

void split(std::vector<std::string> &tokens, const std::string &text, char sep) {
  std::string::size_type start = 0, end = 0;
  while ((end = text.find(sep, start)) != std::string::npos) {
    tokens.push_back(text.substr(start, end - start));
    start = end + 1;
  }
  tokens.push_back(text.substr(start));
}

}
