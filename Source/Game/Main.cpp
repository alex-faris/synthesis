#include <iostream>

#include "Game.hpp"

int main()
{
  try
  {
    Game::Game game;

    game.Init();
    game.Run();
    game.Shutdown();
  }
  catch (const std::exception& kException)
  {
    std::cerr << kException.what() << ::std::endl;
    return -1;
  }

  return 0;
}
