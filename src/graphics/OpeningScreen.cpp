#include <graphics/OpeningScreen.h>
#include <sgg/graphics.h>

OpeningScreen::OpeningScreen() {
  const std::string headline { "Let's play chess!" };
  const std::size_t size{ 90 };
  const auto coordinates { std::make_pair(975 - static_cast<float>(headline.length() * size) / 2, 160) };
  this->welcomeMessage = { HUD(headline, coordinates, size) };
  this->welcomeMessage->setTextBrush(0.4588f, 0.2901f, 0.0f);
}

void OpeningScreen::draw() {
  graphics::Brush openingScreen { graphics::Brush() };
  openingScreen.fill_color[0] = { 1.0f };
  openingScreen.fill_color[1] = { 0.9137f };
  openingScreen.fill_color[2] = { 0.7725f };
  openingScreen.fill_opacity = { 1.0f };
  graphics::setWindowBackground(openingScreen);

  this->mainMenu->draw();
  (*this->welcomeMessage).draw();
}

void OpeningScreen::pressButton(ButtonType type) {
  // press button
}

void OpeningScreen::update(float ms) {
  this->mainMenu->update(ms);
}

