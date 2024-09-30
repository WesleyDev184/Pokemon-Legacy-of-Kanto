#ifndef TYPE_H
#define TYPE_H

#include <string>
#include <map>

using namespace std;

class Type
{
private:
  string name;
  map<string, double> multipliers;

public:
  Type(const string &typeName);

  string getName() const;

  void setMultiplier(const string &defType, double multiplier);

  map<string, double> getMultipliers() const;

  double searchMultiplier(const string &defType) const;
  void showMultipliers() const;
};

#endif // TYPE_H