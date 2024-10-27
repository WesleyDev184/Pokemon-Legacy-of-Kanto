#include "game.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

// game logic
void Game::battle(shared_ptr<Player> &player1, shared_ptr<Player> &player2)
{
  auto player1Pokemons = player1->getPokemons();
  auto player2Pokemons = player2->getPokemons();

  Pokemon &pokemon1 = player1Pokemons[0];
  Pokemon &pokemon2 = player2Pokemons[0];

  // Sorteio de pokemons para batalha player 2
  int indexPokemonsPlayer2 = 0;
  pokemon2 = player2Pokemons[indexPokemonsPlayer2];

  // Abre a lista para o jogador escolher o pokemon
  cout << "===============================\n";
  cout << "     Escolha o seu Pokémon     \n";
  cout << "===============================\n";
  for (size_t i = 0; i < player1Pokemons.size(); ++i)
  {
    cout << i + 1 << ". ";
    player1Pokemons[i].print();
  }

  int chosenPokemon;
  cin >> chosenPokemon;
  cin.ignore();

  pokemon1 = player1Pokemons[chosenPokemon - 1];

  // Batalha
  int turn = 1;

  while (pokemon1.getHp() > 0 && pokemon2.getHp() > 0)
  {
    cout << "\n===============================\n";
    cout << "            Turno " << turn << "\n";
    cout << "===============================\n";
    cout << "Player 1: " << player1->getName() << "\n";
    cout << "    Pokémon: " << pokemon1.getName() << " | HP: " << pokemon1.getHp() << "\n";
    cout << "Player 2: " << player2->getName() << "\n";
    cout << "    Pokémon: " << pokemon2.getName() << " | HP: " << pokemon2.getHp() << "\n";
    cout << "-------------------------------\n";

    // Player 1 ataca
    cout << "Player 1, escolha o ataque:\n";
    for (size_t i = 0; i < pokemon1.getMoves().size(); ++i)
    {
      cout << i + 1 << ". " << pokemon1.getMoves()[i].getName() << "\n";
    }

    int chosenMove;
    cin >> chosenMove;
    cin.ignore();

    double damage = calculateDamage(pokemon1, pokemon2, pokemon1.getMoves()[chosenMove - 1]);
    cout << "\n>> Dano causado por " << pokemon1.getName() << ": " << damage << "!\n";
    pokemon2.setHp(pokemon2.getHp() - damage);
    turn++;

    if (pokemon2.getHp() <= 0)
    {
      cout << "\n>> " << pokemon2.getName() << " foi derrotado!\n";

      if (indexPokemonsPlayer2 < player2Pokemons.size() - 1)
      {
        indexPokemonsPlayer2++;
        pokemon2 = player2Pokemons[indexPokemonsPlayer2];
        cout << ">> Player 2 escolheu " << pokemon2.getName() << "!\n";
        continue;
      }
      else
      {
        cout << "\n*** Player 1 venceu a batalha! ***\n";
        player1->setVictories(player1->getVictories() + 1);
        player2->setDefeats(player2->getDefeats() + 1);
        adjustScore(player1);
        break;
      }
    }

    // Player 2 ataca
    cout << "\n"
         << pokemon2.getName() << " ataca!\n";
    int randomMove = rand() % pokemon2.getMoves().size();
    damage = calculateDamage(pokemon2, pokemon1, pokemon2.getMoves()[randomMove]);
    cout << "\n>> Dano causado por " << pokemon2.getName() << ": " << damage << "!\n";
    pokemon1.setHp(pokemon1.getHp() - damage);

    if (pokemon1.getHp() <= 0)
    {
      cout << "\n>> " << pokemon1.getName() << " foi derrotado!\n";

      int livingPokemons = 0;
      cout << endl;
      for (size_t i = 0; i < player1Pokemons.size(); ++i)
      {
        if (player1Pokemons[i].getHp() > 0)
        {
          livingPokemons++;
          cout << i + 1 << ". ";
          player1Pokemons[i].print();
        }
      }

      if (livingPokemons == 0)
      {
        cout << "\n*** Player 2 venceu a batalha! ***\n";
        player2->setVictories(player2->getVictories() + 1);
        player1->setDefeats(player1->getDefeats() + 1);
        adjustScore(player2);
        break;
      }
      else
      {
        cout << "\nEscolha o seu próximo Pokémon:\n";
        cin >> chosenPokemon;
        cin.ignore();

        pokemon1 = player1Pokemons[chosenPokemon - 1];
      }
    }
  }
}

