#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "../player/player.h"
#include "../pokemon/pokemon.h"
#include "../move/move.h"
#include "../type/type.h"

using namespace std;

class Game
{
private:
  vector<Player*> players;  // Vetor de ponteiros para Player
  vector<Type*> types;      // Vetor de ponteiros para Type
  vector<Pokemon*> pokemons; // Vetor de ponteiros para Pokemon
  vector<Move*> moves;       // Vetor de ponteiros para Move
  int difficulty = 1;        // 1 - easy, 2 - medium, 3 - hard

public:
  Game() {};

  ~Game();  // Destrutor para liberar memória

  // Lógica do jogo
  void drawPokemons(Player* player, Player* CPU) const;
  double calculateDamage(const Pokemon* attacker, const Pokemon* defender, const Move* move) const;

  // Getters
  vector<Player*> getPlayers() const;
  vector<Type*> getTypes() const;
  vector<Pokemon*> getPokemons() const;
  vector<Pokemon*> getPokemonsByType(const string &type) const;
  vector<Move*> getMoves() const;
  int getDifficulty() const;

  // Setters
  void setDifficulty(const int difficulty);
  void setNewPlayer(Player* player);

  // Loaders
  void loadPlayersFromFile(const string &filePath);
  void loadMovesFromFile(const string &filePath);
  void loadEffectivenessFromFile(const string &filePath);
  void loadPokemonFromFile(const string &filePath);

  // Savers
  void savePlayersToFile(const string &filePath);
};

#endif
