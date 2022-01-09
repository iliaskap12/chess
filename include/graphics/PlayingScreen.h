#ifndef PLAYINGSCREEN_H
#define PLAYINGSCREEN_H

#include "Screen.h"
#include "game/Game.h"
#include "hud/PawnCount.h"

class PlayingScreen : public Screen {
  static constexpr unsigned short int numberOfUniquePawns { 6 };
  using Squares = std::array<std::pair<std::shared_ptr<Square>, std::pair<int, std::shared_ptr<PawnCount>>>, PlayingScreen::numberOfUniquePawns>;

  std::shared_ptr<Squares> capturedWhiteSquares { std::make_shared<Squares>() };
  std::shared_ptr<Squares> capturedBlackSquares { std::make_shared<Squares>() };
  std::shared_ptr<Game> game { std::make_shared<Game>() };

public:
  PlayingScreen();
  void draw() override;
  void update(float ms) override;
  [[nodiscard]] std::shared_ptr<Square> getSquare(const std::shared_ptr<Pawn>& pawn) const;
};

#endif // PLAYINGSCREEN_H
