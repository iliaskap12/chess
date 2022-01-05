//
// Created by ilias on 2/1/22.
//

#ifndef CHESS_APP_H
#define CHESS_APP_H

#include <memory>
#include "graphics/Screen.h"
#include "graphics/OpeningScreen.h"
#include <sgg/graphics.h>

class App : public Drawable, public Updateable {
  std::shared_ptr<Screen> activeScreen = std::make_shared<OpeningScreen>();

public:
  App();
  [[nodiscard]] std::shared_ptr<Screen> getScreen() const;
  void changeScreen(std::shared_ptr<Screen> screen);
  void run();
  void draw() override;
  void update(float ms) override;
};

#endif//CHESS_APP_H
