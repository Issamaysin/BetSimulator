/* ******************************************************************** */
/* File name:        BetSimulator.cpp                                   */
/* File description: Main file for the BetSimulator project, which is a */
/*                    compilation of simple games involving bets        */
/* Author name:      Renato Pepe       				                    */
/* Creation date:    16/08/2021                                         */
/* Revision date:    18/08/2021                                         */
/* **********************************************************************/

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
    Function declarations for this file.
*/
//testing boxChance balance 
void testBoxChance();

int main()
{
    //Initial setup
    gameInit();

    //test menu screen
    gameLoop();
    
    
    
    endwin();
    _getch();
    return 0;
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
    cout << "\nTest box Chance:\n";
    //print loop
    char exitLoop;
    float cash = 1000;
    float payout[4] = { 10, 4, 1, 0.3 };
    float chipValue = 100;

    while (exitLoop = _getch() != 'e') {
        float cashThisBet = -chipValue;
        int boxesLed[4];
        boxesLed[0] = rand() % 50;
        boxesLed[1] = rand() % 10;
        boxesLed[2] = rand() % 4;
        boxesLed[3] = rand() % 2;

        char boxesSymbol[4] = { 'L', 'R', 'A', 'V' };

        for (int i = 0; i < 4; i++) {
            if (0 == boxesLed[i]) {
                cashThisBet = cashThisBet + payout[i] * 100;
                cout << " " << boxesSymbol[i];
            }
            else {
                cout << "  ";
            }
        }
        cash = cash + cashThisBet;
        cout << " cash = $ " << cash << " This Bet = $" << cashThisBet << "\n";

    }
}