void Game::adjustScore(shared_ptr<Player> &player)
{
  if (this->difficulty == 1)
  {
    player->setScore(player->getScore() + 10);
  }
  else if (this->difficulty == 2)
  {
    player->setScore(player->getScore() + 20);
  }
  else
  {
    player->setScore(player->getScore() + 30);
  }
}

string normalize(const string &str)
{
  string result;
  transform(str.begin(), str.end(), back_inserter(result), ::tolower);
  result.erase(remove(result.begin(), result.end(), ' '), result.end());
  return result;
}

pair<vector<Move *>, vector<Move *>> filterMovesByType(const Pokemon &pokemon, const vector<shared_ptr<Move>> &moves)
{
  vector<Move *> validTypeMoves;
  vector<Move *> normalMoves;

  for (auto &move : moves)
  {
    bool isValidForType = false;
    string moveType = normalize(move->getType());

    for (const auto &type : pokemon.getTypes())
    {
      string pokemonType = normalize(type.getName());

      if (pokemonType == moveType)
      {
        isValidForType = true;
        break;
      }
    }

    if (isValidForType)
    {
      validTypeMoves.push_back(move.get());
    }
    else if (moveType == "normal")
    {
      normalMoves.push_back(move.get());
    }
    else
    {
      cout << "Invalid move for type!" << endl;
    }
  }

  return {validTypeMoves, normalMoves};
}

