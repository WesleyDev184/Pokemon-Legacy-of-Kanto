#include "Move.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Construtor
Move::Move(const string &name, const string &category, int power, float accuracy, const string &type)
    : name(name), category(category), power(power), accuracy(accuracy), type(type) {}

// Getters
string Move::getName() const
{
  return this->name;
}

string Move::getCategory() const
{
  return this->category;
}

int Move::getPower() const
{
  return this->power;
}

float Move::getAccuracy() const
{
  return this->accuracy;
}

string Move::getType() const
{
  return this->type;
}

void Move::print() const
{
  cout << "Name: " << this->name << ", "
       << "Category: " << this->category << ", "
       << "Power: " << this->power << ", "
       << "Accuracy: " << this->accuracy << ", "
       << "Type: " << this->type
       << endl;
}
