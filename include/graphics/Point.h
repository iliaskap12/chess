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
  Point operator+(const Point &other) const;

#ifdef _WIN32
  friend bool operator==(const Point& lhs, const Point& rhs);
#else
  friend bool operator==(const Point& lhs, const Point& rhs) = default;
#endif
};

#endif//CHESS_POINT_H
