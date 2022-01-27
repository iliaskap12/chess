#include <util/custom-string.h>

std::vector<std::string> custom_string::split(const std::string &string, const std::string &delimiter) {
  std::size_t startingPosition { 0 };
  std::size_t endPosition;
  std::size_t delimiterLength { delimiter.length() };
  std::string token;
  std::vector<std::string> result;

  while ((endPosition = { string.find(delimiter, startingPosition) }) != std::string::npos) {
    token = { string.substr(startingPosition, endPosition - startingPosition) };
    startingPosition = { endPosition + delimiterLength };
    result.push_back(token);
  }

  result.push_back(string.substr(startingPosition));
  return result;
}
