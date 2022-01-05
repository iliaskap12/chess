#ifndef CHESS_RECTANGLE_H
#define CHESS_RECTANGLE_H

#include "Point.h"
#include "Drawable.h"
#include <sgg/graphics.h>

class Rectangle : public Drawable {
  Point leftTop;
  Point rightTop;
  Point leftBottom;
  Point rightBottom;
  Point center;
  float height {};
  float width {};
  graphics::Brush brush_ { graphics::Brush() };

public:
  Rectangle();
  explicit Rectangle(Point leftBottom, float height, float width);
  [[nodiscard]] const graphics::Brush &getBrush() const;
  void setBrush(graphics::Brush brush);
  [[nodiscard]] const Point &getLeftTop() const;
  [[nodiscard]] const Point &getRightTop() const;
  [[nodiscard]] const Point &getLeftBottom() const;
  [[nodiscard]] const Point &getRightBottom() const;
  [[nodiscard]] const Point &getCenter() const;
  [[nodiscard]] float getHeight() const;
  [[nodiscard]] float getWidth() const;
  void draw() override;
};

#endif//CHESS_RECTANGLE_H
