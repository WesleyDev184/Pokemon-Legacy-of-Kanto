#include "game.h"
#include <fstream>
#include <sstream>
#include <iostream>

// game logic
void Game::drawMoves(shared_ptr<Player> &player) const
{
  auto moves = this->getMoves();
  auto playerPokemons = player->getPokemons();

  for (auto &pokemon : playerPokemons)
  {
    vector<Move> pokemonMoves;
    vector<Move *> validTypeMoves;
    vector<Move *> normalMoves;

    // Separar movimentos válidos por tipo e movimentos "Normal"
    for (auto &move : moves)
    {
      bool isValidForType = false;
      for (const auto &type : pokemon.getTypes())
      {
        if (type.getName() == move->getType())
        {
          isValidForType = true;
          break;
        }
      }

      if (isValidForType)
      {
        validTypeMoves.push_back(move.get());
      }
      else if (move->getType() == "Normal")
      {
        normalMoves.push_back(move.get());
      }
    }

    // Sorteia até 4 moves para o Pokémon
    for (int i = 0; i < 4; i++)
    {
      if (!validTypeMoves.empty())
      {
        int randomIndex = rand() % validTypeMoves.size();
        pokemonMoves.push_back(*validTypeMoves[randomIndex]);
        validTypeMoves.erase(validTypeMoves.begin() + randomIndex);
      }
      else if (!normalMoves.empty())
      {
        int randomIndex = rand() % normalMoves.size();
        pokemonMoves.push_back(*normalMoves[randomIndex]);
        normalMoves.erase(normalMoves.begin() + randomIndex);
      }
    }

    // Exibir os movimentos do Pokémon
    for (auto &move : pokemonMoves)
    {
      cout << "Pokemon: " << pokemon.getName() << " - Move: " << move.getName() << " - Type: " << move.getType() << endl;
    }
    cout << endl;

    // Atribuir movimentos ao Pokémon
    pokemon.setMoves(pokemonMoves);
  }
}

void Game::drawPokemons(shared_ptr<Player> &player) const
{
  vector<shared_ptr<Pokemon>> pokemons = this->getPokemons();
  vector<Pokemon> playerPokemons;

  // adiciona 3 pokemons aleatorios ao player
  for (int i = 0; i < 3; i++)
  {
    int randomIndex = rand() % pokemons.size();
    playerPokemons.push_back(*pokemons[randomIndex]);
  }

  player->setPokemons(playerPokemons);

  // adiciona 3 pokemons ao player CPU com base na dificuldade
  // Na dificuldade Facil, os nıveis dos Pokemons da CPU sao sempre menores ou iguais ao
  // seu Pokemon mais fraco. Na dificuldade M´edia, os n´ıveis dos Pok´emons da CPU s˜ao sempre menores ou iguais ao
  // seu Pok´emon mais forte.No modo Dif´ıcil, os n´ıveis dos Pok´emons da CPU s˜ao sempre maiores ou iguais ao seu
  // Pok´emon mais forte
  Pokemon weakestPokemon = player->getPokemons()[0];
  Pokemon strongestPokemon = player->getPokemons()[0];

  for (const auto &pokemon : player->getPokemons())
  {
    if (weakestPokemon.getLevel() == 0 || pokemon.getLevel() < weakestPokemon.getLevel())
    {
      weakestPokemon = pokemon;
    }
    if (strongestPokemon.getLevel() == 0 || pokemon.getLevel() > strongestPokemon.getLevel())
    {
      strongestPokemon = pokemon;
    }
  }

  vector<Pokemon> adversaryPokemons;
  if (this->getDifficulty() == 1)
  {
    // busca aleatoriamente pokemon para o player CPU com nivel menor ou igual ao mais fraco do player
    for (int i = 0; i < 3; i++)
    {
      int randomIndex = rand() % pokemons.size();
      Pokemon pokemon = *pokemons[randomIndex];
      if (pokemon.getLevel() <= weakestPokemon.getLevel())
      {
        adversaryPokemons.push_back(pokemon);
      }
      else
      {
        i--;
      }
    }
  }
  else if (this->getDifficulty() == 2)
  {
    // busca aleatoriamente pokemon para o player CPU com nivel menor ou igual ao mais forte do player
    for (int i = 0; i < 3; i++)
    {
      int randomIndex = rand() % pokemons.size();
      Pokemon pokemon = *pokemons[randomIndex];
      if (pokemon.getLevel() <= strongestPokemon.getLevel())
      {
        adversaryPokemons.push_back(pokemon);
      }
      else
      {
        i--;
      }
    }
  }
  else if (this->getDifficulty() == 3)
  {
    // busca aleatoriamente pokemon para o player CPU com nivel maior ou igual ao mais forte do player
    for (int i = 0; i < 3; i++)
    {
      int randomIndex = rand() % pokemons.size();
      Pokemon pokemon = *pokemons[randomIndex];
      if (pokemon.getLevel() >= strongestPokemon.getLevel())
      {
        adversaryPokemons.push_back(pokemon);
      }
      else
      {
        i--;
      }
    }
  }

  // busca o player CPU na lista
  shared_ptr<Player> CPU = nullptr;
  for (const auto &player : this->players)
  {
    if (player->getName() == "CPU")
    {
      CPU = player;
      break;
    }
  }

  CPU->setPokemons(adversaryPokemons);
}

