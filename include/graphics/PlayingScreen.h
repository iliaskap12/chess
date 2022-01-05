#ifndef PLAYINGSCREEN_H
#define PLAYINGSCREEN_H

#include "Screen.h"
#include "game/Game.h"

class PlayingScreen : public Screen {
  std::shared_ptr<Game> game { std::make_shared<Game>() };

public:
  PlayingScreen();
  [[nodiscard]] std::shared_ptr<Game> getGame() const;
  void draw() override;
  void update(float ms) override;
};

#endif // PLAYINGSCREEN_H
