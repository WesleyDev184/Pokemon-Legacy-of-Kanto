#ifndef POKEMON_H
#define POKEMON_H

#include <vector>
#include <string>
#include "../move/move.h"
#include "../type/type.h"

using namespace std;

class Pokemon
{
private:
  string name;
  Type type1;
  Type type2;
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
  vector<Type> getTypes() const;

  int getHP() const;
  int getLevel() const;
  int getAttack() const;
  int getDefense() const;
  int getSpeed() const;
  int getSpecialAttack() const;
  int getSpecialDefense() const;
  vector<Move> &getMoves();
  const vector<Move> &getMoves() const;

  // Setters
  void setMoves(const vector<Move> &moves);
  void setTypes(const vector<Type> &types);

  void print() const;
};

#endif
