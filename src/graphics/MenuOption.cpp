#include <graphics/MenuOption.h>
#include <utility>
#include <iostream>

MenuOption::MenuOption(HUD hud) : optionHUD(std::move(hud)) {}

HUD MenuOption::getMessage() const {
  return this->optionHUD;
}
bool MenuOption::clicked(const float &mouseHorizontalPoint, const float &mouseVerticalPoint) const {
  const auto [buttonX, buttonY] { this->optionHUD.getCoordinates() };
  const std::size_t size { this->optionHUD.getSize() };
  const float length { this->optionHUD.getLength() * 1.1f};
  bool inVerticalSpace { false };
  bool inHorizontalSpace { false };

  if (mouseVerticalPoint <= buttonY && mouseVerticalPoint >= buttonY - static_cast<float>(size)) {
    inVerticalSpace = true;
  }

  if (mouseHorizontalPoint >= buttonX && mouseHorizontalPoint <= buttonX + static_cast<float>(size) / 2 * length) {
    inHorizontalSpace = true;
  }

  return inVerticalSpace && inHorizontalSpace;
}
