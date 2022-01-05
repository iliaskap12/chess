#include <hud/HUD.h>
#include <utility>

HUD::HUD(std::string message, std::pair<float, float> coordinates, size_t size)
    : message(std::move(message)), coordinates(std::move(coordinates)), size(size) {
  this->textBrush.fill_color[0] = { 1.0f };
  this->textBrush.fill_color[1] = { 0.9137f };
  this->textBrush.fill_color[2] = { 0.7725f };
  this->textBrush.fill_opacity = { 1.0f };
}

void HUD::draw() {
  graphics::drawText(this->coordinates.first, this->coordinates.second, static_cast<float>(this->size), this->message, this->textBrush);
}

const std::pair<float, float> &HUD::getCoordinates() const {
  return this->coordinates;
}

size_t HUD::getSize() const {
  return this->size;
}

float HUD::getLength() const {
  return static_cast<float>(this->message.length());
}

void HUD::setTextBrush(float red, float green, float blue) {
  this->textBrush.fill_color[0] = { red };
  this->textBrush.fill_color[1] = { green };
  this->textBrush.fill_color[2] = { blue };
}
