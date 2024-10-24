#include "main.h"

using namespace std;

void mainMenu()
{
    cout << endl;
    cout << "Menu:" << endl;
    cout << "1 - Selecionar jogador" << endl;
    cout << "2 - Criar jogador" << endl;
    cout << "3 - Alterar dificuldade" << endl;
    cout << "4 - Exibir Rancking" << endl;
    cout << "5 - Sair" << endl;
}

int main()
{
    srand(static_cast<unsigned int>(time(0))); // Inicializa a semente aleatória

    while (true)
    {
        Game game;

        game.loadPlayersFromFile(PLAYERS_PATH);
        game.loadMovesFromFile(MOVES_PATH);
        game.loadEffectivenessFromFile(TYPE_EFFECTIVENESS_PATH);
        game.loadPokemonFromFile(POKEMONS_PATH);

        auto CPU = game.getPlayers().at(0);
        auto player = game.getPlayers().at(1);

        int option;
        mainMenu();

        cin >> option;
        cin.ignore();

        string playerName;
        string newPlayerName;
        shared_ptr<Player> newPlayer;
        int difficulty;

        switch (option)
        {
        case 1:
            cout << "Jogadores disponíveis:" << endl;
            for (size_t i = 1; i < game.getPlayers().size(); ++i)
            {
                game.getPlayers().at(i)->print();
            }

            cout << "Digite o nome do jogador: ";
            getline(cin, playerName);

            for (size_t i = 1; i < game.getPlayers().size(); ++i)
            {
                if (game.getPlayers().at(i)->getName() == playerName)
                {
                    player = game.getPlayers().at(i);
                    break;
                }
            }

            game.drawPokemons(player);
            game.drawMoves(player);
            game.battle(player, CPU);
            game.savePlayersToFile(PLAYERS_PATH);
            break;

        case 2:
            cout << "Digite o nome do jogador: ";
            getline(cin, newPlayerName);

            newPlayer = make_shared<Player>(newPlayerName, 0, 0, 0);
            game.setNewPlayers(newPlayer);
            player = newPlayer;

            game.drawPokemons(player);
            game.drawMoves(player);
            game.battle(player, CPU);
            game.savePlayersToFile(PLAYERS_PATH);
            break;

        case 3:
            cout << "Digite a dificuldade (1 - fácil, 2 - médio, 3 - difícil): ";
            cin >> difficulty;
            game.setDifficulty(difficulty);
            break;

        case 4:
            game.printRanking();
            break;

        case 5:
            game.savePlayersToFile(PLAYERS_PATH);
            return 0;

        default:
            cout << "Opção inválida!" << endl;
            break;
        }
    }

    return 0;
}
