#ifndef POKEMON_H
#define POKEMON_H

#include <vector>
#include <string>
#include "../move/move.h"

using namespace std;

class Pokemon
{
private:
  string name;
  string type1;
  string type2;
  int hp;
  int level;
  int attack;
  int defense;
  int speed;
  int specialAttack;
  int specialDefense;
  vector<Move> moves;

public:
  // Construtor
  Pokemon(const string &name, const string &type1, const string &type2,
          int hp, int level, int attack, int defense, int speed, int specialAttack, int specialDefense);

  // Getters
  string getName() const;
  string getType1() const;
  string getType2() const;
  int getHP() const;
  int getLevel() const;
  int getAttack() const;
  int getDefense() const;
  int getSpeed() const;
  int getSpecialAttack() const;
  int getSpecialDefense() const;
  vector<Move> getMoves() const;

  // Setters
  void setMoves(const vector<Move> &moves);

  void print() const;
};

void loadPokemonFromFile(const std::string &filePath, std::vector<Pokemon> *pokemons);

#endif
