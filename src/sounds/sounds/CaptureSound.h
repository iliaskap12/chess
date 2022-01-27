#ifndef CAPTURESOUND_H
#define CAPTURESOUND_H

#include "Sound.h"
#include <util/paths.h>

class CaptureSound : public Sound {
  const std::string soundPath{paths::getSoundsPath() + "fall.mp3"};

public:
  CaptureSound();
};

#endif// CAPTURESOUND_H
