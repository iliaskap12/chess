#ifndef PLAYINGSCREEN_H
#define PLAYINGSCREEN_H

#include "Screen.h"
#include <hud/EndgameIndicator.h>
#include <game/Game.h>
#include <hud/PawnCount.h>
#include <hud/TurnIndicator.h>
#include <hud/CheckIndicator.h>

class PlayingScreen : public Screen {
  static constexpr unsigned short int numberOfUniquePawns{6};
  using Squares = std::array<std::pair<std::shared_ptr<Square>, std::pair<int, std::shared_ptr<PawnCount>>>, PlayingScreen::numberOfUniquePawns>;

  std::shared_ptr<Squares> capturedWhiteSquares{std::make_shared<Squares>()};
  std::shared_ptr<Squares> capturedBlackSquares{std::make_shared<Squares>()};
  std::shared_ptr<Game> game{std::make_shared<Game>()};
  const std::string message{"White's turn"};
  const std::pair<float, float> coordinates{std::make_pair(2100 - static_cast<float>(this->message.length() * 180) / 2, 240)};
  const std::size_t size{180};
  std::shared_ptr<TurnIndicator> turn{std::make_shared<TurnIndicator>(this->message, this->coordinates, this->size)};
  std::shared_ptr<EndgameIndicator> endgame{nullptr};
  std::shared_ptr<CheckIndicator> check{nullptr};

public:
  PlayingScreen();
  void draw() override;
  void update(float ms) override;
  [[nodiscard]] std::shared_ptr<Square> getSquare(const std::shared_ptr<Pawn> &pawn) const;
  void changeTurn(float ms);
  void updatePawnCount(float ms, PawnColor color);
  void displayCheckmate(float ms);
  void displayCheck(float ms);
};

#endif // PLAYINGSCREEN_H
