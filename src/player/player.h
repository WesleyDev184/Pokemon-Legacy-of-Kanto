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
  vector<Pokemon *> pokemons; // Vetor de ponteiros para Pokémon

public:
  // Construtor
  Player() : score(0), victories(0), defeats(0) {};
  Player(const string &name, int score, int victories, int defeats);

  // Destrutor para liberar memória
  ~Player();

  // Getters
  string getName() const;
  int getScore() const;
  int getVictories() const;
  int getDefeats() const;
  vector<Pokemon *> getPokemons() const; // Retorna ponteiros

  // Setters
  void setScore(const int score);
  void setVictories(const int victories);
  void setDefeats(const int defeats);
  void setPokemons(const vector<Pokemon *> &pokemons); // Define ponteiros

  void addPokemon(Pokemon *pokemon); // Adiciona um ponteiro de Pokémon
  void print() const;
};

#endif
