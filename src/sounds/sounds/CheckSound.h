#ifndef CHESS_CHECKSOUND_H
#define CHESS_CHECKSOUND_H

#include "Sound.h"
#include <util/paths.h>

class CheckSound : public Sound {
  const std::string soundPath{paths::getSoundsPath() + "check.mp3"};

public:
  CheckSound();
};

#endif//CHESS_CHECKSOUND_H
