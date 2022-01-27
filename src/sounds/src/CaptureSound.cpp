#include <sounds/CaptureSound.h>

CaptureSound::CaptureSound() {
  Sound::setSound(this->soundPath);
}
