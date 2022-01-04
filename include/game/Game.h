
#ifndef GAME_H
#define GAME_H

#include <optional>
#include "Player.h"
#include "graphics/Drawable.h"
#include "graphics/Updateable.h"

class Game : public Drawable, public Updateable{
private:
  std::optional<std::pair<Player, Player>> players;

public:
  Game();
  bool start();
  void registerPlayers(const std::pair<Player, Player> &pair);
  const Player &getPlayer(Side side);
  
};

#endif // GAME_H
