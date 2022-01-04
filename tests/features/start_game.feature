Feature: Start game
  As a player,
  when I press the play button,
  I want to pick a name and a side,
  and I want to start a game of chess.

  Scenario: Pressing play
    Given that I'm on the opening screen
    When I press the play button
    Then I pick a name and a side,
    And the game starts
