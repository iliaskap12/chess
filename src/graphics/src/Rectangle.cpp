#include <sgg/graphics.h>
#include <graphics/Rectangle.h>
#include <App.h>

Rectangle::Rectangle() = default;

Rectangle::Rectangle(Point leftBottom, float height, float width) : leftBottom_(leftBottom), height_(height), width_(width) {
  this->leftTop = { Point(this->leftBottom_.getX(), this->leftBottom_.getY() - height) };
  this->rightBottom = { Point(this->leftBottom_.getX() + width, this->leftBottom_.getY()) };
  this->rightTop = { Point(this->rightBottom.getX(), this->leftTop.getY()) };
  this->center_ = { Point((this->leftTop.getX() + this->rightTop.getX()) / 2, (this->leftBottom_.getY() + this->leftTop.getY()) / 2) };
  Rectangle::populateBrushes();
  this->brush_ = { Rectangle::colors.at(Brush::DARK_BROWN) };
  this->markBrush = { Rectangle::colors.at(Brush::DARK_GREEN) };
  this->brushType = { Brush::DARK_BROWN };
  this->markBrushType = { Brush::DARK_GREEN };
}

Rectangle::Rectangle(Point leftBottom, float height, float width, const graphics::Brush& brush, const Brush &type) : Rectangle(leftBottom, height, width) {
  this->brush_ = { brush };
  this->brushType = { type };
}

const graphics::Brush &Rectangle::getBrush() const {
  return this->brush_;
}

void Rectangle::setBrush(Brush type, graphics::Brush brush) {
  this->brushType = { type };
  this->brush_ = { std::move(brush) };
}

void Rectangle::setMarkBrush(Brush brush) {
  this->markBrush = { Rectangle::colors.at(brush) };
  this->markBrushType = { brush };
}

Brush Rectangle::getBrushType() const {
  return this->brushType;
}

void Rectangle::swapBrushes() {
  std::swap(this->brush_, this->markBrush);
  std::swap(this->brushType, this->markBrushType);
  this->swapped = { !this->swapped };
}

const Point &Rectangle::getLeftTop() const {
  return this->leftTop;
}

const Point &Rectangle::getRightTop() const {
  return this->rightTop;
}

const Point &Rectangle::getLeftBottom() const {
  return this->leftBottom_;
}

const Point &Rectangle::getRightBottom() const {
  return this->rightBottom;
}

const Point &Rectangle::getCenter() const {
  return this->center_;
}

float Rectangle::getHeight() const {
  return this->height_;
}

float Rectangle::getWidth() const {
  return this->width_;
}

void Rectangle::setHeight(float height) {
  this->height_ = { height };
}

void Rectangle::setWidth(float width) {
  this->width_ = { width };
}

void Rectangle::setLeftBottom(const Point &leftBottom) {
  this->leftBottom_ = { leftBottom };
  this->leftTop = { Point(this->leftBottom_.getX(), this->leftBottom_.getY() - this->height_) };
  this->rightBottom = { Point(this->leftBottom_.getX() + this->width_, this->leftBottom_.getY()) };
  this->rightTop = { Point(this->rightBottom.getX(), this->leftTop.getY()) };
  this->center_ = { Point((this->leftTop.getX() + this->rightTop.getX()) / 2, (this->leftBottom_.getY() + this->leftTop.getY()) / 2) };
}

void Rectangle::setCenter(const Point &center) {
  this->center_ = { center };
  this->leftTop = { Point((this->center_.getX() * 2) - this->width_, this->center_.getY() * 2) };
  this->rightTop = { Point(this->leftTop.getX() + this->width_, this->leftTop.getY()) };
  this->rightBottom = { Point(this->rightTop.getX(), this->rightTop.getY() - this->height_) };
  this->leftBottom_ = { Point(this->leftTop.getX(), this->rightBottom.getY()) };
}

void Rectangle::draw() {
  if (const auto &game { static_cast<App*>(graphics::getUserData())->getGame() }; game != nullptr) {
    if (game->getCheckboard()->amISelected(this) || game->getCheckboard()->amIinDanger(this)) {
      this->selected = { true };
    } else {
      this->selected = { false };
    }
  } else {
    this->selected = { false };
  }
  graphics::Brush brush { this->selected ? Rectangle::colors.at(Brush::RED) : this->brush_ };
  graphics::drawRect(
      this->center_.getX(),
      this->center_.getY(),
      this->width_,
      this->height_,
      brush
  );
}

void Rectangle::update(float ms) {
  if (const auto& game { static_cast<App*>(graphics::getUserData())->getGame() }; game != nullptr) {
    if (game->getCheckboard()->shouldMark(this)) {
      if (!this->swapped) {
        this->swapBrushes();
      }
    } else {
      if (this->swapped) {
        this->swapBrushes();
      }
    }
  }
}

