#ifndef TYPE_H
#define TYPE_H

#include <string>
#include <map>

using namespace std;

class Type
{
private:
  string* name;                  // Ponteiro para o nome do tipo
  map<string, double>* multipliers;  // Ponteiro para o mapa de multiplicadores

public:
  // Construtor
  Type(const string &typeName);

  // Destrutor
  ~Type();

  // Getters
  string getName() const;

  // Setters
  void setMultiplier(const string &defType, double multiplier);

  map<string, double> getMultipliers() const;

  double searchMultiplier(const string &defType) const;
  void showMultipliers() const;
};

#endif // TYPE_H
