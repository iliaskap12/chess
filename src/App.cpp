#include <App.h>
#include <util/paths.h>

App::App() = default;

std::shared_ptr<Screen> App::getScreen() const {
  return this->activeScreen;
}

void App::run() {
  graphics::createWindow(1024, 768, "Chess");
  graphics::preloadBitmaps(getImagesPath());

  graphics::setUserData(this);
  graphics::setDrawFunction(std::bind_front(&App::draw, this));
  graphics::setUpdateFunction(std::bind_front(&App::update, this));
  graphics::setCanvasSize(1200, 1020);
  graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
  graphics::setFont(getFontsPath() + "typography-times.ttf");

  graphics::startMessageLoop();
  graphics::destroyWindow();
}

void App::draw() {
  this->activeScreen->draw();
}

void App::update(float ms) {
  this->activeScreen->update(ms);
}

void App::changeScreen(std::shared_ptr<Screen> screen) {
  this->activeScreen = { std::move(screen) };
}
