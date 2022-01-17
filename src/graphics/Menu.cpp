#include <graphics/Menu.h>

Menu::Menu() = default;

void Menu::addOption(const MenuOption& option, ButtonType buttonType) {
  this->options.insert(std::make_pair(buttonType, option));
}

const MenuOption &Menu::getMenuOption(ButtonType buttonType) {
  return this->options.at(buttonType);
}

const std::unordered_map<ButtonType, MenuOption> &Menu::getMenuOptions() const {
  return this->options;
}
