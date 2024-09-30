#include "type.h"
#include <iostream>

Type::Type(const string &typeName) : name(typeName) {}

string Type::getName() const
{
  return this->name;
}

void Type::setMultiplier(const string &defType, double multiplier)
{
  if (multiplier != 1)
  {
    this->multipliers[defType] = multiplier;
  }
}

map<string, double> Type::getMultipliers() const
{
  return this->multipliers;
}

double Type::searchMultiplier(const string &defType) const
{
  if (this->multipliers.find(defType) != this->multipliers.end())
  {
    return this->multipliers.at(defType);
  }
  else
  {
    return 1;
  }
}

void Type::showMultipliers() const
{
  cout << "Type: " << this->name << endl;
  for (const auto &multiplier : this->multipliers)
  {
    cout << "Multiplier: ";
    cout << multiplier.second;
    cout << "x - Defending type: ";
    cout << multiplier.first;
    cout << endl;
  }
}