double Game::calculateDamage(const shared_ptr<Pokemon> &attacker, const shared_ptr<Pokemon> &defender, const shared_ptr<Move> &move) const
{
  double damage = 0;
  double level = attacker->getLevel();
  double power = move->getPower();
  double attack = attacker->getAttack();
  double SpecialAttack = attacker->getSpecialAttack();
  double defense = defender->getDefense();
  double SpecialDefense = defender->getSpecialDefense();
  double critical = rand() % 16;
  double STAB = 1;
  double random = (217 + rand() % (255 - 217 + 1)) / 255.0;
  double accuracy = static_cast<double>(rand()) / RAND_MAX;

  // valida se o ataque faz parte do moveset do pokemon
  bool validMove = false;
  for (const auto &pokemonMove : attacker->getMoves())
  {
    if (pokemonMove.getName() == move->getName())
    {
      validMove = true;
      break;
    }
  }

  if (!validMove)
  {
    cout << "O ataque não faz parte do moveset do pokemon!" << endl;
    return 0;
  }

  // calcula o dano
  if (move->getCategory() == "Fisico")
  {
    damage = (((2 * level * power) * (attack / defense)) / 50) + 2;
  }
  else if (move->getCategory() == "Especial")
  {
    damage = ((2 * level * power * (SpecialAttack / SpecialDefense)) / 50) + 2;
  }

  // Critical hit
  if (critical == 0)
  {
    damage *= 2;
    cout << "Critical hit!" << endl;
  }

  // Same type attack bonus
  auto type1 = attacker->getTypes()[0];
  if (type1.getName() == move->getType())
  {
    STAB = 1.5;
  }

  damage *= STAB;

  // Type effectiveness
  double effectiveness = 1;
  for (const auto &type : defender->getTypes())
  {
    effectiveness *= type.searchMultiplier(move->getType());
  }

  if (effectiveness > 1)
  {
    cout << "O ataque foi super efetivo!" << endl;
  }
  else if (effectiveness < 1)
  {
    cout << "O ataque não foi muito efetivo!" << endl;
  }
  else if (effectiveness == 0)
  {
    cout << "O ataque não é efetivo!" << endl;
  }

  damage *= effectiveness;

  // Random factor
  damage *= random;

  // accuracy
  cout << "Accuracy: " << accuracy << endl;
  if (accuracy > move->getAccuracy())
  {
    cout << "O ataque errou!" << endl;
    return 0;
  }

  return damage;
}

