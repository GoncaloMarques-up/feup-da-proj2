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
                //cenarios();
                break;
            case 2:
                devTeam();
                break;
            case 3:
                //chooseFile();
                break;
            case 0:
                input = exit();
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