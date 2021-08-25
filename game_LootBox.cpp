/* ***********************************************************************/
/* File name:        game_LootBox.cpp                                    */
/* File description: Cpp file where loot box game methods are defined    */
/* Author name:      Renato Pepe       				                     */
/* Creation date:    24/08/2021                                          */
/* Revision date:    24/08/2021                                          */
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
#include "game_LootBox.h"



/*
    Frequently used namespaces.
*/
using std::cout;
using std::list;
using std::string;

/*
    Loot box game functions
*/

/*
Method name:    lootBoxGameCommandsScreen
Description:    Prints the game instructions on the screen and wait for user confirmation
Outputs:        n/a
Inputs:         WINDOW gameWindow: curses screen where game happens
Author:         Renato Pepe
Creation date:  24/08/2021
Last modified:  24/08/2021
*/
void lootBoxGameCommandsScreen(WINDOW*& gameWindow) {
    //Clear what was previously printed on the screen and box the screen
    wclear(stdscr);
    wrefresh(stdscr);
    wclear(gameWindow);
    wrefresh(gameWindow);
    box(gameWindow, 0, 0);

    int line = 1;
    //Prints game instructions
    mvwprintw(gameWindow, line++, 1, " Loot box game, simulates a classic loot box:");
    line++;
    mvwprintw(gameWindow, line++, 1, "-Each prize has a different chance and proportional");
    mvwprintw(gameWindow, line++, 1, "rewards. On a bet each prize is drawn independently");
    mvwprintw(gameWindow, line++, 1, "and the total reward is the sum of all the prizes won.");
    line++;
    mvwprintw(gameWindow, line++, 1, "-Prize chances and rewards:");
    wattron(gameWindow, COLOR_PAIR(CP_ORANGE));
    mvwprintw(gameWindow, line++, 1, "Orange: 1/100 chance, 10x payout");
    wattroff(gameWindow, COLOR_PAIR(CP_ORANGE));
    wattron(gameWindow, COLOR_PAIR(CP_PURPLE));
    mvwprintw(gameWindow, line++, 1, "Purple: 1/20 chance,  4x payout");
    wattroff(gameWindow, COLOR_PAIR(CP_PURPLE));
    wattron(gameWindow, COLOR_PAIR(CP_BLUE));
    mvwprintw(gameWindow, line++, 1, "Blue:   1/4 chance,   1.4x payout");
    wattroff(gameWindow, COLOR_PAIR(CP_BLUE));
    wattron(gameWindow, COLOR_PAIR(CP_GREEN));
    mvwprintw(gameWindow, line++, 1, "Green:  1/2 chance,   0.7x payout");
    wattroff(gameWindow, COLOR_PAIR(CP_GREEN));
    line++;
    mvwprintw(gameWindow, line++, 1, "-Controls:");
    mvwprintw(gameWindow, line++, 1, "up/down     => increase/decrease bet");
    mvwprintw(gameWindow, line++, 1, "left/right  => increase/decrease chip");
    mvwprintw(gameWindow, line++, 1, "E           => bet!");
    mvwprintw(gameWindow, line++, 1, "Q           => go back to menu");
    wrefresh(gameWindow);

    //Wait for user to press any key before continuing to the game
    _getch();
}



/*
Method name:    lootBoxGameRun
Description:    Main loot box game method, initialize game parameters and start the game loop (where the other methods will be called)
Outputs:        n/a
Inputs:         float playerWallet: Player's current cash
                float chipValue: Current chip value
                WINDOW gameWindow: curses window where game happens
Author:         Renato Pepe
Creation date:  24/08/2021
Last modified:  25/08/2021
*/
void lootBoxGameRun(float& playerWallet, float& chipValue, WINDOW*& gameWindow) {
    //Print commands screen before starting the actual game
    lootBoxGameCommandsScreen(gameWindow);

    /*
         Loot box game variables
    */
    //Ammount of cash player is currently betting
    float betValue = 100.0f;
    //Profit of this round, separated by each prize (orange, purple, blue, green, total)
    float thisRoundProfit[5] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    //Variable that stores user input (initialized with a 'random' char that's different than 'q' so loop can start properly)
    int userInput = 'n';
    //Stores prize status, false = draw failed, true = draw sucessfull
    bool prizesStatus[4] = { false, false, false, false };
    //Main game loop
    while ('q' != userInput && 'Q' != userInput) {

        //BetValue can't be greater than playerWallet
        if (betValue > playerWallet) {
            betValue = playerWallet;
        }

        //Print data on screen
        printLootBoxGameScreen(prizesStatus, playerWallet, chipValue, betValue, thisRoundProfit, gameWindow);

        //If player reached $0 he 'lost' the game, break this loop and handle defeat on main game loop
        if (0 >= playerWallet) {
            _getch();
            break;
        }
        //If player reached $999.999 he 'won' the game, break this loop and handle victory on main game loop
        if (999999.0f <= playerWallet) {
            _getch();
            break;
        }

        //Get user input and respond accordingly
        userInput = wgetch(gameWindow);
        getAndHandleInputLootBoxGame(userInput, playerWallet, chipValue, betValue, prizesStatus, thisRoundProfit);
    }
}

