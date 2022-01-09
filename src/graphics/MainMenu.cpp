#include <graphics/MainMenu.h>
#include <utility>
#include <iostream>
#include <App.h>
#include <graphics/PlayingScreen.h>

MainMenu::MainMenu() {
  Menu::addOption(MainMenu::createMenuOption("Start a game", 400.0f), ButtonType::PLAY);
}

void MainMenu::draw() {
  for (const auto& [type, option] : Menu::getMenuOptions()) {
    option.getMessage().draw();
    option.getButton().draw();
  }
}

void MainMenu::update(float ms) {
  if (Menu::getMenuOption(ButtonType::PLAY).getButton().clicked()) {
    this->pressButton(ButtonType::PLAY);
  }

  for (const auto& [type, option] : Menu::getMenuOptions()) {
    option.getMessage().update(ms);
    option.getButton().update(ms);
  }
}

MenuOption MainMenu::createMenuOption(std::string message, float verticalPoint) {
  const std::size_t size { 80 };
  const float horizontalPoint { 1025 - static_cast<float>(message.length()) * size / 2 };
  const auto coordinates { std::make_pair(horizontalPoint, verticalPoint) };
  HUD menuHud { HUD(std::move(message), coordinates, size) };
  menuHud.setTextBrush(Brush::LIGHT_BROWN);
  return MenuOption(menuHud);
}

void MainMenu::pressButton(const ButtonType &type) const {
  if (type == ButtonType::PLAY) {
    App *app {static_cast<App *>(graphics::getUserData())};
    app->changeScreen(std::make_shared<PlayingScreen>());
  }
}
