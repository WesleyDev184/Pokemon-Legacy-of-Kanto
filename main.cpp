#include "main.h"

using namespace std;

void printLine(char ch, int length)
{
    for (int i = 0; i < length; ++i)
    {
        cout << ch;
    }
    cout << endl;
}

void mainMenu()
{
    cout << endl;
    printLine('=', 30);
    cout << "Menu:" << endl;
    printLine('-', 30);
    cout << "1 - Iniciar Batalha" << endl;
    cout << "2 - Alterar dificuldade" << endl;
    cout << "3 - Exibir Rancking" << endl;
    cout << "4 - Sair" << endl;
    printLine('=', 30);
}

void playerChoiceMenu()
{
    cout << endl;
    printLine('=', 30);
    cout << "Escolha de jogador:" << endl;
    printLine('-', 30);
    cout << "1 - Escolher jogador existente" << endl;
    cout << "2 - Cadastrar novo jogador" << endl;
    printLine('=', 30);
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
            playerChoiceMenu();
            cin >> option;
            cin.ignore();

            if (option == 1)
            {
                cout << endl;
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
            }
            else
            {
                cout << "\nDigite o nome do jogador: ";
                getline(cin, newPlayerName);

                newPlayer = make_shared<Player>(newPlayerName, 0, 0, 0);
                game.setNewPlayers(newPlayer);
                player = newPlayer;

                game.drawPokemons(player);
                game.drawMoves(player);
                game.battle(player, CPU);
                game.savePlayersToFile(PLAYERS_PATH);
                break;
            }

        case 2:
            cout << endl;
            printLine('=', 30);
            cout << "Digite a dificuldade (1 - fácil, 2 - médio, 3 - difícil): \n";
            printLine('=', 30);
            cin >> difficulty;
            game.setDifficulty(difficulty);
            break;

        case 3:
            game.printRanking();
            break;

        case 4:
            game.savePlayersToFile(PLAYERS_PATH);
            return 0;

        default:
            cout << "Opção inválida!" << endl;
            return 1;
        }
    }

    return 0;
}