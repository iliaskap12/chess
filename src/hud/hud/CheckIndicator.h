#ifndef CHECKINDICATOR_H
#define CHECKINDICATOR_H

#include "HUD.h"

class CheckIndicator : public HUD {

public:
  explicit CheckIndicator(const std::string &message, const std::pair<float, float> &coordinates, std::size_t size);
};

#endif// CHECKINDICATOR_H
