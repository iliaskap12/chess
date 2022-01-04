//
// Created by ilias on 2/1/22.
//

#ifndef CHESS_APP_H
#define CHESS_APP_H

#include <memory>
#include "graphics/Screen.h"
#include "graphics/OpeningScreen.h"
#include "game/Game.h"
#include <sgg/graphics.h>

class App : public Drawable, public Updateable {
private:
  std::shared_ptr<Screen> activeScreen = std::make_shared<OpeningScreen>();
  std::optional<Game> game;

public:
  App();
  void createNewGame();
  [[nodiscard]] std::shared_ptr<Screen> getScreen() const;
  [[nodiscard]] std::unique_ptr<Game> getGame() const;
  void run();
  void draw() override;
  void update(float ms) override;
};

#endif//CHESS_APP_H
