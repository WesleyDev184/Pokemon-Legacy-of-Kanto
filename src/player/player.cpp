#include "Player.h"
#include <iostream>

using namespace std;

// Construtor
Player::Player(const string &name, int score, int victories, int defeats)
    : name(name), score(score), victories(victories), defeats(defeats) {}

// Destrutor
Player::~Player()
{
  for (Pokemon *pokemon : pokemons)
  {
    delete pokemon; // Libera a memória de cada Pokémon
  }
}

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

vector<Pokemon *> Player::getPokemons() const
{
  return this->pokemons; // Retorna ponteiros
}

// Setters
void Player::setScore(int score)
{
  this->score = score;
}

void Player::setVictories(int victories)
{
  this->victories = victories;
}

void Player::setDefeats(int defeats)
{
  this->defeats = defeats;
}

void Player::setPokemons(const vector<Pokemon *> &pokemons)
{
  this->pokemons = pokemons; // Define ponteiros
}

// Adiciona um Pokémon ao vetor
void Player::addPokemon(Pokemon *pokemon)
{
  pokemons.push_back(pokemon); // Adiciona o ponteiro ao vetor
}

void Player::print() const
{
  cout << "Player: " << this->name << ", "
       << "Score: " << this->score << ", "
       << "Victories: " << this->victories << ", "
       << "Defeats: " << this->defeats
       << endl;

  cout << "Pokémons: ";
  for (const Pokemon *pokemon : pokemons)
  {
    cout << pokemon->getName() << " "; // Supondo que Pokémon tenha um método getName()
  }
  cout << endl;
}
