#include "pokemon.h"
#include <iostream>

// Construtor
Pokemon::Pokemon(const string &name, const string &type1, const string &type2,
                 int hp, int level, int attack, int defense, int speed, int specialAttack, int specialDefense)
{
  this->name = new string(name);
  this->type1 = new Type(type1);
  this->type2 = new Type(type2);
  this->hp = hp;
  this->level = level;
  this->attack = attack;
  this->defense = defense;
  this->speed = speed;
  this->specialAttack = specialAttack;
  this->specialDefense = specialDefense;
}

// Destrutor
Pokemon::~Pokemon()
{
  delete name;
  delete type1;
  delete type2;

  for (Move *move : moves)
  {
    delete move; // Libera a memória alocada para cada movimento
  }
}

// Getters
string Pokemon::getName() const
{
  return *name;
}

vector<Type *> Pokemon::getTypes() const
{
  return {type1, type2};
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

vector<Move *> Pokemon::getMoves() const
{
  return this->moves;
}

// Setters
void Pokemon::setMoves(const vector<Move *> &moves)
{
  for (Move *move : this->moves)
  {
    delete move; // Libera a memória antiga dos movimentos
  }
  this->moves = moves; // Define os novos movimentos
}

void Pokemon::setTypes(const vector<Type *> &types)
{
  if (types.size() >= 2)
  {
    *this->type1 = *types[0];
    *this->type2 = *types[1];
  }
}
  
// Método print
void Pokemon::print() const
{
  cout << "Pokemon: " << *name << ", "
       << "Type1: " << type1->getName() << ", "
       << "Type2: " << type2->getName() << ", "
       << "HP: " << hp << ", "
       << "Level: " << level << ", "
       << "Attack: " << attack << ", "
       << "Defense: " << defense << ", "
       << "Speed: " << speed << ", "
       << "Special Attack: " << specialAttack << ", "
       << "Special Defense: " << specialDefense
       << endl;

  cout << "Moves: ";
  for (Move *move : moves)
  {
    cout << move->getName() << " "; // Supondo que Move tenha um método getName()
  }
  cout << endl;
}