/*
Method name:    printLootBoxGameScreen
Description:    Prints loot box game data on screen
Outputs:        n/a
Inputs:         bool prizeStatus[4]: status of each prize, if they were drawn or not
                float playerWallet: Player's current cash
                float chipValue: Current chip value
                float betValue: current bet value
                float thisRoundProfit[5]: round profit of each prize + total
                WINDOW gameWindow: curses window where game happens
Author:         Renato Pepe
Creation date:  24/08/2021
Last modified:  25/08/2021
*/
void printLootBoxGameScreen(bool prizesStatus[4], float playerWallet, float chipValue, float betValue, float thisRoundProfit[5], WINDOW*& gameWindow) {
    //Clear what was previously printed on the screen and box the screen
    wclear(stdscr);
    wrefresh(stdscr);
    wclear(gameWindow);
    wrefresh(gameWindow);
    box(gameWindow, 0, 0);

    //Line and column variables to make printing on the screen easier
    int line = 2;
    int column = 13;

    /*
        Print prizes
    */
    //Print prize boxes first, since they'll always be print, then fill boxes according to prizesStatus.
    //Prize boxes: first draw upper line, then middle columns, and bottom line.
    wattron(gameWindow, A_ALTCHARSET);
    for (int i = 0; i < 4; i++) {
        mvwaddch(gameWindow, line, column++, 108);
        mvwaddch(gameWindow, line, column++, 113);
        mvwaddch(gameWindow, line, column++, 113);
        mvwaddch(gameWindow, line, column++, 107);
        column += 5;
    }
    column = 13;
    line++;
    for (int i = 0; i < 4; i++) {
        mvwaddch(gameWindow, line, column++, 120);
        column += 2;
        mvwaddch(gameWindow, line, column++, 120);
        column += 5;
    }
    column = 13;
    line++;
    for (int i = 0; i < 4; i++) {
        mvwaddch(gameWindow, line, column++, 109);
        mvwaddch(gameWindow, line, column++, 113);
        mvwaddch(gameWindow, line, column++, 113);
        mvwaddch(gameWindow, line, column++, 106);
        column += 5;
    }
    wattroff(gameWindow, A_ALTCHARSET);
  
    //Fill prize boxes according to their status
    if (prizesStatus[0]) {
        line = 3;
        column = 14;
        mvwaddch(gameWindow, line, column++, ' ' | A_REVERSE | COLOR_PAIR(CP_ORANGE));
        mvwaddch(gameWindow, line, column++, ' ' | A_REVERSE | COLOR_PAIR(CP_ORANGE));
    }
    if (prizesStatus[1]) {
        line = 3;
        column = 23;
        mvwaddch(gameWindow, line, column++, ' ' | A_REVERSE | COLOR_PAIR(CP_PURPLE));
        mvwaddch(gameWindow, line, column++, ' ' | A_REVERSE | COLOR_PAIR(CP_PURPLE));
    }
    if (prizesStatus[2]) {
        line = 3;
        column = 32;
        mvwaddch(gameWindow, line, column++, ' ' | A_REVERSE | COLOR_PAIR(CP_BLUE));
        mvwaddch(gameWindow, line, column++, ' ' | A_REVERSE | COLOR_PAIR(CP_BLUE));
    }
    if (prizesStatus[3]) {
        line = 3;
        column = 41;
        mvwaddch(gameWindow, line, column++, ' ' | A_REVERSE | COLOR_PAIR(CP_GREEN));
        mvwaddch(gameWindow, line, column++, ' ' | A_REVERSE | COLOR_PAIR(CP_GREEN));
    }

    line = 9;
    //Print wallet info
    mvwprintw(gameWindow, line++, 2, "Wallet:   $");
    wprintw(gameWindow, (std::to_string((int)playerWallet)).c_str());

    //Print chip info
    mvwprintw(gameWindow, line++, 2, "Chip:     $");
    wprintw(gameWindow, (std::to_string((int)chipValue)).c_str());

    //Print bet value info
    mvwprintw(gameWindow, line++, 2, "Bet:      $");
    wprintw(gameWindow, (std::to_string((int)betValue).c_str()));

    //Print profits, each prize has a separate line and then a total profit on the last line.
    line = 9;
    column = 30;
    mvwprintw(gameWindow, line, column, "Profit:");
    column += 8;
    //Prize profits are colored for better UX
    wattron(gameWindow, COLOR_PAIR(CP_ORANGE));
    mvwaddch(gameWindow, line, column, '$');
    mvwprintw(gameWindow, line++, column+1, (std::to_string((int)thisRoundProfit[0])).c_str());
    wattroff(gameWindow, COLOR_PAIR(CP_ORANGE));
    wattron(gameWindow, COLOR_PAIR(CP_PURPLE));
    mvwaddch(gameWindow, line, column, '$');
    mvwprintw(gameWindow, line++, column + 1, (std::to_string((int)thisRoundProfit[1])).c_str());
    wattroff(gameWindow, COLOR_PAIR(CP_PURPLE));
    wattron(gameWindow, COLOR_PAIR(CP_BLUE));
    mvwaddch(gameWindow, line, column, '$');
    mvwprintw(gameWindow, line++, column + 1, (std::to_string((int)thisRoundProfit[2])).c_str());
    wattroff(gameWindow, COLOR_PAIR(CP_BLUE));
    wattron(gameWindow, COLOR_PAIR(CP_GREEN));
    mvwaddch(gameWindow, line, column, '$');
    mvwprintw(gameWindow, line++, column + 1, (std::to_string((int)thisRoundProfit[3])).c_str());
    wattroff(gameWindow, COLOR_PAIR(CP_GREEN));

    //Draw a line to separate each prize profit from the total
    wattron(gameWindow, A_ALTCHARSET);
    for (int i = 0; i < 7; i++) {
        mvwaddch(gameWindow, line, column++, 113);
    }
    mvwaddch(gameWindow, line++, column, 113);
    wattroff(gameWindow, A_ALTCHARSET);

    //Total ammount, will be printed in green if positive and in red if negative.
    column = 38;
    mvwprintw(gameWindow, line, 32, "Total: ");
    mvwaddch(gameWindow, line, column, '$');

    if (0 < thisRoundProfit[4]) {
        wattron(gameWindow, COLOR_PAIR(CP_GREEN));
        waddch(gameWindow, '+');
    }
    else if(0 > thisRoundProfit[4]){
        wattron(gameWindow, COLOR_PAIR(CP_RED));
    }
    wprintw(gameWindow, (std::to_string((int)thisRoundProfit[4])).c_str());
    wattroff(gameWindow, COLOR_PAIR(CP_GREEN));
    wattroff(gameWindow, COLOR_PAIR(CP_RED));

    wrefresh(gameWindow);
}

