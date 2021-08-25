/* ***********************************************************************/
/* File name:        game_Dice.cpp                                       */
/* File description: Cpp file where dice game methods are defined        */
/* Author name:      Renato Pepe       				                     */
/* Creation date:    20/08/2021                                          */
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
Inputs:         WINDOW gameWindow: curses screen where game happens
Author:         Renato Pepe
Creation date:  20/08/2021
Last modified:  24/08/2021
*/
void diceGameCommandsScreen(WINDOW*& gameWindow) {
    //Clear what was previously printed on the screen and box the screen
    wclear(stdscr);
    wrefresh(stdscr);
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
    mvwprintw(gameWindow, line++, 1, "(if both bet types are made the bet will be divided)");
    line++;
    mvwprintw(gameWindow, line++, 1, "-Controls:");
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
Inputs:         float playerWallet: Player's current cash
                float chipValue: Current chip value
                WINDOW gameWindow: curses window where game happens
Author:         Renato Pepe
Creation date:  20/08/2021
Last modified:  24/08/2021
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
    //Variable that stores user input (initialized with a 'random' char that's different than 'q' so loop can start properly)
    int userInput = 'n';

    //Main game loop
    while ('q' != userInput && 'Q' != userInput) {

        //BetValue can't be greater than playerWallet
        if (betValue > playerWallet) {
            betValue = playerWallet;
        }

        //Print data on screen
        printDiceGameScreen(playerWallet, chipValue, betValue, playerBetNumber, dieNumber, playerBetHL, thisRoundProfit, gameWindow);
        
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
        getAndHandleInputDiceGame(userInput, playerWallet, chipValue, betValue, playerBetNumber, dieNumber, playerBetHL, thisRoundProfit);
    }

}

/*
Method name:    printDiceGameScreen
Description:    Prints dice game data on the screen.
Outputs:        n/a
Inputs:         float playerWallet: Player's current stored cash
                float chipValue: Current chip value
                float betValue: Current ammount being bet
                int playerBetNumber: Die number choosen by player
                int playerBetHL: H/L choosen by player
                int dieNumber: Die actual number
                float thisRoundProfit: How much player won or lost this round
                WINDOW gameWindow: curses screen where game happens
Author:         Renato Pepe
Creation date:  20/08/2021
Last modified:  24/08/2021
*/
void printDiceGameScreen(float playerWallet, float chipValue, float betValue, int playerBetNumber, int dieNumber, int playerBetHL, float thisRoundProfit, WINDOW *& gameWindow) {
    //Clear what was previously printed on the screen and box the screen
    wclear(stdscr);
    wrefresh(stdscr);
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

    /*
        Draw die
    */
    line = 5;
    int drawDieXPosition = screen_Width - 25;
    //Draw upper line
    wattron(gameWindow, A_ALTCHARSET);
    mvwaddch(gameWindow, line++, drawDieXPosition, 108);
    waddch(gameWindow, 113);
    waddch(gameWindow, 113);
    waddch(gameWindow, 113);
    waddch(gameWindow, 113);
    waddch(gameWindow, 113);
    waddch(gameWindow, 107);
    wattroff(gameWindow, A_ALTCHARSET);

    //Draw die interior
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

    //Draw side lines
    wattron(gameWindow, A_ALTCHARSET);
    mvwaddch(gameWindow, line - 3, drawDieXPosition, 120);
    mvwaddch(gameWindow, line - 2, drawDieXPosition, 120);
    mvwaddch(gameWindow, line - 1, drawDieXPosition, 120);
    mvwaddch(gameWindow, line - 3, drawDieXPosition + 6, 120);
    mvwaddch(gameWindow, line - 2, drawDieXPosition + 6, 120);
    mvwaddch(gameWindow, line - 1, drawDieXPosition + 6, 120);

    //Draw bottom line
    mvwaddch(gameWindow, line++, drawDieXPosition, 109);
    waddch(gameWindow, 113);
    waddch(gameWindow, 113);
    waddch(gameWindow, 113);
    waddch(gameWindow, 113);
    waddch(gameWindow, 113);
    waddch(gameWindow, 106);
    wattroff(gameWindow, A_ALTCHARSET);

    //Draw profit 
    line++;
    mvwprintw(gameWindow, line++, drawDieXPosition - 8, "Round profit total: $ ");
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

/*
Method name:    getAndHandleInputDiceGame
Description:    Gets user input and respond accordingly
Outputs:        n/a
Inputs:         int userInput: stores user pressed key (obs: int so it can fit curses arrow keys)
                float playerWallet: Player's current stored cash
                float chipValue: Current chip value
                float betValue: Current ammount being bet
                int playerBetNumber: Die number choosen by player
                int playerBetHL: H/L choosen by player
                int dieNumber: Die actual number
                float thisRoundProfit: How much player won or lost this round
Author:         Renato Pepe
Creation date:  20/08/2021
Last modified:  24/08/2021
*/
void getAndHandleInputDiceGame(int userInput, float& playerWallet, float& chipValue, float& betValue, int& playerBetNumber, int& dieNumber, int& playerBetHL, float& thisRoundProfit) {
     
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
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
        playerBetNumber = userInput - '0';
        break;
    //Place a High bet
    case 'H':
    case 'h':
        playerBetHL = 1;
        break;
    //Place a Low bet
    case 'L':
    case 'l':
        playerBetHL = 2;
        break;
    //Reset number and HL bets to NA
    case '0':
        playerBetHL = 0;
        playerBetNumber = 0;
        break;
    //Make a bet
    case 'e':
    case 'E':
        //Check if at least one bet type was placed, otherwise do nothing
        if (playerBetHL != 0 || playerBetNumber != 0) {
            //Draw die and update round profit
            dieNumber = rand() % 6 + 1;
            thisRoundProfit = 0;
            //If player made both bet types
            if (0 != playerBetHL && 0 != playerBetNumber) {
                float AuxthisRoundProfit = 0;
                if ((dieNumber >= 4 && playerBetHL == 1) || (dieNumber <= 3 && playerBetHL == 2)) {
                    AuxthisRoundProfit = AuxthisRoundProfit + betValue;
                    thisRoundProfit = AuxthisRoundProfit;
                }
                if (playerBetNumber == dieNumber) {
                    AuxthisRoundProfit = AuxthisRoundProfit + 6 * (betValue/2);
                    thisRoundProfit = AuxthisRoundProfit;
                }
            }
            //If player made only HL bet
            else if(0 == playerBetNumber){
                if ((dieNumber >= 4 && playerBetHL == 1) || (dieNumber <= 3 && playerBetHL == 2)) {
                    thisRoundProfit = 2 * betValue;
                }
            }
            //If player made only a number bet
            else {
                if (playerBetNumber == dieNumber) {
                    thisRoundProfit = 6 * betValue;
                }
            }
            //Update wallet
            thisRoundProfit = thisRoundProfit - betValue;
            playerWallet = playerWallet + thisRoundProfit;
        }
        break;
    default:
        //other inputs do nothing
        break;
    }
}



