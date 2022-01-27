#include <sounds/ClickSound.h>

ClickSound::ClickSound() {
  Sound::setSound(this->soundPath);
}
