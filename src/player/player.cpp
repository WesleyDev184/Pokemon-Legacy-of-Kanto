#include "Player.h"
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

vector<Pokemon> Player::getPokemons() const
{
  return this->pokemons;
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

void Player::setPokemons(const vector<Pokemon> &pokemons)
{
  this->pokemons = pokemons;
}
