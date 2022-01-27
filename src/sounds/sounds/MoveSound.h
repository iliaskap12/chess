#ifndef MOVESOUND_H
#define MOVESOUND_H

#include "Sound.h"
#include <util/paths.h>

class MoveSound : public Sound {
  const std::string soundPath{paths::getSoundsPath() + "slide.mp3"};

public:
  MoveSound();
};

#endif// MOVESOUND_H
