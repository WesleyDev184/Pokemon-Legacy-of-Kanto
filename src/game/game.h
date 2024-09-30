#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <memory>
#include "../player/player.h"
#include "../pokemon/pokemon.h"
#include "../move/move.h"
#include "../type/type.h"

using namespace std;

class Game
{
private:
  vector<shared_ptr<Player>> players; // Usando smart pointers
  vector<shared_ptr<Type>> types;
  vector<shared_ptr<Pokemon>> pokemons;
  vector<shared_ptr<Move>> moves;
  int difficulty = 1; // 1 - easy, 2 - medium, 3 - hard

public:
  Game(/* args */) {};

  // game logic
  void drawPokemons(shared_ptr<Player> &player, shared_ptr<Player> &CPU) const; // Use shared_ptr como parâmetro
  double calculateDamage(const shared_ptr<Pokemon> &attacker, const shared_ptr<Pokemon> &defender, const shared_ptr<Move> &move) const;

  // Getters
  vector<shared_ptr<Player>> getPlayers() const;
  vector<shared_ptr<Type>> getTypes() const;
  vector<shared_ptr<Pokemon>> getPokemons() const;
  vector<shared_ptr<Pokemon>> getPokemonsByType(const string &type) const;
  vector<shared_ptr<Move>> getMoves() const;
  int getDifficulty() const;

  // Setters
  void setDifficulty(const int difficulty);
  void setNewPlayers(const shared_ptr<Player> player); // Use shared_ptr como parâmetro

  // Loaders
  void loadPlayersFromFile(const string &filePath);
  void loadMovesFromFile(const string &filePath);
  void loadEffectivenessFromFile(const string &filePath);
  void loadPokemonFromFile(const string &filePath);

  // Savers
  void savePlayersToFile(const string &filePath);
};

#endif