void Game::drawMoves(shared_ptr<Player> &player) const
{

  auto moves = this->getMoves();
  auto &playerPokemons = player->getPokemons();

  // Sorteio de 4 movimentos para cada Pokémon do player
  for (auto &pokemon : playerPokemons)
  {
    vector<Move> pokemonMoves;

    auto movePairs = filterMovesByType(pokemon, moves);
    vector<Move *> validTypeMoves = movePairs.first;
    vector<Move *> normalMoves = movePairs.second;

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

    // Atribuir movimentos ao Pokémon
    pokemon.setMoves(pokemonMoves);
  }

  // Buscar o player CPU na lista
  shared_ptr<Player> CPU = nullptr;
  for (const auto &p : this->players)
  {
    if (p->getName() == "CPU")
    {
      CPU = p;
      break;
    }
  }

  // Sorteio de 4 movimentos para cada Pokémon do player CPU
  auto &CPUPlayerPokemons = CPU->getPokemons();
  for (auto &pokemon : CPUPlayerPokemons)
  {
    vector<Move> pokemonMoves;

    auto movePairs = filterMovesByType(pokemon, moves);
    vector<Move *> validTypeMoves = movePairs.first;
    vector<Move *> normalMoves = movePairs.second;

    // Escolha dos movimentos de acordo com a dificuldade
    if (this->getDifficulty() == 1)
    {
      // Escolher sempre o ataque com menor dano
      sort(validTypeMoves.begin(), validTypeMoves.end(), [](Move *a, Move *b)
           { return a->getPower() < b->getPower(); });
    }
    else if (this->getDifficulty() == 3)
    {
      // Escolher sempre o ataque com maior dano
      sort(validTypeMoves.begin(), validTypeMoves.end(), [](Move *a, Move *b)
           { return a->getPower() > b->getPower(); });
    }

    // Sorteia até 4 moves para o Pokémon
    for (int i = 0; i < 4; i++)
    {
      if (!validTypeMoves.empty())
      {
        int index = (this->getDifficulty() == 2) ? rand() % validTypeMoves.size() : 0; // Aleatório no Médio, primeiro no Fácil e Difícil
        pokemonMoves.push_back(*validTypeMoves[index]);
        validTypeMoves.erase(validTypeMoves.begin() + index);
      }
      else if (!normalMoves.empty())
      {
        int index = (this->getDifficulty() == 2) ? rand() % normalMoves.size() : 0; // Aleatório no Médio, primeiro no Fácil e Difícil
        pokemonMoves.push_back(*normalMoves[index]);
        normalMoves.erase(normalMoves.begin() + index);
      }
    }

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

double Game::calculateDamage(const Pokemon &attacker, const Pokemon &defender, const Move &move) const
{
  double damage = 0;
  double level = attacker.getLevel();
  double power = move.getPower();
  double attack = attacker.getAttack();
  double SpecialAttack = attacker.getSpecialAttack();
  double defense = defender.getDefense();
  double SpecialDefense = defender.getSpecialDefense();
  double critical = rand() % 16;
  double STAB = 1;
  double random = (217 + rand() % (255 - 217 + 1)) / 255.0;
  double accuracy = static_cast<double>(rand()) / RAND_MAX;

  // valida se o ataque faz parte do moveset do pokemon
  bool validMove = false;
  for (const auto &pokemonMove : attacker.getMoves())
  {
    if (pokemonMove.getName() == move.getName())
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
  if (move.getCategory() == "Fisico")
  {
    damage = (((2 * level * power) * (attack / defense)) / 50) + 2;
  }
  else if (move.getCategory() == "Especial")
  {
    damage = ((2 * level * power * (SpecialAttack / SpecialDefense)) / 50) + 2;
  }

  // Critical hit
  if (critical == 0)
  {
    damage *= 2;
    cout << endl
         << ">> Critical hit!" << endl;
  }

  // Same type attack bonus
  auto type1 = attacker.getTypes()[0];
  if (type1.getName() == move.getType())
  {
    STAB = 1.5;
  }

  damage *= STAB;

  // Type effectiveness
  double effectiveness = 1;
  for (const auto &type : defender.getTypes())
  {
    effectiveness *= type.searchMultiplier(move.getType());
  }

  if (effectiveness > 1)
  {
    cout << endl
         << ">> O ataque foi super efetivo!" << endl;
  }
  else if (effectiveness < 1)
  {
    cout << endl
         << ">> O ataque não foi muito efetivo!" << endl;
  }
  else if (effectiveness == 0)
  {
    cout << endl
         << ">> O ataque não é efetivo!" << endl;
  }

  damage *= effectiveness;

  // Random factor
  damage *= random;

  // accuracy
  cout << endl
       << ">> Accuracy: " << accuracy << endl;
  if (accuracy > move.getAccuracy())
  {
    cout << endl
         << ">> O ataque errou!" << endl;
    return 0;
  }

  return damage;
}

void Game::printRanking() const
{
  vector<shared_ptr<Player>> players = this->getPlayers();

  // Ordena os jogadores pelo score de forma decrescente
  sort(players.begin(), players.end(),
       [](const shared_ptr<Player> &p1, const shared_ptr<Player> &p2)
       {
         return p1->getScore() > p2->getScore(); // Maior score primeiro
       });

  cout << endl
       << "===========================\n";
  cout << "           Ranking         \n";
  cout << "===========================\n";
  for (size_t i = 0; i < players.size(); ++i)
  {
    cout << "Top " << i + 1 << ": " << endl;
    cout << '\t';
    players[i]->print();
  }
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
  // valida se o player já existe
  for (const auto &p : this->players)
  {
    if (p->getName() == player->getName())
    {
      cout << "Player já existe!" << endl;
      return;
    }
  }

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
