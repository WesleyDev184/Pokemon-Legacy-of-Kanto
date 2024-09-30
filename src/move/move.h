#ifndef MOVE_H
#define MOVE_H

#include <string>

using namespace std;

class Move
{
private:
  string *name;
  string *category;
  int power;
  float accuracy;
  string *type;

public:
  // Construtor
  Move(const string &name, const string &category, int power, float accuracy, const string &type);

  // Destrutor
  ~Move();

  // Getters
  string getName() const;
  string getCategory() const;
  int getPower() const;
  float getAccuracy() const;
  string getType() const;

  // Setters (opcional, caso queira modificar depois)
  void setName(const string &name);
  void setCategory(const string &category);
  void setType(const string &type);

  void print() const;
};

#endif
