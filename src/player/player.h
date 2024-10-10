#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "../pokemon/pokemon.h"

using namespace std;

class Player
{
private:
  string name;
  int score;
  int victories;
  int defeats;
  vector<Pokemon> pokemons;

public:
  // Construtor
  Player() {};
  Player(const string &name, int score, int victories, int defeats);

  // Getters
  string getName() const;
  int getScore() const;
  int getVictories() const;
  int getDefeats() const;
  vector<Pokemon> &getPokemons();
  const vector<Pokemon> &getPokemons() const;

  // Setters
  void setScore(const int score);
  void setVictories(const int victories);
  void setDefeats(const int defeats);
  void setPokemons(const vector<Pokemon> &pokemons);

  void print() const;
};

#endif
