//
// Created by ASUS on 22/05/2022.
//

#include "../includes/Menu.h"


void Menu::run() {
    mainMenu();
}

void Menu::drawMainMenu() {
    std::cout << "-------------- Design de Algoritmos - 2021/22 --------------" << '\n';
    std::cout << "1 - Cenarios" << '\n';
    std::cout << "2 - DevTeam" << '\n';
    std::cout << "3 - Escolha de ficheiros" << '\n';
    std::cout << "0 - Sair" << "\n\n";
}

void Menu::mainMenu() {
    int input;
    do{
        drawMainMenu();
        std::cin >> input;
        switch (input) {
            case 1:
                cenarios();
                break;
            case 2:
                devTeam();
                break;
            case 3:
                chooseFile();
                break;
            case 0:
                input = exit();
                break;
        }
    } while (input);
}


void Menu::drawCenarios() {
    std::cout << "----------------- Escolha de Cenarios -----------------\n";
    std::cout << "1 - Cenario 1 - Grupos que nao se separam\n";
    std::cout << "2 - Cenario 2 - Grupos que podem separar-se\n";
    std::cout << "0 - Sair\n\n";
}

void Menu::cenarios() {
    int input;
    do{
        drawCenarios();
        std::cin >> input;
        switch (input) {
            case 1:
                cenarios1();
                break;
            case 2:
                cenarios2();
                break;
        }
    } while (input);
}

void Menu::drawCenarios1() {
    std::cout << "----------------- Escolha de Cenarios 1 ----------------\n";
    std::cout << "1 - 1.1 - Maximizar a Dimensao do Grupo e Indicar um Qualquer Encaminhamento\n";
    std::cout << "2 - 1.2 - Maximizar a Dimensao do Grupo e Minimizar o Numero de Transbordos\n";
    std::cout << "0 - Sair\n\n";
}

void Menu::cenarios1() {
    int input;
    do{
        drawCenarios1();
        std::cin >> input;
        switch (input) {
            case 1:
                readInputNodes();
                graph.maxCapacityPath(src, sink);
                graph.cenario1_1Output(src, sink);
                break;
            case 2:
                readInputNodes();
                graph.maxCapacityAndShortestPath(src, sink);
                break;
        }
    } while (input);
}

void Menu::drawCenarios2() {
    std::cout << "----------------- Escolha de Cenarios 2 ----------------\n";
    std::cout << "1 - 2.1 - Determinar um Encaminhamento para um Grupo, com Dimensao Fixa\n";
    std::cout << "2 - 2.2 - Determinar um Encaminhamento para um Grupo, com Dimensao Flutuante\n";
    std::cout << "3 - 2.3 - Determinar a Dimensao Maxima do Grupo e um Encaminhamento\n";
    std::cout << "4 - 2.4 - Determinar Quando e que o Grupo se Reuniria Novamente no Destino, no Minimo.\n";
    std::cout << "5 - 2.5 - Indicar o Tempo Maximo de Espera e os Locais em que Haveria Elementos que Esperam Esse Tempo\n";
    std::cout << "0 - Sair\n\n";
}

void Menu::cenarios2() {
    int input;
    do{
        drawCenarios2();
        std::cin >> input;
        switch (input) {

            case 1:
                readInputNodes();
                graph.cenario21(src, sink);
                break;
            case 2:
                graph.cenario22();
                break;
            case 3:
                readInputNodes();
                graph.cenario23(src, sink);
                break;
            case 4:
                graph.cenario24();
                break;
            case 5:
                graph.cenario25();
                break;
        }
    } while (input);
}

void Menu::drawDevTeam() {
    std::cout << "----------------- DevTeam -----------------" << '\n';
    std::cout << "201905574 - David Marques" << '\n';
    std::cout << "202006874 - Goncalo Marques" << '\n';
    std::cout << "202103631 - Rui Soares" << '\n' << '\n';
    std::cout << "Selecione Qualquer Input para Voltar ao Menu Principal" << "\n\n";
}

void Menu::devTeam() {
    drawDevTeam();
    std::string input;
    std::cin >> input;
}

void Menu::drawFileChooser() {
    std::cout << "----------------- Escolha de Ficheiros -----------------\n";
    std::cout << "1 - Dataset de Teste (mais pequeno)\n";
    std::cout << "2 - Dataset Principal (maior)\n";
    std::cout << "0 - Sair\n\n";
}

void Menu::chooseFile() {
    int input;
    std::string pre, file;
    drawFileChooser();
    std::cin >> input;
    std::cout << "Escolha o Numero do Ficheiro ";
    switch (input) {
        case 1:
            pre="ts";
            std::cout << "[1-3]\n";
            break;
        case 2:
            pre="in";
            std::cout << "[1-10]\n";
            break;
    }
    std::cin >> input;
    if(input<10)
        file = pre + "0" + std::to_string(input) + "_b.txt";
    else
        file = pre + std::to_string(input) + "_b.txt";

    graph = FileReader::readFile(file);
}


void Menu::drawExit() {
    std::cout << "Pretende Mesmo Sair?" << '\n';
    std::cout << "1 - Sim" << '\n';
    std::cout << "0 - Nao" << '\n';
}


int Menu::exit() {
    drawExit();
    int input;
    std::cin >> input;
    return !input;
}

void Menu::readInputNodes() {
    do{
        std::cout << "Introduza a Paragem Inicial e a Final [1-" << graph.getN() << "]\n";
        std::cin >> src;
        std::cin >> sink;
    }while(src<=0 or src>graph.getN() or sink<=0 or sink>graph.getN());
}
