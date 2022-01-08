#include <graphics/MenuOption.h>
#include <utility>

MenuOption::MenuOption(HUD hud) : optionHUD(std::move(hud)) {
  const auto [buttonX, buttonY] { this->optionHUD.getCoordinates() };
  const std::size_t size { this->optionHUD.getSize() };
  const float length { this->optionHUD.getLength() * 1.25f * static_cast<float>(size) / 2};
  this->button.setHeight(static_cast<float>(size) * 1.25f);
  this->button.setWidth(length);
  this->button.setLeftBottom(Point(buttonX * 0.875f, buttonY * 1.075f));
}

HUD MenuOption::getMessage() const {
  return this->optionHUD;
}

Rectangle MenuOption::getButton() const {
  return this->button;
}
