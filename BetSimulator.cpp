/* ******************************************************************** */
/* File name:        BetSimulator.cpp                                   */
/* File description: Main file for the BetSimulator project, which is a */
/*                    compilation of simple games involving bets        */
/* Author name:      Renato Pepe       				                    */
/* Creation date:    16/08/2021                                         */
/* Revision date:    25/08/2021                                         */
/* **********************************************************************/
#include "curses.h"
#include "gameRun.h"

int main()
{
    //Initial setup
    gameInit();

    //Run game
    gameLoop();
    
    //Close curses screen
    endwin();
    return 0;
}




