#include "pokemon.h"
#include <iostream>

using namespace std;

// Construtor
Pokemon::Pokemon(const string &name, const string &type1, const string &type2,
                 int hp, int level, int attack, int defense, int speed, int specialAttack, int specialDefense)
    : name(name), type1(type1), type2(type2), hp(hp), level(level), attack(attack), defense(defense),
      speed(speed), specialAttack(specialAttack), specialDefense(specialDefense) {}

// Getters
string Pokemon::getName() const
{
  return this->name;
}

vector<Type> Pokemon::getTypes() const
{
  return {this->type1, this->type2};
}

int Pokemon::getHP() const
{
  return this->hp;
}

int Pokemon::getLevel() const
{
  return this->level;
}

int Pokemon::getAttack() const
{
  return this->attack;
}

int Pokemon::getDefense() const
{
  return this->defense;
}

int Pokemon::getSpeed() const
{
  return this->speed;
}

int Pokemon::getSpecialAttack() const
{
  return this->specialAttack;
}

int Pokemon::getSpecialDefense() const
{
  return this->specialDefense;
}

vector<Move> Pokemon::getMoves() const
{
  return this->moves;
}

// Setters
void Pokemon::setMoves(const vector<Move> &moves)
{
  this->moves = moves;
}

void Pokemon::setTypes(const vector<Type> &types)
{
  for (auto &type : types)
  {
    if (this->type1.getName() == type.getName())
    {
      this->type1 = type;
    }
    if (this->type2.getName() == type.getName())
    {
      this->type2 = type;
    }
  }
}

void Pokemon::print() const
{
  cout << "Pokemon: " << this->name << ", "
       << "Type1: " << this->type1.getName() << ", "
       << "Type2: " << this->type2.getName() << ", "
       << "HP: " << this->hp << ", "
       << "Level: " << this->level << ", "
       << "Attack: " << this->attack << ", "
       << "Defense: " << this->defense << ", "
       << "Speed: " << this->speed << ", "
       << "Special Attack: " << this->specialAttack << ", "
       << "Special Defense: " << this->specialDefense
       << endl;
}
