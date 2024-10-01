#include "main.h"

using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(0))); // Inicializa a semente aleatória

    Game game;

    game.loadPlayersFromFile(PLAYERS_PATH);
    game.loadMovesFromFile(MOVES_PATH);
    game.loadEffectivenessFromFile(TYPE_EFFECTIVENESS_PATH);
    game.loadPokemonFromFile(POKEMONS_PATH);

    // Selecionando jogadores
    auto players = game.getPlayers().at(1);
    auto CPU = game.getPlayers().at(0);

    game.drawMoves(players);

    // Exibindo Pokémon do jogador
    cout << endl
         << "Jogador: " << players->getName() << endl;
    for (const auto &pokemon : game.getPlayers().at(1)->getPokemons())
    {
        pokemon.print();
        cout << "Moves: ";
        for (const auto &move : pokemon.getMoves())
        {
            cout << move.getName() << " ";
        }
    }

    // Exibindo Pokémon da CPU
    cout << endl
         << "CPU: " << CPU->getName() << endl;
    for (const auto &pokemon : CPU->getPokemons())
    {
        pokemon.print();
    }

    cout << endl;

    return 0;
}
