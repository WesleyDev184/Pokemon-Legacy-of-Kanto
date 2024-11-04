#include "move.h"
#include <iostream>
#include <iomanip>

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
  cout << "==============================" << endl;
  cout << "Move: " << this->name << endl;
  cout << "==============================" << endl;
  cout << left << setw(20) << "Category: " << this->category << endl;
  cout << left << setw(20) << "Power: " << this->power << endl;
  cout << left << setw(20) << "Accuracy: " << this->accuracy << endl;
  cout << left << setw(20) << "Type: " << this->type << endl;
  cout << "==============================" << endl
       << endl;
}
