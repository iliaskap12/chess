
#ifndef GAME_H
#define GAME_H

#include <optional>
#include "Player.h"
#include "graphics/Drawable.h"
#include "graphics/Updateable.h"
#include "Checkboard.h"

class Game : public Drawable, public Updateable{
private:
  std::optional<std::pair<Player, Player>> players;
  std::shared_ptr<Checkboard> checkboard { std::make_shared<Checkboard>() };

public:
  Game();
  bool start();
  void registerPlayers(const std::pair<Player, Player> &pair);
  const Player &getPlayer(PawnColor side);
  [[nodiscard]] std::shared_ptr<Checkboard> getCheckboard() const;
  void draw() override;
  void update(float ms) override;
};

#endif // GAME_H
