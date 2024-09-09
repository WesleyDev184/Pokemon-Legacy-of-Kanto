#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream arquivo("mapa.txt"); // Substitua "nome_do_arquivo.txt" pelo nome do seu arquivo
    if (!arquivo.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return 1;
    }

    std::string linha;
    while (std::getline(arquivo, linha))
    {
        std::cout << linha << std::endl;
    }

    arquivo.close();
    return 0;
}
