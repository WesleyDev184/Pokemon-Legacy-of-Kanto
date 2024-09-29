#include "main.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

class PokemonTypeChart
{
private:
    vector<vector<double>> typeChart;
    unordered_map<string, int> typeIndex;

    void loadTypes(const vector<string> &types)
    {
        for (int i = 0; i < types.size(); ++i)
        {
            typeIndex[types[i]] = i;
        }
    }

public:
    void loadFromCSV(const string &filename)
    {
        ifstream file(filename);
        string line, cell;
        bool headerProcessed = false;

        if (!file.is_open())
        {
            cerr << "Erro ao abrir o arquivo " << filename << endl;
            return;
        }

        while (getline(file, line))
        {
            stringstream lineStream(line);
            vector<double> row;

            if (!headerProcessed)
            {
                // Process header
                vector<string> headers;
                getline(lineStream, cell, ','); // Skip "attack" header
                while (getline(lineStream, cell, ','))
                {
                    headers.push_back(cell);
                }
                loadTypes(headers);
                headerProcessed = true;
            }
            else
            {
                // Process data rows
                getline(lineStream, cell, ','); // Skip row type (e.g., Normal, Fogo)
                while (getline(lineStream, cell, ','))
                {
                    row.push_back(stod(cell));
                }
                typeChart.push_back(row);
            }
        }
    }

    double getDamageMultiplier(const string &attackType, const string &defenseType) const
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

    string attackType = "Gelo";
    string defenseType = "Dragao";
    double multiplier = typeChart.getDamageMultiplier(attackType, defenseType);

    cout << "Um ataque de tipo " << attackType << " causa " << multiplier << "x de dano em um Pokémon de tipo " << defenseType << ".\n";

    // Outros exemplos de consulta
    cout << "Um ataque de tipo Fogo causa " << typeChart.getDamageMultiplier("Fogo", "Grama") << "x de dano em um Pokémon de tipo Grama.\n";
    cout << "Um ataque de tipo Agua causa " << typeChart.getDamageMultiplier("Agua", "Fogo") << "x de dano em um Pokémon de tipo Fogo.\n";

    return 0;
}

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