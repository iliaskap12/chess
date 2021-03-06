#include <hud/HUD.h>
#include <utility>

HUD::HUD() = default;

HUD::HUD(std::string message, std::pair<float, float> coordinates, size_t size)
    : message(std::move(message)), coordinates(std::move(coordinates)), size(size) {
  this->drawingArea->setHeight(static_cast<float>(this->size));
  this->drawingArea->setWidth(static_cast<float>(this->message.length() * this->size) / 2);
  this->drawingArea->setCenter(Point(this->coordinates.first, this->coordinates.second));
}

void HUD::draw() {
  graphics::drawText(this->coordinates.first, this->coordinates.second, static_cast<float>(this->size), this->message, this->drawingArea->getBrush());
}

void HUD::update(float ms) {
  if (this->newMessage.first) {
    this->message = { *(this->newMessage.second) };
    this->newMessage = { std::make_pair(false, std::optional<std::string>()) };
  }
}

void HUD::updateText(std::string text) {
  this->newMessage = { std::make_pair(true, std::move(text)) };
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

void HUD::setTextBrush(Brush type) {
  this->drawingArea->setBrush(type, Rectangle::colors.at(type));
}
