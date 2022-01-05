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
  graphics::MouseState mouse { graphics::MouseState() };
  graphics::getMouseState(mouse);
  const float mouseHorizontalPoint { graphics::windowToCanvasX(static_cast<float>(mouse.cur_pos_x)) };
  const float mouseVerticalPoint { graphics::windowToCanvasY(static_cast<float>(mouse.cur_pos_y)) };
  if (mouse.button_left_pressed && Menu::getMenuOption(ButtonType::PLAY).clicked(mouseHorizontalPoint, mouseVerticalPoint)) {
    this->pressButton(ButtonType::PLAY);
  }
}

MenuOption MainMenu::createMenuOption(std::string message, float verticalPoint) {
  const std::size_t size { 80 };
  const float horizontalPoint { 825 - static_cast<float>(message.length()) * size / 2 };
  const auto coordinates { std::make_pair(horizontalPoint, verticalPoint) };
  return MenuOption(HUD(std::move(message), coordinates, size));
}

void MainMenu::pressButton(const ButtonType &type) const {
  if (type == ButtonType::PLAY) {
    App *app {static_cast<App *>(graphics::getUserData())};
    app->changeScreen(std::make_shared<PlayingScreen>());
  }
}
