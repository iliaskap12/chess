#include <sgg/graphics.h>
#include <sounds/Sound.h>

Sound::Sound() = default;

void Sound::setSound(const std::string &path) {
  this->soundPath = {path};
}

void Sound::play() const {
  graphics::playSound(this->soundPath, Sound::volume, Sound::looping);
}
