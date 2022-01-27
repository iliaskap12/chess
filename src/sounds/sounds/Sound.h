#ifndef SOUND_H
#define SOUND_H

#include <string>

class Sound {
  std::string soundPath{};
  static constexpr bool looping{false};
  static constexpr float volume{1.0f};

protected:
  Sound();

public:
  void play() const;
  void setSound(const std::string &path);
};

#endif// SOUND_H