/*
Method name:    getAndHandleInputLootBoxGame
Description:    Gets user input and respond accordingly
Outputs:        n/a
Inputs:         int userInput: stores user preso
                int playerBetHL: H/L choosen by player
                int dieNumber: Die actual number
                float thisRoundProfit: How much player won or lost this round
Author:         Renato Pepe
Creation date:  25/08/2021
Last modified:  25/08/2021
*/
void getAndHandleInputLootBoxGame(int userInput, float& playerWallet, float& chipValue, float& betValue, bool prizesStatus[4], float thisRoundProfit[5]) {

    //Respond to user input
    switch (userInput) {
        //Decrease chip value
    case KEY_LEFT:
    case 'a':
    case 'A':
        changeChipValue(chipValue, '-');
        break;
        //Increase chip value
    case KEY_RIGHT:
    case 'd':
    case 'D':
        changeChipValue(chipValue, '+');
        break;
        //Increase bet value
    case KEY_UP:
    case 'w':
    case 'W':
        if ((betValue + chipValue) <= playerWallet) {
            betValue = betValue + chipValue;
        }
        else {
            betValue = playerWallet;
        }
        break;
        //Decrease bet value
    case KEY_DOWN:
    case 's':
    case 'S':
        if ((betValue - chipValue) >= 0) {
            betValue = betValue - chipValue;
        }
        else {
            betValue = 0;
        }
        break;
        //Place a number bet
   
    case 'e':
    case 'E':
    case '\n':
        //run animationa
        
        //Reset profits
        thisRoundProfit[0] = thisRoundProfit[1] = thisRoundProfit[2] = thisRoundProfit[3] = 0;
        //Draw the prizes, 0 = sucessfull, !0 = failed
        int drawPrizes[4];
        drawPrizes[0] = rand() % 100;
        drawPrizes[1] = rand() % 20;
        drawPrizes[2] = rand() % 4;
        drawPrizes[3] = rand() % 2;

        for (int i = 0; i < 4; i++) {
            if (0 == drawPrizes[i]) {
                prizesStatus[i] = true;
            }
            else {
                prizesStatus[i] = false;
            }
        }

        if (prizesStatus[0]) {
            thisRoundProfit[0] = betValue * 10;
        }
        if (prizesStatus[1]) {
            thisRoundProfit[1] = betValue * 4;
        }
        if (prizesStatus[2]) {
            thisRoundProfit[2] = betValue * 1.4;
        }
        if (prizesStatus[3]) {
            thisRoundProfit[3] = betValue * 0.7;
        }

        thisRoundProfit[4] = thisRoundProfit[0] + thisRoundProfit[1] + thisRoundProfit[2] + thisRoundProfit[3] - betValue;
        playerWallet = playerWallet + thisRoundProfit[4];
        break;
    default:
        //other inputs do nothing
        break;
    }
}



