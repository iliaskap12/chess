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
    option.getMessage().lock()->draw();
    option.getButton().lock()->draw();
  }
}

void InGameMenu::update(float ms) {
  std::for_each(this->getMenuOptions().begin(), this->getMenuOptions().end(), [&ms](const auto &pair) {
    pair.second.getMessage().lock()->update(ms);
    pair.second.getButton().lock()->update(ms);
    if (pair.second.getButton().lock()->clicked()) {
      pair.second.playSound();
    }
  });

  if (Menu::getMenuOption(ButtonType::QUIT).getButton().lock()->clicked()) {
    this->pressButton(ButtonType::QUIT);
  }
}

void InGameMenu::pressButton(const ButtonType &type) const {
  if (type == ButtonType::QUIT) {
    App *app{static_cast<App *>(graphics::getUserData())};
    if (!app->getGame().expired() && app->getGame().lock()->getCheckboard() != nullptr && !app->getGame().lock()->getCheckboard()->isPawnMoving()) {
      app->changeScreen(std::make_shared<OpeningScreen>());
    }
  }
}