// Getters
vector<shared_ptr<Player>> Game::getPlayers() const
{
  return this->players;
}

vector<shared_ptr<Type>> Game::getTypes() const
{
  return this->types;
}

vector<shared_ptr<Pokemon>> Game::getPokemons() const
{
  return this->pokemons;
}

vector<shared_ptr<Pokemon>> Game::getPokemonsByType(const string &type) const
{
  vector<shared_ptr<Pokemon>> pokemonsByType;
  for (const auto &pokemon : this->pokemons)
  {
    for (const auto &pokemonType : pokemon->getTypes())
    {
      if (pokemonType.getName() == type)
      {
        pokemonsByType.push_back(pokemon);
        break;
      }
    }
  }
  return pokemonsByType;
}

vector<shared_ptr<Move>> Game::getMoves() const
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

void Game::setNewPlayers(const shared_ptr<Player> player)
{
  this->players.push_back(player);
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

  for (const auto &player : this->players)
  {
    file << player->getName() << ","
         << player->getScore() << ","
         << player->getVictories() << ","
         << player->getDefeats() << endl;
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

void Game::loadPlayersFromFile(const string &filePath)
{
  ifstream file(filePath);
  if (!file.is_open())
  {
    cerr << "Error: Could not open file " << filePath << endl;
    return;
  }

  string line;
  getline(file, line); // Ignorar cabeçalho

  while (getline(file, line))
  {
    stringstream ss(line);
    string name;
    int score, victories, defeats;

    getline(ss, name, ',');
    ss >> score;
    ss.ignore();
    ss >> victories;
    ss.ignore();
    ss >> defeats;

    // Criar o objeto Player usando shared_ptr e adicionar ao vetor
    shared_ptr<Player> newPlayer = make_shared<Player>(name, score, victories, defeats);
    this->players.push_back(newPlayer);
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
  getline(file, line); // Ignorar cabeçalho

  while (getline(file, line))
  {
    stringstream ss(line);
    string name, category, type;
    int power;
    float accuracy;

    getline(ss, name, ',');
    getline(ss, category, ',');
    ss >> power;
    ss.ignore();
    ss >> accuracy;
    ss.ignore();
    getline(ss, type, ',');

    // Criar o objeto Move usando shared_ptr e adicionar ao vetor
    shared_ptr<Move> newMove = make_shared<Move>(name, category, power, accuracy, type);
    this->moves.push_back(newMove);
  }

  file.close();
}

void Game::loadEffectivenessFromFile(const string &filePath)
{
  ifstream file(filePath);
  string line;

  // Lendo o cabeçalho
  getline(file, line);
  vector<string> typeNames = split(line, ',');

  // Lendo cada linha (cada tipo de Pokémon)
  while (getline(file, line))
  {
    vector<string> multipliers = split(line, ',');
    Type newType(multipliers[0]);
    for (size_t i = 1; i < multipliers.size(); i++)
    {
      newType.setMultiplier(typeNames[i], stod(multipliers[i]));
    }
    this->types.push_back(make_shared<Type>(newType)); // Adiciona como shared_ptr
  }
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
  getline(file, line); // Ignorar cabeçalho

  while (getline(file, line))
  {
    stringstream ss(line);
    string name, type1, type2;
    int hp, level, attack, defense, speed, specialAttack, specialDefense;

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

    // Criar o objeto Pokemon usando shared_ptr e adicionar ao vetor
    shared_ptr<Pokemon> newPokemon = make_shared<Pokemon>(name, type1, type2, hp, level, attack, defense, speed, specialAttack, specialDefense);
    this->pokemons.push_back(newPokemon);
  }

  file.close();

  // Associar tipos com Pokémon
  for (auto &pokemon : this->pokemons)
  {
    vector<Type> typeObjects;
    for (const auto &typePtr : this->types)
    {
      typeObjects.push_back(*typePtr);
    }
    pokemon->setTypes(typeObjects);
  }
}
