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

void loadMovesFromFile(const string &filePath, vector<Move> *moves)
{
  ifstream file(filePath);

  if (!file.is_open())
  {
    cerr << "Error: Could not open file " << filePath << endl;
    return;
  }

  string line;
  // Ignorar a primeira linha (cabeçalho)
  getline(file, line);

  while (getline(file, line))
  {
    stringstream ss(line);
    string name, category, type;
    int power;
    float accuracy;

    // Dividir a linha pelos campos, assumindo que eles são separados por vírgulas
    getline(ss, name, ',');
    getline(ss, category, ',');
    ss >> power;
    ss.ignore(); // Ignorar a vírgula após o número
    ss >> accuracy;
    ss.ignore(); // Ignorar a vírgula após o número
    getline(ss, type, ',');

    // Criar o objeto Move e adicionar ao vetor
    moves->emplace_back(name, category, power, accuracy, type);
  }

  file.close();
}