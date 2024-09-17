#include "pokemon.h"
#include <fstream>
#include <sstream>
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

string Pokemon::getType1() const
{
  return this->type1;
}
string Pokemon::getType2() const
{
  return this->type2;
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

void Pokemon::print() const
{
  cout << "Pokemon: " << this->name << ", "
       << "Type1: " << this->type1 << ", "
       << "Type2: " << this->type2 << ", "
       << "HP: " << this->hp << ", "
       << "Level: " << this->level << ", "
       << "Attack: " << this->attack << ", "
       << "Defense: " << this->defense << ", "
       << "Speed: " << this->speed << ", "
       << "Special Attack: " << this->specialAttack << ", "
       << "Special Defense: " << this->specialDefense
       << endl;
}

void loadPokemonFromFile(const string &filePath, vector<Pokemon> *pokemons)
{
  ifstream file(filePath);

  if (!file.is_open())
  {
    cerr << "Error: Could not open file " << filePath << endl;
    return;
  }

  string line;
  // Ignorar a primeira linha (cabeçalho)
  getline(file, line);

  while (getline(file, line))
  {
    stringstream ss(line);
    string name, type1, type2;
    int hp, level, attack, defense, speed, specialAttack, specialDefense;

    // Dividir a linha pelos campos, assumindo que eles são separados por vírgulas
    getline(ss, name, ',');
    getline(ss, type1, ',');
    getline(ss, type2, ',');
    ss >> hp;
    ss.ignore();
    ss >> level;
    ss.ignore();
    ss >> attack;
    ss.ignore();
    ss >> defense;
    ss.ignore();
    ss >> speed;
    ss.ignore();
    ss >> specialAttack;
    ss.ignore();
    ss >> specialDefense;

    // Criar o objeto Pokemon e adicionar ao vetor
    pokemons->emplace_back(name, type1, type2, hp, level, attack, defense, speed, specialAttack, specialDefense);
  }

  file.close();
}