#include <game/Pawn.h>

Pawn::Pawn(PawnColor color) : color(color) {}

void Pawn::setSquare(Square* square) {
  this->square_ = { square };
  this->drawingArea = { this->square_->getDrawingArea() };
  graphics::Brush pawn { (*this->drawingArea).getBrush() };
  pawn.fill_color[0] = { 1.0f };
  pawn.fill_color[1] = { 1.0f };
  pawn.fill_color[2] = { 1.0f };
  pawn.texture = { getImagesPath() + this->texture_ + "-" + this->getColor() + this->png };
  (*this->drawingArea).setBrush(pawn);
}

Square *Pawn::getSquare() const {
  return this->square_;
}

PawnColor Pawn::getColor() const {
  return this->color;
}

void Pawn::draw() {
  if (this->drawingArea) {
    (*this->drawingArea).draw();
  }
}

void Pawn::setTexture(std::string texture) {
  this->texture_ = { std::move(texture) };
}
