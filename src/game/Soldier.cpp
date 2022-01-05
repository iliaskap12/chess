#include <game/Soldier.h>

Soldier::Soldier(PawnColor color) : Pawn(color) {
  Pawn::setTexture("soldier");
}

void Soldier::update(float ms) {
//  Pawn::update(ms);
}
