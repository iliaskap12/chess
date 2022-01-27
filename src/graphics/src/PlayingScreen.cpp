#include <graphics/PlayingScreen.h>
#include <util/custom-string.h>
#include <hud/PawnCount.h>
#include <filesystem>
#include <util/paths.h>

PlayingScreen::PlayingScreen() {
  constexpr float squareWidth{125.0f};
  for (unsigned short int white{0}; white < PlayingScreen::numberOfUniquePawns; ++white) {
    const Point leftBottom{Point(825.0f, 425.0f + static_cast<float>(white) * 125.0f)};
    (*this->capturedWhiteSquares)[white].first = {std::make_shared<Square>()};
    (*this->capturedWhiteSquares)[white].first->initialize(leftBottom, Rectangle::colors.at(Brush::TEXTURE), Brush::TEXTURE, squareWidth);
    const std::pair<float, float> coordinates{(*this->capturedWhiteSquares)[white].first->getDrawingArea()->getCenter().getX() - 125.0f,
                                              (*this->capturedWhiteSquares)[white].first->getDrawingArea()->getCenter().getY() + 50.0f};
    (*this->capturedWhiteSquares)[white].second = {std::make_pair(0, std::make_shared<PawnCount>(coordinates, squareWidth - 20.0f))};
  }

  for (unsigned short int black { 0 }; black < PlayingScreen::numberOfUniquePawns; ++black) {
    const Point leftBottom{Point(825.0f, 1550.0f - static_cast<float>(black) * 125.0f)};
    (*this->capturedBlackSquares)[black].first = {std::make_shared<Square>()};
    (*this->capturedBlackSquares)[black].first->initialize(leftBottom, Rectangle::colors.at(Brush::TEXTURE), Brush::TEXTURE, squareWidth);
    const std::pair<float, float> coordinates{(*this->capturedBlackSquares)[black].first->getDrawingArea()->getCenter().getX() - 125.0f,
                                              (*this->capturedBlackSquares)[black].first->getDrawingArea()->getCenter().getY() + 50.0f};
    (*this->capturedBlackSquares)[black].second = {std::make_pair(0, std::make_shared<PawnCount>(coordinates, squareWidth - 20.0f))};
  }
}

void PlayingScreen::draw() {
  this->game->draw();
  if (!this->game->hasGameEnded().first) {
    if (this->turn != nullptr) {
      this->turn->draw();
    }
    if (this->check != nullptr) {
      this->check->draw();
    }
  } else {
    if (this->endgame != nullptr) {
      this->endgame->draw();
    }
  }
  for (unsigned short int i{0}; i < PlayingScreen::numberOfUniquePawns; ++i) {
    if ((*this->capturedWhiteSquares)[i].second.first != 0) {
      (*this->capturedWhiteSquares)[i].first->draw();
      (*this->capturedWhiteSquares)[i].second.second->draw();
    }

    if ((*this->capturedBlackSquares)[i].second.first != 0) {
      (*this->capturedBlackSquares)[i].first->draw();
      (*this->capturedBlackSquares)[i].second.second->draw();
    }
  }
}

void PlayingScreen::update(float ms) {
  this->game->update(ms);
  if (!this->game->hasGameEnded().first) {
    this->displayCheck(ms);
  } else {
    this->displayCheckmate(ms);
  }
  this->updatePawnCount(ms, PawnColor::WHITE);
  this->updatePawnCount(ms, PawnColor::BLACK);
}

void PlayingScreen::updatePawnCount(float ms, PawnColor color) {
  const auto squares{color == PawnColor::WHITE ? this->capturedWhiteSquares : this->capturedBlackSquares};
  for (unsigned short int i{0}; i < PlayingScreen::numberOfUniquePawns; ++i) {
    if ((*squares)[i].second.first != 0) {
      (*squares)[i].first->update(ms);
      if ((*squares)[i].second.first > 0) {
        (*squares)[i].second.second->updateText(std::to_string((*squares)[i].second.first));
        (*squares)[i].second.second->update(ms);
      }
    }
  }
}

std::shared_ptr<Square> PlayingScreen::getSquare(const std::shared_ptr<Pawn>& pawn) const {
  const std::string& texture { pawn->getTexture() };
  std::vector<std::string> directories{custom_string::split(texture, std::to_string(std::filesystem::path::preferred_separator))};
  const std::string pawnType{custom_string::split(directories.at(directories.size() - 1), "-").at(0)};
  std::size_t index;
  const PawnColor color { pawn->getColor() };

  switch (stringHash(pawnType.c_str())) {
    case "soldier"_hash:
      index = { 0 };
      break;
    case "rook"_hash:
      index = { 1 };
      break;
    case "knight"_hash:
      index = { 2 };
      break;
    case "bishop"_hash:
      index = { 3 };
      break;
    case "queen"_hash:
      index = { 4 };
      break;
    default:
      return nullptr;
  }

  std::shared_ptr<Square> square { nullptr };
  if (color == PawnColor::WHITE) {
    square = { (*this->capturedWhiteSquares)[index].first };
    ++(*this->capturedWhiteSquares)[index].second.first;
  } else {
    square = { (*this->capturedBlackSquares)[index].first };
    ++(*this->capturedBlackSquares)[index].second.first;
  }

  if (square->hasPawn()) {
    return nullptr;
  }

  graphics::Brush textureBrush{Rectangle::colors.at(Brush::TEXTURE)};
  textureBrush.texture = {paths::getImagesPath() + texture + "-" + color + ".png"};

  square->initialize(square->getDrawingArea()->getLeftBottom(), textureBrush, Brush::TEXTURE, square->getDrawingArea()->getWidth());

  return square;
}

void PlayingScreen::changeTurn(float ms) {
  this->turn->setTurn(this->game->isWhiteTurn());
  this->turn->progress();
  this->turn->update(ms);
}

void PlayingScreen::displayCheckmate(float ms) {
  this->turn = {nullptr};
  const std::string winningMessage{"Checkmate, " + pawnColorToString(this->game->hasGameEnded().second.value()) + " wins!"};
  const auto newCoordinates{std::make_pair(2400 - static_cast<float>(winningMessage.length() * 180) / 2, 240)};
  this->endgame = {std::make_shared<EndgameIndicator>(EndgameIndicator(winningMessage, newCoordinates, this->size))};
  this->endgame->setTextBrush(Brush::DARK_BROWN);
  this->endgame->update(ms);
}

void PlayingScreen::displayCheck(float ms) {
  if (const auto checkedPawn{this->game->isChecked()}; checkedPawn.has_value()) {
    this->turn = {nullptr};
    std::string color{pawnColorToString(checkedPawn.value())};
    color[0] = {static_cast<char>(std::toupper(color[0]))};
    const std::string checkMessage{color + " is checked."};
    const auto newCoordinates{std::make_pair(2400 - static_cast<float>(checkMessage.length() * 180) / 2, 240)};
    this->check = {std::make_shared<CheckIndicator>(CheckIndicator(checkMessage, newCoordinates, this->size))};
    this->check->setTextBrush(Brush::DARK_BROWN);
    this->check->update(ms);
  } else {
    this->check = {nullptr};
    this->turn = {std::make_shared<TurnIndicator>(this->message, this->coordinates, this->size)};
    this->changeTurn(ms);
  }
}
