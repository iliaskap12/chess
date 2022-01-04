#include <graphics/MainMenu.h>
#include <utility>
#include <iostream>

MainMenu::MainMenu() {
  Menu::addOption(MainMenu::createMenuOption("Start a game", 384.0f), ButtonType::PLAY);
}

void MainMenu::draw() {
  for (const auto& [type, option] : Menu::getMenuOptions()) {
    option.getMessage().draw();
  }
}

void MainMenu::update(float ms) {
  graphics::MouseState mouse { graphics::MouseState() };
  graphics::getMouseState(mouse);
  const float mouseHorizontalPoint { graphics::windowToCanvasX(static_cast<float>(mouse.cur_pos_x)) };
  const float mouseVerticalPoint { graphics::windowToCanvasY(static_cast<float>(mouse.cur_pos_y)) };
  if (mouse.button_left_released && Menu::getMenuOption(ButtonType::PLAY).clicked(mouseHorizontalPoint, mouseVerticalPoint)) {
    std::cout << "Clicked!" << std::endl;
  }
}

MenuOption MainMenu::createMenuOption(std::string message, float verticalPoint) {
  const std::size_t size { 50 };
  const float horizontalPoint { 640 - static_cast<float>(message.length()) * size / 2 };
  const auto coordinates { std::make_pair(horizontalPoint, verticalPoint) };
  return MenuOption(HUD(std::move(message), coordinates, size));
}
