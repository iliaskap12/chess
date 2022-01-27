#ifndef ENDGAMESOUND_H
#define ENDGAMESOUND_H

#include "Sound.h"
#include <util/paths.h>

class EndgameSound : public Sound {
  const std::string soundPath{paths::getSoundsPath() + "checkmate.mp3"};

public:
  EndgameSound();
};

#endif// ENDGAMESOUND_H
