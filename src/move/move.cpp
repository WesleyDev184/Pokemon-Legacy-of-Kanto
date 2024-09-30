#include "Move.h"
#include <iostream>

// Construtor
Move::Move(const string &name, const string &category, int power, float accuracy, const string &type)
{
  this->name = new string(name);
  this->category = new string(category);
  this->power = power;
  this->accuracy = accuracy;
  this->type = new string(type);
}

// Destrutor
Move::~Move()
{
  delete name;
  delete category;
  delete type;
}

// Getters
string Move::getName() const
{
  return *name;
}

string Move::getCategory() const
{
  return *category;
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
  return *type;
}

// Setters (opcional, caso queira modificar depois)
void Move::setName(const string &name)
{
  delete this->name; // Libera a memória antiga
  this->name = new string(name);
}

void Move::setCategory(const string &category)
{
  delete this->category; // Libera a memória antiga
  this->category = new string(category);
}

void Move::setType(const string &type)
{
  delete this->type; // Libera a memória antiga
  this->type = new string(type);
}

// Método print
void Move::print() const
{
  cout << "Name: " << *name << ", "
       << "Category: " << *category << ", "
       << "Power: " << power << ", "
       << "Accuracy: " << accuracy << ", "
       << "Type: " << *type
       << endl;
}