bool Rectangle::clicked() const {
  graphics::MouseState mouse { graphics::MouseState() };
  graphics::getMouseState(mouse);
  const float mouseHorizontalPoint { graphics::windowToCanvasX(static_cast<float>(mouse.cur_pos_x)) };
  const float mouseVerticalPoint { graphics::windowToCanvasY(static_cast<float>(mouse.cur_pos_y)) };

  bool inVerticalSpace { false };
  bool inHorizontalSpace { false };

  if (mouseVerticalPoint >= this->leftTop.getY() && mouseVerticalPoint <= this->leftBottom_.getY()) {
    inVerticalSpace = { true };
  }

  if (mouseHorizontalPoint >= this->leftTop.getX() && mouseHorizontalPoint <= this->rightTop.getX()) {
    inHorizontalSpace = { true };
  }

  return mouse.button_left_pressed && inVerticalSpace && inHorizontalSpace;
}

bool operator==(const Rectangle &lhs, const Rectangle &rhs) {
  return lhs.id == rhs.id;
}

void Rectangle::populateBrushes() {
  graphics::Brush lightBrown { graphics::Brush() };
  lightBrown.fill_color[0] = { 1.0f };
  lightBrown.fill_color[1] = { 0.9137f };
  lightBrown.fill_color[2] = { 0.7725f };
  lightBrown.fill_opacity = { 1.0f };
  lightBrown.outline_opacity = { 0.0f };
  lightBrown.outline_width = { 0.0f };

  graphics::Brush darkBrown { graphics::Brush() };
  darkBrown.fill_color[0] = { 0.4588f };
  darkBrown.fill_color[1] = { 0.2901f };
  darkBrown.fill_color[2] = { 0.0f };
  darkBrown.fill_opacity = { 1.0f };
  darkBrown.outline_opacity = { 0.0f };
  darkBrown.outline_width = { 0.0f };

  graphics::Brush lightGreen { graphics::Brush() };
  lightGreen.fill_color[0] = { 0.0f };
  lightGreen.fill_color[1] = { 1.0f };
  lightGreen.fill_color[2] = { 0.1725f };
  lightGreen.fill_opacity = { 0.5f };
  lightGreen.outline_opacity = { 0.0f };
  lightGreen.outline_width = { 0.0f };

  graphics::Brush darkGreen { graphics::Brush() };
  darkGreen.fill_color[0] = { 0.2392f };
  darkGreen.fill_color[1] = { 0.4f };
  darkGreen.fill_color[2] = { 0.0f };
  darkGreen.fill_opacity = { 0.5f };
  darkGreen.outline_opacity = { 0.0f };
  darkGreen.outline_width = { 0.0f };

  graphics::Brush red { graphics::Brush() };
  red.fill_color[0] = { 0.5803f };
  red.fill_color[1] = { 0.0f };
  red.fill_color[2] = { 0.0f };
  red.fill_opacity = { 0.5f };
  red.outline_opacity = { 0.0f };
  red.outline_width = { 0.0f };

  graphics::Brush texture { graphics::Brush() };
  texture.fill_color[0] = { 1.0f };
  texture.fill_color[1] = { 1.0f };
  texture.fill_color[2] = { 1.0f };
  texture.fill_opacity = { 1.0f };
  texture.outline_opacity = { 0.0f };
  texture.outline_width = { 0.0f };

  graphics::Brush checkboard { graphics::Brush() };
  checkboard.fill_color[0] = { 1.0f };
  checkboard.fill_color[1] = { 1.0f };
  checkboard.fill_color[2] = { 1.0f };
  checkboard.fill_opacity = { 1.0f };
  checkboard.outline_width = { 10 };
  checkboard.outline_opacity = { 1.0f };
  checkboard.outline_color[0] = { 0.4588f };
  checkboard.outline_color[1] = { 0.2901f };
  checkboard.outline_color[2] = { 0.0f };

  Rectangle::colors.try_emplace(Brush::LIGHT_BROWN, lightBrown);
  Rectangle::colors.try_emplace(Brush::DARK_BROWN, darkBrown);
  Rectangle::colors.try_emplace(Brush::LIGHT_GREEN, lightGreen);
  Rectangle::colors.try_emplace(Brush::DARK_GREEN, darkGreen);
  Rectangle::colors.try_emplace(Brush::RED, red);
  Rectangle::colors.try_emplace(Brush::TEXTURE, texture);
  Rectangle::colors.try_emplace(Brush::CHECKBOARD, checkboard);
}

long Rectangle::getId() const {
  return this->id;
}
