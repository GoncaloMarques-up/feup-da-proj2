//
// Created by ASUS on 22/05/2022.
//

#ifndef FEUP_DAL_PROJ2_MENU_H
#define FEUP_DAL_PROJ2_MENU_H

#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Menu {

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
    * draws the dev team
    */
    static void drawDevTeam();

    /**
     * the computation for the dev team
     */
    static void devTeam();

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