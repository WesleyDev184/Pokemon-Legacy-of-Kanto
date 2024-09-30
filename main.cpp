#include "main.h"

using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(0))); // Inicializa a semente

    Game game;

    // Carregando dados do jogo
    game.loadPlayersFromFile(PLAYERS_PATH);
    game.loadMovesFromFile(MOVES_PATH);
    game.loadEffectivenessFromFile(TYPE_EFFECTIVENESS_PATH);
    game.loadPokemonFromFile(POKEMONS_PATH);

    // Obtendo jogadores
    auto players = game.getPlayers();
    if (players.size() < 2)
    {
        cerr << "Erro: Não há jogadores suficientes." << endl;
        return 1; // Retorna um código de erro
    }

    Player &humanPlayer = *players.at(1);
    Player &CPUPlayer = *players.at(0);

    // Desenhando Pokémon para os jogadores
    game.drawPokemons(&humanPlayer, &CPUPlayer);

    // Imprimindo Pokémon do jogador humano
    cout << endl
         << "Jogador: " << humanPlayer.getName() << endl;
    for (const auto &pokemon : humanPlayer.getPokemons())
    {
        pokemon->print();
    }

    // Imprimindo Pokémon do jogador CPU
    cout << endl
         << "Jogador: " << CPUPlayer.getName() << endl;
    for (const auto &pokemon : CPUPlayer.getPokemons())
    {
        pokemon->print();
    }

    return 0;
}
