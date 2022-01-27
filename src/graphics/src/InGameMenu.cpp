#include <App.h>
#include <algorithm>
#include <graphics/InGameMenu.h>
#include <graphics/OpeningScreen.h>

InGameMenu::InGameMenu() {
  const std::string message{"Quit game"};
  const float verticalPoint{600.0f};
  const std::size_t size{100};
  const float horizontalPoint{2400.0f};
  const auto coordinates{std::make_pair(horizontalPoint, verticalPoint)};
  HUD menuHud{HUD(message, coordinates, size)};
  menuHud.setTextBrush(Brush::LIGHT_BROWN);
  Menu::addOption(MenuOption(menuHud), ButtonType::QUIT);
}

void InGameMenu::draw() {
  for (const auto &[type, option]: Menu::getMenuOptions()) {
    option.getMessage().draw();
    option.getButton().draw();
  }
}

void InGameMenu::update(float ms) {
  std::ranges::for_each(this->getMenuOptions().begin(), this->getMenuOptions().end(), [&ms](const auto &pair) {
    pair.second.getMessage().update(ms);
    pair.second.getButton().update(ms);
    if (pair.second.getButton().clicked()) {
      pair.second.playSound();
    }
  });

  if (Menu::getMenuOption(ButtonType::QUIT).getButton().clicked()) {
    this->pressButton(ButtonType::QUIT);
  }
}

void InGameMenu::pressButton(const ButtonType &type) const {
  if (type == ButtonType::QUIT) {
    App *app{static_cast<App *>(graphics::getUserData())};
    app->changeScreen(std::make_shared<OpeningScreen>());
  }
}
