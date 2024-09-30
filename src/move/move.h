#ifndef MOVE_H
#define MOVE_H

#include <string>
#include <vector>

using namespace std;

class Move
{
private:
  string name;
  string category;
  int power;
  float accuracy;
  string type;

public:
  // Construtor
  Move(const string &name, const string &category, int power, float accuracy, const string &type);

  // Getters
  string getName() const;
  string getCategory() const;
  int getPower() const;
  float getAccuracy() const;
  string getType() const;

  void print() const;
};

#endif
