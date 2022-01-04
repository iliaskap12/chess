#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <graphics/Screen.h>
#include <App.h>
#include <game/Player.h>

SCENARIO ( "Pressing play" ) {
  auto app = App();
  app.run();
  GIVEN ( "that I'm on the opening screen" ) {
    auto screen = app.getScreen();
    // No active game on opening screen
    REQUIRE ( app.getGame() == nullptr );
    WHEN ( "I press the play button" ) {
      REQUIRE_NOTHROW( screen->pressButton(ButtonType::PLAY) );
      app.createNewGame();
      auto game = app.getGame();
      THEN ( "I pick a name and a side" ) {
        auto player1 = Player("player1", Side::WHITE);
        auto player2 = Player("player2", Side::BLACK);
        game->registerPlayers(std::make_pair(player1, player2));
        AND_THEN ( "the game starts" ) {
          REQUIRE ( game->start() );
        }
      }
    }
  }
}
