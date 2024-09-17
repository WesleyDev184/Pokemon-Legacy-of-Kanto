#include <iostream>
#include <memory>
#include "src/move/move.h"
#include "src/pokemon/pokemon.h"
#include "src/player/player.h"

using namespace std;

int main()
{
    shared_ptr<vector<Move>> moves(new vector<Move>());
    shared_ptr<vector<Pokemon>> pokemons(new vector<Pokemon>());
    shared_ptr<vector<Player>> players(new vector<Player>());

    // string filePath = "data/player.txt";

    // loadPlayersFromFile(filePath, players.get());

    // for (const auto &player : *players)
    // {
    //     player.print();
    // }

    string filePath = "data/moves.txt";

    loadMovesFromFile(filePath, moves.get());

    for (const auto &move : *moves)
    {
        move.print();
    }

    // string filePath = "data/pokemons.txt";

    // loadPokemonFromFile(filePath, pokemons.get());

    // for (const auto &pokemon : *pokemons)
    // {
    //     pokemon.print();
    // }

    return 0;
}