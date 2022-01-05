#ifndef CHESS_POINT_H
#define CHESS_POINT_H

class Point {
  float x {};
  float y {};

public:
  Point();
  Point(float x, float y);
  [[nodiscard]] float getX() const;
  [[nodiscard]] float getY() const;
};

#endif//CHESS_POINT_H
