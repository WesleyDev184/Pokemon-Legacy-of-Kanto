#include "type.h"
#include <iostream>

// Construtor com alocação dinâmica
Type::Type(const string &typeName)
{
  name = new string(typeName);             // Aloca dinamicamente o nome
  multipliers = new map<string, double>(); // Aloca dinamicamente o mapa de multiplicadores
}

// Destrutor para liberar memória
Type::~Type()
{
  delete name;        // Libera a memória do nome
  delete multipliers; // Libera a memória do mapa de multiplicadores
}

// Getter para o nome do tipo
string Type::getName() const
{
  return *name; // Retorna o valor apontado por `name`
}

// Método para definir o multiplicador para um tipo defensor
void Type::setMultiplier(const string &defType, double multiplier)
{
  if (multiplier != 1)
  {
    (*multipliers)[defType] = multiplier; // Adiciona ou modifica o valor no mapa
  }
}

// Getter para o mapa de multiplicadores
map<string, double> Type::getMultipliers() const
{
  return *multipliers; // Retorna o mapa de multiplicadores
}

// Método para buscar um multiplicador específico
double Type::searchMultiplier(const string &defType) const
{
  auto it = multipliers->find(defType); // Busca no mapa
  if (it != multipliers->end())
  {
    return it->second; // Retorna o multiplicador se encontrado
  }
  return 1.0; // Retorna 1.0 caso o tipo não esteja presente
}

// Método para exibir os multiplicadores
void Type::showMultipliers() const
{
  cout << "Type: " << *name << endl; // Exibe o nome do tipo
  for (const auto &pair : *multipliers)
  {
    cout << "Multiplier: " << pair.second << "x - Defending type: " << pair.first << endl;
  }
}
