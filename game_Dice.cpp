/* ***********************************************************************/
/* File name:        game_Dice.cpp                                       */
/* File description: Cpp file where dice game methods are defined        */
/* Author name:      Renato Pepe       				                     */
/* Creation date:    20/08/2021                                          */
/* Revision date:    22/08/2021                                          */
/* ***********************************************************************/


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
#include "game_Dice.h"

/*
    Frequently used namespaces.
*/
using std::cout;
using std::list;
using std::string;

/*
    Dice game functions
*/

/*
Method name:    diceGameCommandsScreen
Description:    Prints the game instructions on the screen and wait for user confirmation
Outputs:        n/a
Inputs:         n/a
Author:         Renato Pepe
Creation date:  20/08/2021
Last modified:  21/08/2021
*/
void diceGameCommandsScreen(WINDOW*& gameWindow) {
    //Clear what was previously printed on the screen and box the screen
    wclear(gameWindow);
    wrefresh(gameWindow);
    box(gameWindow, 0, 0);

    int line = 1;
    //Prints game instructions
    mvwprintw(gameWindow, line++ , 1, " Simple dice game:");
    line++;
    mvwprintw(gameWindow, line++, 1, "-Choose a number between 1 and 6");
    mvwprintw(gameWindow, line++, 1, "and/or High/Low to place a bet.");
    line++;
    mvwprintw(gameWindow, line++, 1, "-Numbers have a 1/6 chance and will give 6x rewards, while");
    mvwprintw(gameWindow, line++, 1, "High/Low has 1/2 chance and will give 2X rewards.");
    line++;
    mvwprintw(gameWindow, line++, 1, "-Controls:");
    line++;
    mvwprintw(gameWindow, line++, 1, "1/2/3/4/5/6 => choose a number");
    mvwprintw(gameWindow, line++, 1, "H/L         => choose a High/Low");
    mvwprintw(gameWindow, line++, 1, "0           => reset bet");
    mvwprintw(gameWindow, line++, 1, "up/down     => increase/decrease bet");
    mvwprintw(gameWindow, line++, 1, "left/right  => increase/decrease chip");
    mvwprintw(gameWindow, line++, 1, "E           => bet!");
    mvwprintw(gameWindow, line++, 1, "Q           => go back to menu");
    wrefresh(gameWindow);

    //Wait for user to press any key before continuing to the game
    _getch();
}

/*
Method name:    diceGameRun
Description:    Main dice game method, initialize game parameters and start the game loop (where the other methods will be called)
Outputs:        n/a
Inputs:         n/a
Author:         Renato Pepe
Creation date:  20/08/2021
Last modified:  22/08/2021
*/
void diceGameRun(float& playerWallet, float& chipValue, WINDOW*& gameWindow) {
    //Print commands screen before starting the actual game
    diceGameCommandsScreen(gameWindow);
    
    /*
        Dice game variables
    */
    //Die data
    int dieNumber = rand()%6 + 1;
    //User data
    int playerBetNumber = 0;
    //Obs: H/L => 0 = none, 1 = High, 2 = Low.
    int playerBetHL = 0;
    float betValue = 100.0f;
    float thisRoundProfit = 0.0f;

    //Main game loop
    while (1) {

        //print stuff
        printDiceGameScreen(playerWallet, chipValue, betValue, playerBetNumber, dieNumber, playerBetHL, thisRoundProfit, gameWindow);
        
        //get key
        _getch();
        break;
        //do something according to key

    }

}

