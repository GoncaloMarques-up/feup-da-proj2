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
    Graph graph = static_cast<Graph>(0);

public:

    /**
    * starts the menu
    */
    void run();

    /**
     * draws the main menu
     */
    static void drawMainMenu();

    /**
    * the computation for the main menu
    */
    void mainMenu();

    /**
    * draws the cenarios
    */
    static void drawCenarios();

    /**
     * the computation for cenarios
     */
    void cenarios();

    /**
    * draws the cenarios 1
    */
    static void drawCenarios1();

    /**
     * the computation for cenarios 1
     */
    void cenarios1();

    /**
    * draws the cenarios 2
    */
    static void drawCenarios2();

    /**
     * the computation for cenarios 2
     */
    void cenarios2();

    /**
    * draws the dev team
    */
    static void drawDevTeam();

    /**
     * the computation for the dev team
     */
    static void devTeam();

    /**
    * draws file options
    */
    static void drawFileChooser();
    /**
     * the computation for the file chooser
     */
    void chooseFile();


    /**
    * draws the exit
    */
    static void drawExit();

    /**
     * the computation for the exit
     */
    static int exit();

};


#endif //FEUP_DAL_PROJ2_MENU_H