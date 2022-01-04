#include <game/Soldier.h>

Soldier::Soldier(PawnColor color) {
  Pawn::color = color;
}

void Soldier::update(float ms) {
  Pawn::update(ms);
}

void Soldier::draw() {
  Pawn::draw();
}
