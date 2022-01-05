#include <sgg/graphics.h>
#include <iostream>
#include "graphics/Rectangle.h"

Rectangle::Rectangle() = default;

Rectangle::Rectangle(Point leftBottom, float height, float width) : leftBottom(leftBottom), height(height), width(width) {
  this->leftTop = { Point(this->leftBottom.getX(), this->leftBottom.getY() - height) };
  this->rightBottom = { Point(this->leftBottom.getX() + width, this->leftBottom.getY()) };
  this->rightTop = { Point(this->rightBottom.getX(), this->leftTop.getY()) };
  this->center = { Point((this->leftTop.getX() + this->rightTop.getX()) / 2, (this->leftBottom.getY() + this->leftTop.getY()) / 2) };
  this->brush_.fill_color[0] = { 0.4588f };
  this->brush_.fill_color[1] = { 0.2901f };
  this->brush_.fill_color[2] = { 0.0f };
  this->brush_.outline_opacity = { 0.0f };
}

const graphics::Brush &Rectangle::getBrush() const {
  return this->brush_;
}

void Rectangle::setBrush(graphics::Brush brush) {
  this->brush_ = { std::move(brush) };
}

const Point &Rectangle::getLeftTop() const {
  return this->leftTop;
}

const Point &Rectangle::getRightTop() const {
  return this->rightTop;
}

const Point &Rectangle::getLeftBottom() const {
  return this->leftBottom;
}

const Point &Rectangle::getRightBottom() const {
  return this->rightBottom;
}

const Point &Rectangle::getCenter() const {
  return this->center;
}

float Rectangle::getHeight() const {
  return this->height;
}

float Rectangle::getWidth() const {
  return this->width;
}
void Rectangle::draw() {
  graphics::drawRect(
      this->center.getX(),
      this->center.getY(),
      this->width,
      this->height,
      this->brush_);
}
