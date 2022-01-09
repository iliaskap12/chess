#include <hud/PawnCount.h>

PawnCount::PawnCount(std::pair<float, float> coordinates, size_t size) : HUD("", coordinates, size) {
  HUD::setTextBrush(Brush::DARK_BROWN);
}
