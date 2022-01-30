#include <App.h>
#include <graphics/MainMenu.h>
#include <graphics/PlayingScreen.h>
#include <utility>
#include <algorithm>

MainMenu::MainMenu() {
  Menu::addOption(MainMenu::createMenuOption("Start a game", 940.0f), ButtonType::PLAY);
}

void MainMenu::draw() {
  for (const auto& [type, option] : Menu::getMenuOptions()) {
    option.getMessage().lock()->draw();
    option.getButton().lock()->draw();
  }
}

void MainMenu::update(float ms) {
  std::for_each(this->getMenuOptions().begin(), this->getMenuOptions().end(), [&ms](const auto &pair) {
    pair.second.getMessage().lock()->update(ms);
    pair.second.getButton().lock()->update(ms);
    if (pair.second.getButton().lock()->clicked()) {
      pair.second.playSound();
    }
  });

  if (Menu::getMenuOption(ButtonType::PLAY).getButton().lock()->clicked()) {
    this->pressButton(ButtonType::PLAY);
  }
}

MenuOption MainMenu::createMenuOption(std::string message, float verticalPoint) {
  const std::size_t size{160};
  const float horizontalPoint{2050 - static_cast<float>(message.length()) * size / 2};
  const auto coordinates{std::make_pair(horizontalPoint, verticalPoint)};
  HUD menuHud{HUD(std::move(message), coordinates, size)};
  menuHud.setTextBrush(Brush::LIGHT_BROWN);
  return MenuOption(menuHud);
}

void MainMenu::pressButton(const ButtonType &type) const {
  if (type == ButtonType::PLAY) {
    App *app{static_cast<App *>(graphics::getUserData())};
    const auto playingScreen{std::make_shared<PlayingScreen>()};
    app->changeScreen(playingScreen);
  }
}
