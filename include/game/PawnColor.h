//
// Created by ilias on 3/1/22.
//

#ifndef CHESS_PAWNCOLOR_H
#define CHESS_PAWNCOLOR_H

#include <string>
#include <array>

enum class PawnColor {
  WHITE = 0,
  BLACK = 1
};

template <typename T>
std::string operator+(const T& lhs, const PawnColor &color);

template <typename T>
std::string operator+(const PawnColor &color, const T& rhs);

std::string operator+(const PawnColor &color1, const PawnColor &color2);

std::ostream& operator<<(std::ostream& lhs, const PawnColor &color);

std::string pawnColorToString(const PawnColor& color);

#endif//CHESS_PAWNCOLOR_H
