#include <graphics/MenuOption.h>
#include <utility>

MenuOption::MenuOption(HUD hud) : optionHUD(std::move(hud)) {
  const auto [buttonX, buttonY] { this->optionHUD.getCoordinates() };
  const std::size_t size { this->optionHUD.getSize() };
  const float length { this->optionHUD.getLength() * 1.25f * static_cast<float>(size) / 2};
  this->button = { Rectangle(Point(buttonX * 0.875f, buttonY * 1.075f), static_cast<float>(size) * 1.25f, length) };
}

HUD MenuOption::getMessage() const {
  return this->optionHUD;
}
bool MenuOption::clicked(const float &mouseHorizontalPoint, const float &mouseVerticalPoint) const {
  bool inVerticalSpace { false };
  bool inHorizontalSpace { false };

  if (mouseVerticalPoint >= this->button.getLeftTop().getY() && mouseVerticalPoint <= this->button.getLeftBottom().getY()) {
    inVerticalSpace = { true };
  }

  if (mouseHorizontalPoint >= this->button.getLeftTop().getX() && mouseHorizontalPoint <= this->button.getRightTop().getX()) {
    inHorizontalSpace = { true };
  }

  return inVerticalSpace && inHorizontalSpace;
}

Rectangle MenuOption::getButton() const {
  return this->button;
}
