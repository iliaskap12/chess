#ifndef CHESS_APP_H
#define CHESS_APP_H

#include <memory>
#include <graphics/Screen.h>
#include <graphics/OpeningScreen.h>
#include <game/Game.h>
#include <sgg/graphics.h>

class App : public Drawable, public Updateable {
  std::shared_ptr<Screen> activeScreen{nullptr};
  Game *game_{nullptr};
  std::string input{};

public:
  App();
  [[nodiscard]] std::shared_ptr<Screen> getScreen() const;
  void changeScreen(std::shared_ptr<Screen> screen);
  void registerGame(Game* game);
  [[nodiscard]] Game *getGame() const;
  void run();
  void draw() override;
  void update(float ms) override;
};

#endif//CHESS_APP_H
