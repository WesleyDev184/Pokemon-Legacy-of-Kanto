#include "pokemon.h"
#include <iostream>
#include <iomanip>

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

int Pokemon::getHp() const
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

vector<Move> &Pokemon::getMoves()
{
  return this->moves;
}

const vector<Move> &Pokemon::getMoves() const
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

void Pokemon::setHp(int hp)
{
  this->hp = hp;
}

void Pokemon::print() const
{
  cout << "==============================" << endl;
  cout << "Pokemon: " << this->name << endl;
  cout << "==============================" << endl;
  cout << left << setw(20) << "Type1: " << this->type1.getName() << endl;
  cout << left << setw(20) << "Type2: " << this->type2.getName() << endl;
  cout << left << setw(20) << "HP: " << this->hp << endl;
  cout << left << setw(20) << "Level: " << this->level << endl;
  cout << left << setw(20) << "Attack: " << this->attack << endl;
  cout << left << setw(20) << "Defense: " << this->defense << endl;
  cout << left << setw(20) << "Speed: " << this->speed << endl;
  cout << left << setw(20) << "Special Attack: " << this->specialAttack << endl;
  cout << left << setw(20) << "Special Defense: " << this->specialDefense << endl;
  cout << "==============================" << endl
       << endl;
}
