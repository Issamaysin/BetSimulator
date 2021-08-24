/* ********************************************************************** */
/* File name:        menu.cpp                                             */
/* File description: File where the methods of the game menu are defined  */
/*                    -menu let's user select and enter a game.           */
/* Author name:      Renato Pepe       				                      */
/* Creation date:    16/08/2021                                           */
/* Revision date:    24/08/2021                                           */
/* ************************************************************************/

/*
    Includes
*/
#include <iostream>
#include <conio.h>
#include <list>
#include <string>
#include "curses.h"
#include "gameRun.h"
#include "menu.h"

/*
    Frequently used namespaces.
*/
using std::cout;
using std::list;
using std::string;


/*
Method name:    screen_Menu
Description:    Display the Menu where user can select the game they'll be playing, and run the selected game.
Outputs:        n/a
Inputs:         float playerWallet: Player's current cash
                float chipValue: Current chip value
                gameState state: Current game state, so menu can change it to a game according to user input
                WINDOW gameWindow: Curses window where simulator happens
Author:         Renato Pepe
Creation date:  16/08/2021
Last modified:  24/08/2021
*/
void screen_Menu(float& playerWallet, float& chipValue, gameState& state, WINDOW *&gameWindow) {
    //Clear what was previously printed on the screen and box the screen
    wclear(gameWindow);
    wrefresh(gameWindow);
    box(gameWindow, 0, 0);

    //Print title at the top of the screen
    wattron(gameWindow, A_BOLD | A_REVERSE);
    mvwprintw(gameWindow, 2, (screen_Width/2) - 10, "Bet Simulator");
    wattroff(gameWindow, A_BOLD | A_REVERSE);

    mvwprintw(gameWindow, 4, 4, "Wallet: $");
    wprintw(gameWindow, (std::to_string((int)playerWallet)).c_str());
    mvwprintw(gameWindow, 6, 4, "Games:");

    //Makes a list of the games (the names are hardcoded here since it's the only time they are needed)
    string menuText[numberOfGames] = { "-Dice", "-Loot box"};

    /*
        Menu variables
    */
    //Highligh keeps track of what option is being selected
    int highlight = 0;
    //Key stores user input
    int key;
    while (1) {
        //Print options and highlights selected option
        for (int i = 0; i < numberOfGames; i++) {
            if (i == highlight) {
                wattron(gameWindow, A_REVERSE);
            }
            mvwprintw(gameWindow, 7 + i, 6, menuText[i].c_str());
            if (i == highlight) {
                wattroff(gameWindow, A_REVERSE);
            }
        }

        //Get user input
        key = wgetch(gameWindow);

        //Changes option being highlighted, enter game, or end program according to user input
        if (key == KEY_DOWN || key == 's' || key == 'S') {
            highlight++;
            if (highlight > (numberOfGames - 1)) {
                highlight = 0;
            }
        }
        else if (key == KEY_UP || key == 'w' || key == 'W') {
            highlight--;
            if (highlight < 0) {
                highlight = (numberOfGames - 1);
            }
        }
        else if (key == 'x' || key == 'X') {
            state = gameState::EXIT;
            return;
            break;
        }
        else if (key == 'e' || key == 'E') {
            break;
        }
        else {
            //Other keys do nothing
        }
    }
    
    //Changes game state according to selected option.
    switch (highlight) {
    case 0:
        state = gameState::GAME1;
        break;
    case 1:
        state = gameState::GAME2;
        break;
    case 2:
        //for future games
        break;
    default:
        //Should never enter here
        state = gameState::MENU;
        break;
    }
    wrefresh(gameWindow);
}