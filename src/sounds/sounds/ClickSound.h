#ifndef CLICKSOUND_H
#define CLICKSOUND_H

#include "Sound.h"
#include <util/paths.h>

class ClickSound : public Sound {
  const std::string soundPath{paths::getSoundsPath() + "click.mp3"};

public:
  ClickSound();
};

#endif// CLICKSOUND_H
