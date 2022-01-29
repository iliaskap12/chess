#include <game/PawnColor.h>
#ifdef _WIN32
  #include <sstream>
#endif

std::string pawnColorToString(const PawnColor& color) {
  if (color == PawnColor::WHITE) {
    return "white";
  } else {
    return "black";
  }
}

template <typename T>
std::string operator+(const T& lhs, const PawnColor &color) {
  return lhs + pawnColorToString(color);
}

template <typename T>
std::string operator+(const PawnColor &color, const T& rhs) {
  return pawnColorToString(color) + rhs;
}

std::string operator+(const PawnColor &color1, const PawnColor &color2) {
  return pawnColorToString(color1) + pawnColorToString(color2);
}

std::ostream &operator<<(std::ostream &lhs, const PawnColor &color) {
  return lhs << pawnColorToString(color);
}

PawnColor operator!(const PawnColor &color) {
  PawnColor oppositeColor;
  if (color == PawnColor::WHITE) {
    oppositeColor = PawnColor::BLACK;
  } else {
    oppositeColor = PawnColor::WHITE;
  }
  return oppositeColor;
}

template std::string operator+(const std::string &lhs, const PawnColor &color);
template std::string operator+(const PawnColor &color, const std::string &rhs);
