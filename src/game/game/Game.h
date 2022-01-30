
#ifndef GAME_H
#define GAME_H

#include <optional>
#include "Player.h"
#include <graphics/Drawable.h>
#include <graphics/Updateable.h>
#include "Checkboard.h"

class Game : public Drawable, public Updateable, public std::enable_shared_from_this<Game> {
private:
  std::optional<std::pair<Player, Player>> players;
  std::shared_ptr<Checkboard> checkboard{std::make_shared<Checkboard>()};
  bool whiteTurn_{true};
  bool isGameEnded{false};
  std::optional<PawnColor> winner{std::make_optional<PawnColor>()};
  EndgameSound checkmateSound{EndgameSound()};
  CheckSound checkSound{CheckSound()};
  std::optional<PawnColor> checkedColor{};

public:
  Game();
  bool start();
  void registerPlayers(const std::pair<Player, Player> &pair);
  [[nodiscard]] const Player &getPlayer(PawnColor side);
  [[nodiscard]] std::shared_ptr<Checkboard> getCheckboard() const;
  void draw() override;
  void update(float ms) override;
  [[nodiscard]] bool isWhiteTurn() const;
  void setWhiteTurn(bool white_turn);
  void end(PawnColor color);
  [[nodiscard]] std::pair<bool, std::optional<PawnColor>> hasGameEnded() const;
  [[nodiscard]] std::optional<PawnColor> isChecked();
  void playCheckSound() const;
};

#endif // GAME_H
