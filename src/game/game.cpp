#include "game.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>

// game logic
void Game::drawPokemons(Player *player, Player *CPU) const
{
  vector<Pokemon *> pokemons = this->getPokemons();
  vector<Pokemon *> playerPokemons;

  // Adiciona 3 Pokémon aleatórios ao jogador
  for (int i = 0; i < 3; i++)
  {
    int randomIndex = rand() % pokemons.size();
    playerPokemons.push_back(pokemons[randomIndex]);
  }

  player->setPokemons(playerPokemons);

  // Adiciona 3 Pokémon ao CPU com base na dificuldade
  if (player->getPokemons().empty())
  {
    cerr << "Erro: O jogador não tem Pokémon." << endl;
    return; // Ou você pode decidir como lidar com essa situação
  }

  Pokemon *weakestPokemon = player->getPokemons()[0];
  Pokemon *strongestPokemon = player->getPokemons()[0];

  for (const auto &pokemon : player->getPokemons())
  {
    if (pokemon->getLevel() < weakestPokemon->getLevel())
    {
      weakestPokemon = pokemon;
    }
    if (pokemon->getLevel() > strongestPokemon->getLevel())
    {
      strongestPokemon = pokemon;
    }
  }

  vector<Pokemon *> adversaryPokemons;

  for (int i = 0; i < 3;)
  {
    int randomIndex = rand() % pokemons.size();
    Pokemon *pokemon = pokemons[randomIndex];

    // Lógica de dificuldade
    if ((this->getDifficulty() == 1 && pokemon->getLevel() <= weakestPokemon->getLevel()) ||
        (this->getDifficulty() == 2 && pokemon->getLevel() <= strongestPokemon->getLevel()) ||
        (this->getDifficulty() == 3 && pokemon->getLevel() >= strongestPokemon->getLevel()))
    {
      adversaryPokemons.push_back(pokemon);
      i++; // Incrementa apenas quando um Pokémon válido é adicionado
    }
  }

  CPU->setPokemons(adversaryPokemons);
}

double Game::calculateDamage(const Pokemon *attacker, const Pokemon *defender, const Move *move) const
{
  double damage = 0;
  double level = attacker->getLevel();
  double power = move->getPower();
  double attack = attacker->getAttack();
  double specialAttack = attacker->getSpecialAttack();
  double defense = defender->getDefense();
  double specialDefense = defender->getSpecialDefense();
  double critical = rand() % 16; // Crítico se for 0
  double STAB = 1;
  double random = (217 + rand() % (255 - 217 + 1)) / 255.0;
  double accuracy = static_cast<double>(rand()) / RAND_MAX;

  // Valida se o ataque faz parte do moveset do Pokémon
  bool validMove = false;
  for (const auto &pokemonMove : attacker->getMoves())
  {
    if (pokemonMove->getName() == move->getName())
    {
      validMove = true;
      break;
    }
  }

  if (!validMove)
  {
    cout << "O ataque não faz parte do moveset do Pokémon!" << endl;
    return 0;
  }

  // Calcula o dano
  if (move->getCategory() == "Fisico")
  {
    damage = (((2 * level * power * (attack / defense)) / 50) + 2);
  }
  else if (move->getCategory() == "Especial")
  {
    damage = ((2 * level * power * (specialAttack / specialDefense)) / 50) + 2;
  }

  // Crítico
  if (critical == 0)
  {
    damage *= 2;
    cout << "Critical hit!" << endl;
  }

  // Same Type Attack Bonus (STAB)
  if (attacker->getTypes()[0]->getName() == move->getType())
  {
    STAB = 1.5;
  }

  damage *= STAB;

  // Efetividade do tipo
  double effectiveness = 1;
  for (const auto &type : defender->getTypes())
  {
    effectiveness *= type->searchMultiplier(move->getType());
  }

  // Mensagens de efetividade
  if (effectiveness > 1)
  {
    cout << "O ataque foi super efetivo!" << endl;
  }
  else if (effectiveness < 1 && effectiveness > 0)
  {
    cout << "O ataque não foi muito efetivo!" << endl;
  }
  else if (effectiveness == 0)
  {
    cout << "O ataque não é efetivo!" << endl;
  }

  damage *= effectiveness;
  damage *= random;

  // Verificação de precisão
  if (accuracy > move->getAccuracy())
  {
    cout << "O ataque errou!" << endl;
    return 0;
  }

  // Verifica se o dano é negativo
  return damage < 0 ? 0 : damage;
}

// Getters
vector<Player *> Game::getPlayers() const
{
  return this->players;
}

vector<Type *> Game::getTypes() const
{
  return this->types;
}

vector<Pokemon *> Game::getPokemons() const
{
  return this->pokemons;
}

vector<Pokemon *> Game::getPokemonsByType(const string &type) const
{
  vector<Pokemon *> pokemonsByType;
  for (const auto &pokemon : this->pokemons)
  {
    for (const auto &pokemonType : pokemon->getTypes())
    {
      if (pokemonType->getName() == type)
      {
        pokemonsByType.push_back(pokemon); // Adiciona o ponteiro ao vetor
        break;                             // Saia do loop após encontrar o tipo
      }
    }
  }
  return pokemonsByType;
}

