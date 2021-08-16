/* ******************************************************************** */
/* File name:        BetSimulator.cpp                                   */
/* File description: Main file for the BetSimulator project, which is a */
/*                    compilation of simple games involving bets        */
/* Author name:      Renato Pepe       				                    */
/* Creation date:    16/08/2021                                         */
/* Revision date:    16/08/2021                                         */
/* **********************************************************************/

#include <iostream>
#include <conio.h>
#include <list>
#include <string>
#include "curses.h"
#include "menu.h"


using std::cout;
using std::list;
using std::string;

/*
    Function declarations for this file.
*/
//testing boxChance balance 
void testBoxChance();
//Start and configure the default curses screen
int startCurses();
//Runs menu screen that lets user select which game will be played
void screen_Menu();

int main()
{
    cout << "Maximize your terminal screen for a better performance then press any key \n";
    _getch();

    //init rand
    srand(static_cast<unsigned int>(std::time(nullptr)));
    rand();

    //init curses screen
    startCurses();

    //test menu screen
    screen_Menu();

    _getch();
    return 0;
}

/*
Method name:    startCurses    
Description:    Start and configure the curses std screen
Outputs:        int: error flag, return 0 if it couldn't properly start/configure the screen, and 1 if
                      the initialization was sucessfull.
Inputs:         n/a
Author:         Renato Pepe
Creation date:  16/08/2021
Last modified:  16/08/2021
*/
int startCurses() {

    //Starts curses default screen.
    initscr();
    //Remove typed key echo and buffer
    noecho();
    cbreak();

    //Start color mode, if terminal can't support colors exit program and give a warning
    if (!has_colors) {
        cout << "Terminal doesnt have colors :(" << std::endl;
        _getch();
        return 0;
    }
    start_color();
    refresh();

    //Remove blinking cursor indicator and start keypad mode (can read keyboard arrows)
    curs_set(0);
    keypad(stdscr, true);

    return 1;
}

/*
Method name:    testBoxChance
Description:    Function made quickly to test the box game balance
Outputs:        n/a
Inputs:         n/a
Author:         Renato Pepe
Creation date:  16/08/2021
Last modified:  16/08/2021
*/
void testBoxChance() {
    /*
        Test box chance. Prints directly on temrinal, just for testing.
    */
    cout << "\nTest box Chance: ";
    //print loop
    char exitLoop;
    float cash = 1000;
    float payout[4] = { 10, 4, 1, 0.3 };

    while (exitLoop = _getch() != 'e') {
        float cashThisBet = -100;
        int boxesLed[4];
        boxesLed[0] = rand() % 50;
        boxesLed[1] = rand() % 10;
        boxesLed[2] = rand() % 4;
        boxesLed[3] = rand() % 2;

        char boxesSymbol[4] = { 'L', 'R', 'A', 'V' };

        for (int i = 0; i < 4; i++) {
            if (0 == boxesLed[i]) {
                cashThisBet = cashThisBet + payout[i] * 100;
                cout << boxesSymbol[i] << " ";
            }
            else {
                cout << "  ";
            }
        }
        cash = cash + cashThisBet;
        cout << " cash = $ " << cash << " This Bet = $" << cashThisBet << "\n";

    }
}

