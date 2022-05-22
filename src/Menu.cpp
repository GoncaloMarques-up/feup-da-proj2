//
// Created by ASUS on 22/05/2022.
//

#include "../includes/Menu.h"


void Menu::run() {
    mainMenu();
}

void Menu::drawMainMenu() {
    cout << "-------------- Design de Algoritmos - 2021/22 --------------" << endl;
    cout << "1 - Cenarios" << endl;
    cout << "2 - DevTeam" << endl;
    cout << "3 - Escolha de ficheiros" << endl;
    cout << "0 - Sair" << endl << endl;
}

void Menu::mainMenu() {
    int input;
    do{
        drawMainMenu();
        cin >> input;
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
    cout << "----------------- DevTeam -----------------" << endl;
    cout << "201905574 - David Marques" << endl;
    cout << "202006874 - Goncalo Marques" << endl;
    cout << "202103631 - Rui Soares" << endl << endl;
    cout << "Selecione Qualquer Input para Voltar ao Menu Principal" << endl << endl;
}

void Menu::devTeam() {
    drawDevTeam();
    string input;
    cin >> input;
}

void Menu::drawExit() {
    cout << "Pretende Mesmo Sair?" << endl;
    cout << "1 - Sim" << endl;
    cout << "0 - Nao" << endl;
}


int Menu::exit() {
    drawExit();
    int input;
    cin >> input;
    return !input;
}