vector<Move *> Game::getMoves() const
{
  return this->moves;
}

int Game::getDifficulty() const
{
  return this->difficulty;
}

// Setters
void Game::setDifficulty(const int difficulty)
{
  this->difficulty = difficulty;
}

void Game::setNewPlayer(Player *player)
{
  this->players.push_back(player);
}

void Game::loadPlayersFromFile(const string &filePath)
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
    string name;
    int score, victories, defeats;

    // Dividir a linha pelos campos, assumindo que eles são separados por vírgulas
    getline(ss, name, ',');
    ss >> score;
    ss.ignore();
    ss >> victories;
    ss.ignore();
    ss >> defeats;

    // Criar um novo objeto Player e adicionar ao vetor como ponteiro
    Player *newPlayer = new Player(name, score, victories, defeats);
    this->players.push_back(newPlayer); // Agora players é um vetor de ponteiros
  }

  file.close();
}

void Game::savePlayersToFile(const string &filePath)
{
  ofstream file(filePath);

  if (!file.is_open())
  {
    cerr << "Error: Could not open file " << filePath << endl;
    return;
  }

  file << "Name,Score,Victories,Defeats" << endl;

  for (const auto &playerPtr : this->players) // Note que agora deve ser um ponteiro
  {
    file << playerPtr->getName() << "," // Usando o operador '->' para acessar membros do ponteiro
         << playerPtr->getScore() << ","
         << playerPtr->getVictories() << ","
         << playerPtr->getDefeats() << endl;
  }

  file.close();
}

void Game::loadMovesFromFile(const string &filePath)
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

    // Criar o objeto Move usando ponteiro e adicionar ao vetor
    Move *newMove = new Move(name, category, power, accuracy, type); // Usando ponteiro
    this->moves.push_back(newMove);                                  // Adicionando ponteiro ao vetor
  }

  file.close();
}

vector<string> split(const string &linha, char delimitador)
{
  vector<string> tokens;
  string token;
  istringstream tokenStream(linha);
  while (getline(tokenStream, token, delimitador))
  {
    tokens.push_back(token);
  }
  return tokens;
}

void Game::loadEffectivenessFromFile(const string &filePath)
{
  ifstream file(filePath);
  string line;

  // Reading the first line (header)
  getline(file, line);
  vector<string> typeNames = split(line, ',');

  // Reading each line (each Pokémon type)
  while (getline(file, line))
  {
    vector<string> multipliers = split(line, ',');
    Type *newType = new Type(multipliers[0]); // Usando ponteiro

    for (size_t i = 1; i < multipliers.size(); i++)
    {
      newType->setMultiplier(typeNames[i], stod(multipliers[i])); // Usando operador ->
    }

    this->types.push_back(newType); // Adicionando ponteiro ao vetor
  }

  file.close();
}

void Game::loadPokemonFromFile(const string &filePath)
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
    string name, type1, type2;
    int hp, level, attack, defense, speed, specialAttack, specialDefense;

    // Dividir a linha pelos campos, assumindo que eles são separados por vírgulas
    getline(ss, name, ',');
    getline(ss, type1, ',');
    getline(ss, type2, ',');
    ss >> hp;
    ss.ignore();
    ss >> level;
    ss.ignore();
    ss >> attack;
    ss.ignore();
    ss >> defense;
    ss.ignore();
    ss >> speed;
    ss.ignore();
    ss >> specialAttack;
    ss.ignore();
    ss >> specialDefense;

    // Criar o objeto Pokemon e adicionar ao vetor de ponteiros
    Pokemon *pokemon = new Pokemon(name, type1, type2, hp, level, attack, defense, speed, specialAttack, specialDefense);
    this->pokemons.push_back(pokemon);
  }

  file.close();

  // Definir os tipos para cada Pokémon
  for (auto &pokemon : this->pokemons)
  {
    vector<Type *> typesForPokemon; // Vetor para armazenar os ponteiros dos tipos

    // Adiciona tipo1
    for (Type *type : this->types)
    {
      if (type->getName() == pokemon->getTypes()[0]->getName())
      {
        typesForPokemon.push_back(type);
        break;
      }
    }

    // Adiciona tipo2 se existir
    if (!pokemon->getTypes()[1]->getName().empty())
    {
      for (Type *type : this->types)
      {
        if (type->getName() == pokemon->getTypes()[1]->getName())
        {
          typesForPokemon.push_back(type);
          break;
        }
      }
    }

    pokemon->setTypes(typesForPokemon);
  }
}

Game::~Game()
{
  for (Player *player : players)
  {
    delete player;
  }
  for (Type *type : types)
  {
    delete type;
  }
  for (Pokemon *pokemon : pokemons)
  {
    delete pokemon;
  }
  for (Move *move : moves)
  {
    delete move;
  }
}