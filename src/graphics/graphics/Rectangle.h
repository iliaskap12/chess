#ifndef CHESS_RECTANGLE_H
#define CHESS_RECTANGLE_H

#include "Point.h"
#include "Drawable.h"
#include "Updateable.h"
#include "Brush.h"
#include <sgg/graphics.h>
#include <chrono>
#include <memory>

class Rectangle : public Drawable, public Updateable, public std::enable_shared_from_this<Rectangle> {
public:
  inline static std::unordered_map<Brush, graphics::Brush> colors{std::unordered_map<Brush, graphics::Brush>()};

private:
  Point leftTop;
  Point rightTop;
  Point leftBottom_;
  Point rightBottom;
  Point center_;
  float height_{};
  float width_{};
  graphics::Brush brush_ { graphics::Brush() };
  Brush brushType {};
  graphics::Brush markBrush { graphics::Brush() };
  Brush markBrushType {};
  bool selected { false };
  bool swapped { false };
  const long long id { std::chrono::high_resolution_clock::now().time_since_epoch().count() };

public:
  Rectangle();
  explicit Rectangle(Point leftBottom, float height, float width);
  explicit Rectangle(Point leftBottom, float height, float width, const graphics::Brush& brush, const Brush &type);

  // brushes
  static void populateBrushes();
  [[nodiscard]] const graphics::Brush &getBrush() const;
  [[nodiscard]] Brush getBrushType() const;
  void setBrush(Brush type, graphics::Brush brush);
  void setMarkBrush(Brush brush);
  void swapBrushes();

  // points
  [[nodiscard]] const Point &getLeftTop() const;
  [[nodiscard]] const Point &getRightTop() const;
  [[nodiscard]] const Point &getLeftBottom() const;
  void setLeftBottom(const Point &leftBottom);
  [[nodiscard]] const Point &getRightBottom() const;
  [[nodiscard]] const Point &getCenter() const;
  void setCenter(const Point &center);
  [[nodiscard]] float getHeight() const;
  [[nodiscard]] float getWidth() const;
  void setHeight(float height);
  void setWidth(float width);

  // rendering
  void draw() override;
  void update(float ms) override;
  [[nodiscard]] bool clicked() const;

  friend bool operator==(const Rectangle& lhs, const Rectangle& rhs);
  [[nodiscard]] long getId() const;
};

#endif//CHESS_RECTANGLE_H
