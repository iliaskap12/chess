#ifndef TURNINDICATOR_H
#define TURNINDICATOR_H

#include "HUD.h"

class TurnIndicator : public HUD {
  bool whitesTurn{true};
  const std::string whitesTurnMessage{"White's turn"};
  const std::string blacksTurnMessage{"Black's turn"};

public:
  explicit TurnIndicator(const std::string &message, const std::pair<float, float> &coordinates, std::size_t size);
  void progress();
  void setTurn(bool white);
};

#endif // TURNINDICATOR_H
