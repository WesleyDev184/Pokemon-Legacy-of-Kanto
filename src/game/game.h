#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "../player/player.h"
#include "../pokemon/pokemon.h"
#include "../move/move.h"

using namespace std;

class Game
{
private:
  vector<Player> players;
  vector<Pokemon> pokemons;
  vector<Move> moves;
  int difficulty; // 1 - easy, 2 - medium, 3 - hard

public:
  Game(/* args */);
};

#endif
