//
// Created by ilias on 9/1/22.
//

#ifndef CHESS_PAWNCOUNT_H
#define CHESS_PAWNCOUNT_H

#include "HUD.h"

class PawnCount : public HUD {

public:
  explicit PawnCount(std::pair<float, float> coordinates, size_t size);
};


#endif//CHESS_PAWNCOUNT_H
