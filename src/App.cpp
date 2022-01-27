#include <App.h>
#include <functional>
#include <util/paths.h>

App::App() = default;

std::shared_ptr<Screen> App::getScreen() const {
  return this->activeScreen;
}

void App::run() {
  graphics::createWindow(1920, 1080, "Chess");
  graphics::preloadBitmaps(paths::getImagesPath());

  graphics::setUserData(this);
  graphics::setDrawFunction(std::bind_front(&App::draw, this));
  graphics::setUpdateFunction(std::bind_front(&App::update, this));
  graphics::setCanvasSize(3200, 1900);
  graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
  graphics::setFont(paths::getFontsPath() + "typography-times.ttf");
  Rectangle::populateBrushes();
  this->activeScreen = {std::make_shared<OpeningScreen>()};

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
  this->activeScreen = {std::move(screen)};
}

void App::registerGame(Game *game) {
  this->game_ = {game};
}

Game *App::getGame() const {
  return this->game_;
}
