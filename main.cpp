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
    auto player = game.getPlayers().at(1);
    auto CPU = game.getPlayers().at(0);

    game.drawMoves(player);

    // Exibindo Pokémon do jogador
    cout << endl
         << "Jogador: " << player->getName() << endl;
    for (const auto &pokemon : game.getPlayers().at(1)->getPokemons())
    {
        pokemon.print();
        // Exibindo movimentos
        for (auto &move : pokemon.getMoves())
        {
            move.print();
        }

        cout << endl;
    }

    // Exibindo Pokémon da CPU
    cout << endl
         << "CPU: " << CPU->getName() << endl;
    for (const auto &pokemon : CPU->getPokemons())
    {
        pokemon.print();

        for (auto &move : pokemon.getMoves())
        {
            move.print();
        }

        cout << endl;
    }

    cout << endl;

    return 0;
}
