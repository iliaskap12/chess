#include <graphics/OpeningScreen.h>
#include <sgg/graphics.h>

OpeningScreen::OpeningScreen() {
  const std::string headline { "Let's play chess!" };
  const std::size_t size { 90 };
  const auto coordinates { std::make_pair(1200 - static_cast<float>(headline.length() * size) / 2, 160) };
  this->welcomeMessage = { std::make_unique<HUD>(headline, coordinates, size) };
  this->welcomeMessage->setTextBrush(Brush::DARK_BROWN);
}

void OpeningScreen::draw() {
  graphics::setWindowBackground(Rectangle::colors.at(Brush::LIGHT_BROWN));

  this->mainMenu->draw();
  this->welcomeMessage->draw();
}

void OpeningScreen::update(float ms) {
  this->mainMenu->update(ms);
}

