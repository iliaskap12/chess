#ifndef ENDGAMEINDICATOR_H
#define ENDGAMEINDICATOR_H

#include "HUD.h"

class EndgameIndicator : public HUD {

public:
  explicit EndgameIndicator(const std::string &message, const std::pair<float, float> &coordinates, std::size_t size);
};

#endif// ENDGAMEINDICATOR_H
