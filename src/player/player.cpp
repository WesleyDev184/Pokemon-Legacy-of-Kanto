#include "Player.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Construtor
Player::Player(const string &name, int score, int victories, int defeats)
    : name(name), score(score), victories(victories), defeats(defeats) {}

// Getters
string Player::getName() const
{
  return this->name;
}
int Player::getScore() const
{
  return this->score;
}
int Player::getVictories() const
{
  return this->victories;
}
int Player::getDefeats() const
{
  return this->defeats;
}

void Player::print() const
{
  cout << "Player: " << this->name << ", "
       << "Score: " << this->score << ", "
       << "Victories: " << this->victories << ", "
       << "Defeats: " << this->defeats
       << endl;
}

// Setters
void Player::setPokemons(const vector<Pokemon> &pokemons)
{
  this->pokemons = pokemons;
}

void loadPlayersFromFile(const string &filePath, vector<Player> *players)
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
    string name;
    int score, victories, defeats;

    // Dividir a linha pelos campos, assumindo que eles são separados por vírgulas
    getline(ss, name, ',');
    ss >> score;
    ss.ignore();
    ss >> victories;
    ss.ignore();
    ss >> defeats;

    // Criar o objeto Player e adicionar ao vetor
    players->emplace_back(name, score, victories, defeats);
  }

  file.close();
}