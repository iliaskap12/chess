#ifndef PLAYINGSCREEN_H
#define PLAYINGSCREEN_H

#include "Screen.h"
#include <hud/EndgameIndicator.h>
#include <game/Game.h>
#include <hud/PawnCount.h>
#include <hud/TurnIndicator.h>
#include <hud/CheckIndicator.h>
#include "InGameMenu.h"
#include <game/Soldier.h>

class PlayingScreen : public Screen {
  static constexpr unsigned short int numberOfUniquePawns{6};
  using Squares = std::array<std::pair<std::shared_ptr<Square>, std::pair<int, std::shared_ptr<PawnCount>>>, PlayingScreen::numberOfUniquePawns>;

  std::shared_ptr<Squares> capturedWhiteSquares{std::make_shared<Squares>()};
  std::shared_ptr<Squares> capturedBlackSquares{std::make_shared<Squares>()};
  std::shared_ptr<Game> game{std::make_shared<Game>()};
  const std::string message{"White's turn"};
  std::pair<float, float> coordinates;
  const std::size_t size{180};
  std::shared_ptr<TurnIndicator> turn{nullptr};
  std::shared_ptr<EndgameIndicator> endgame{nullptr};
  std::shared_ptr<CheckIndicator> check{nullptr};
  std::unique_ptr<Menu> gameMenu{std::make_unique<InGameMenu>()};
  std::shared_ptr<std::array<std::shared_ptr<Square>, static_cast<std::size_t>(4)>> choices{std::make_shared<std::array<std::shared_ptr<Square>, static_cast<std::size_t>(4)>>()};
  bool promotion{false};
  std::weak_ptr<Soldier> promotionPawn_{std::weak_ptr<Soldier>()};
  bool stopUpdating{false};

public:
  PlayingScreen();
  void draw() override;
  void update(float ms) override;
  [[nodiscard]] std::shared_ptr<Square> getSquare(const std::shared_ptr<Pawn> &pawn) const;
  void changeTurn(float ms);
  void updatePawnCount(float ms, PawnColor color);
  void displayCheckmate(float ms);
  void displayCheck(float ms);
  [[nodiscard]] const std::shared_ptr<Game> &getGame() const;
  void setPromotion(const std::shared_ptr<Soldier> &promotionPawn);
  void destroyChoices();
  void drawPromotionChoices();
  void cleanup() override;
};

#endif // PLAYINGSCREEN_H