/*
Method name:    printDiceGameScreen
Description:    Prints dice game data on the screen.
Outputs:        n/a
Inputs:         n/a
Author:         Renato Pepe
Creation date:  20/08/2021
Last modified:  22/08/2021
*/
void printDiceGameScreen(float playerWallet, float chipValue, float betValue, int playerBetNumber, int dieNumber, int playerBetHL, float thisRoundProfit, WINDOW *& gameWindow) {
    //Clear what was previously printed on the screen and box the screen
    wclear(gameWindow);
    wrefresh(gameWindow);
    box(gameWindow, 0, 0);
    
    int line = 5;
    
    //Print wallet info
    mvwprintw(gameWindow, line++, 2, "Wallet:   $");
    wprintw(gameWindow, (std::to_string((int)playerWallet)).c_str());
    
    //Print chip info
    mvwprintw(gameWindow, line++, 2, "Chip:     $");
    wprintw(gameWindow, (std::to_string((int)chipValue)).c_str());

    //Print bet value info
    mvwprintw(gameWindow, line++, 2, "Bet:      $");
    wprintw(gameWindow, (std::to_string((int)betValue).c_str()));

    //Print number and H/L info
    line++;
    mvwprintw(gameWindow, line++, 2, "Number:   ");
    if (0 != playerBetNumber) {
        wprintw(gameWindow, (std::to_string(playerBetNumber)).c_str());
    }
    else {
        wprintw(gameWindow, "N/A");
    }
    mvwprintw(gameWindow, line++, 2, "High/Low: ");
    if (0 == playerBetHL) {
        wprintw(gameWindow, "N/A");
    }
    else if (1 == playerBetHL) {
        wprintw(gameWindow, "High");
    }
    else {
        wprintw(gameWindow, "Low");
    }

    //Draw die
    line = 5;
    int drawDieXPosition = screen_Width - 25;

    wattron(gameWindow, A_ALTCHARSET);
    mvwaddch(gameWindow, line++, drawDieXPosition, 108);
    waddch(gameWindow, 113);
    waddch(gameWindow, 113);
    waddch(gameWindow, 113);
    waddch(gameWindow, 113);
    waddch(gameWindow, 113);
    waddch(gameWindow, 107);
    wattroff(gameWindow, A_ALTCHARSET);

    switch (dieNumber) {
    case 1:

        mvwprintw(gameWindow, line++, drawDieXPosition, "|     |");
        mvwprintw(gameWindow, line++, drawDieXPosition, "|  *  |");
        mvwprintw(gameWindow, line++, drawDieXPosition, "|     |");
        break;
    case 2:
        mvwprintw(gameWindow, line++, drawDieXPosition, "|*    |");
        mvwprintw(gameWindow, line++, drawDieXPosition, "|     |");
        mvwprintw(gameWindow, line++, drawDieXPosition, "|    *|");
        break;
    case 3:
        mvwprintw(gameWindow, line++, drawDieXPosition, "|*    |");
        mvwprintw(gameWindow, line++, drawDieXPosition, "|  *  |");
        mvwprintw(gameWindow, line++, drawDieXPosition, "|    *|");
        break;
    case 4:
        mvwprintw(gameWindow, line++, drawDieXPosition, "|*   *|");
        mvwprintw(gameWindow, line++, drawDieXPosition, "|     |");
        mvwprintw(gameWindow, line++, drawDieXPosition, "|*   *|");
        break;
    case 5:
        mvwprintw(gameWindow, line++, drawDieXPosition, "|*   *|");
        mvwprintw(gameWindow, line++, drawDieXPosition, "|  *  |");
        mvwprintw(gameWindow, line++, drawDieXPosition, "|*   *|");
        break;
    case 6:
        mvwprintw(gameWindow, line++, drawDieXPosition, "|* * *|");
        mvwprintw(gameWindow, line++, drawDieXPosition, "|     |");
        mvwprintw(gameWindow, line++, drawDieXPosition, "|* * *|");
        break;
    default:
        //Should never enter here
        mvwprintw(gameWindow, line++, drawDieXPosition, "|XXXXX|");
        mvwprintw(gameWindow, line++, drawDieXPosition, "|XXXXX|");
        mvwprintw(gameWindow, line++, drawDieXPosition, "|XXXXX|");
        break;
    }

    wattron(gameWindow, A_ALTCHARSET);
    mvwaddch(gameWindow, line - 3, drawDieXPosition, 120);
    mvwaddch(gameWindow, line - 2, drawDieXPosition, 120);
    mvwaddch(gameWindow, line - 1, drawDieXPosition, 120);
    mvwaddch(gameWindow, line - 3, drawDieXPosition + 6, 120);
    mvwaddch(gameWindow, line - 2, drawDieXPosition + 6, 120);
    mvwaddch(gameWindow, line - 1, drawDieXPosition + 6, 120);

    mvwaddch(gameWindow, line++, drawDieXPosition, 109);
    waddch(gameWindow, 113);
    waddch(gameWindow, 113);
    waddch(gameWindow, 113);
    waddch(gameWindow, 113);
    waddch(gameWindow, 113);
    waddch(gameWindow, 106);
    wattroff(gameWindow, A_ALTCHARSET);

    //Draw profit here
    line++;
    mvwprintw(gameWindow, line++, drawDieXPosition - 6, "Round profit: $ ");
    if (0 <= thisRoundProfit) {
        wattron(gameWindow, COLOR_PAIR(CP_GREEN));
        waddch(gameWindow, '+');
        wprintw(gameWindow, (std::to_string((int)thisRoundProfit)).c_str());
        wattroff(gameWindow, COLOR_PAIR(CP_GREEN));
    }
    else {
        wattron(gameWindow, COLOR_PAIR(CP_RED));
        wprintw(gameWindow, (std::to_string((int)thisRoundProfit)).c_str());
        wattroff(gameWindow, COLOR_PAIR(CP_RED));
    }

    wrefresh(gameWindow);
}