#include <App.h>
#include <util/paths.h>

App::App() = default;

std::shared_ptr<Screen> App::getScreen() const {
  return this->activeScreen;
}

std::unique_ptr<Game> App::getGame() const {
  if (!this->game) {
    return nullptr;
  }
  return std::make_unique<Game>(*this->game);
}

void App::createNewGame() {
  this->game = Game();
}

void App::run() {
  graphics::createWindow(1024, 768, "Chess");
//  graphics::setFullScreen(true);
  graphics::preloadBitmaps(getImagesPath());

  graphics::setUserData(this);
  graphics::setDrawFunction(std::bind_front(&App::draw, this));
  graphics::setUpdateFunction(std::bind_front(&App::update, this));
  graphics::setCanvasSize(1024, 768);
  graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
  graphics::setFont(getFontsPath() + "typography-times.ttf");

  graphics::startMessageLoop();
  graphics::destroyWindow();
}

void App::draw() {
  this->activeScreen->draw();
  if (this->game) {
    (*this->game).draw();
  }
}

void App::update(float ms) {
  this->activeScreen->update(ms);
  if (this->game) {
    (*this->game).update(ms);
  }
}

