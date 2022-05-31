//
// Created by ASUS on 22/05/2022.
//

#ifndef FEUP_DAL_PROJ2_MENU_H
#define FEUP_DAL_PROJ2_MENU_H

#include <iostream>
#include <string>
#include <utility>

#include "FileReader.h"

class Menu {
    Graph graph = FileReader::readFile("ts01_b.txt");;
    int s, t;
public:

    /**
    * starts the menu
    */
    void run();

    /**
     * draws the main menu
     */
    void drawMainMenu();

    /**
    * the computation for the main menu
    */
    void mainMenu();

    /**
    * draws the cenarios
    */
    void drawCenarios();

    /**
     * the computation for cenarios
     */
    void cenarios();

    /**
    * draws the cenarios 1
    */
    void drawCenarios1();

    /**
     * the computation for cenarios 1
     */
    void cenarios1();

    /**
    * draws the cenarios 2
    */
    void drawCenarios2();

    /**
     * the computation for cenarios 2
     */
    void cenarios2();

    /**
    * draws the dev team
    */
    void drawDevTeam();

    /**
     * the computation for the dev team
     */
    void devTeam();

    /**
    * draws file options
    */
    void drawFileChooser();
    /**
     * the computation for the file chooser
     */
    void chooseFile();


    /**
    * draws the exit
    */
    void drawExit();

    /**
     * the computation for the exit
     */
    int exit();

    void readInputNodes(int &s, int &t);
};


#endif //FEUP_DAL_PROJ2_MENU_H