#include <graphics/Point.h>

Point::Point() = default;

Point::Point(float x, float y) : x(x), y(y) {}

float Point::getX() const {
  return this->x;
}

float Point::getY() const {
  return this->y;
}

Point Point::operator+(const Point &other) const {
  return {other.x + this->x, other.y + this->y};
}

#ifdef _WIN32
bool operator==(const Point &lhs, const Point &rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}
#endif
