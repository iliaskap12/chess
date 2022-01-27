#include <hud/TurnIndicator.h>

TurnIndicator::TurnIndicator(const std::string &message, const std::pair<float, float> &coordinates, std::size_t size) : HUD(message, coordinates, size) {
  HUD::setTextBrush(Brush::DARK_BROWN);
}

void TurnIndicator::progress() {
  if (this->whitesTurn) {
    HUD::updateText(this->whitesTurnMessage);
  } else {
    HUD::updateText(this->blacksTurnMessage);
  }
}

void TurnIndicator::setTurn(bool white) {
  this->whitesTurn = {white};
}
