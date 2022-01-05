#include <game/King.h>

King::King(PawnColor color) : Pawn(color) {
  Pawn::setTexture("king");
}

void King::update(float ms) {
//  Pawn::update(ms);
}
