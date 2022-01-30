#include <graphics/OpeningScreen.h>
#include <sgg/graphics.h>

OpeningScreen::OpeningScreen() {
  const std::string headline{"Let's play chess!"};
  const std::size_t size{180};
  const auto coordinates{std::make_pair(2400 - static_cast<float>(headline.length() * size) / 2, 480)};
  this->welcomeMessage = {std::make_unique<HUD>(headline, coordinates, size)};
  this->welcomeMessage->setTextBrush(Brush::DARK_BROWN);
}

void OpeningScreen::draw() {
  if (!this->stopUpdating) {
    graphics::setWindowBackground(Rectangle::colors.at(Brush::LIGHT_BROWN));

    this->mainMenu->draw();
    this->welcomeMessage->draw();
  }
}

void OpeningScreen::update(float ms) {
  if (!this->stopUpdating) {
    this->mainMenu->update(ms);
  }
}

void OpeningScreen::cleanup() {
  this->mainMenu.reset();
  this->welcomeMessage.reset();
  this->stopUpdating = {true};
}
