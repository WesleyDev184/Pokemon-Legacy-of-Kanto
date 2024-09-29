#include "main.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

class PokemonTypeChart
{
private:
    std::vector<std::vector<double>> typeChart;
    std::unordered_map<std::string, int> typeIndex;

    void loadTypes(const std::vector<std::string> &types)
    {
        for (int i = 0; i < types.size(); ++i)
        {
            typeIndex[types[i]] = i;
        }
    }

public:
    void loadFromCSV(const std::string &filename)
    {
        std::ifstream file(filename);
        std::string line, cell;
        bool headerProcessed = false;

        if (!file.is_open())
        {
            std::cerr << "Erro ao abrir o arquivo " << filename << std::endl;
            return;
        }

        while (std::getline(file, line))
        {
            std::stringstream lineStream(line);
            std::vector<double> row;

            if (!headerProcessed)
            {
                // Process header
                std::vector<std::string> headers;
                std::getline(lineStream, cell, ','); // Skip "attack" header
                while (std::getline(lineStream, cell, ','))
                {
                    headers.push_back(cell);
                }
                loadTypes(headers);
                headerProcessed = true;
            }
            else
            {
                // Process data rows
                std::getline(lineStream, cell, ','); // Skip row type (e.g., Normal, Fogo)
                while (std::getline(lineStream, cell, ','))
                {
                    row.push_back(std::stod(cell));
                }
                typeChart.push_back(row);
            }
        }
    }

    double getDamageMultiplier(const std::string &attackType, const std::string &defenseType) const
    {
        if (typeIndex.find(attackType) != typeIndex.end() && typeIndex.find(defenseType) != typeIndex.end())
        {
            int attackIdx = typeIndex.at(attackType);
            int defenseIdx = typeIndex.at(defenseType);
            return typeChart[attackIdx][defenseIdx];
        }
        cout << "Tipo de ataque ou defesa não encontrado" << endl;
        return 1.0; // Default to neutral damage if type not found
    }
};

int main()
{
    PokemonTypeChart typeChart;
    typeChart.loadFromCSV(TYPE_EFFECTIVENESS_PATH);

    std::string attackType = "Gelo";
    std::string defenseType = "Dragao";
    double multiplier = typeChart.getDamageMultiplier(attackType, defenseType);

    std::cout << "Um ataque de tipo " << attackType << " causa " << multiplier << "x de dano em um Pokémon de tipo " << defenseType << ".\n";

    // Outros exemplos de consulta
    std::cout << "Um ataque de tipo Fogo causa " << typeChart.getDamageMultiplier("Fogo", "Grama") << "x de dano em um Pokémon de tipo Grama.\n";
    std::cout << "Um ataque de tipo Agua causa " << typeChart.getDamageMultiplier("Agua", "Fogo") << "x de dano em um Pokémon de tipo Fogo.\n";

    return 0;
}

// using namespace std;

// int main()
// {
//     shared_ptr<vector<Move>> moves(new vector<Move>());
//     shared_ptr<vector<Pokemon>> pokemons(new vector<Pokemon>());
//     shared_ptr<vector<Player>> players(new vector<Player>());

//     loadPlayersFromFile(PLAYERS_PATH, players.get());

//     players->at(0).setScore(2000);

//     for (const auto &player : *players)
//     {
//         player.print();
//     }

//     savePlayersToFile(PLAYERS_PATH, *players);

//     // loadMovesFromFile(MOVES_PATH, moves.get());

//     // for (const auto &move : *moves)
//     // {
//     //     move.print();
//     // }

//     // loadPokemonFromFile(POKEMONS_PATH, pokemons.get());

//     // for (const auto &pokemon : *pokemons)
//     // {
//     //     pokemon.print();
//     // }

//     return 0;
// }