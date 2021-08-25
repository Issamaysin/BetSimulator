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

    //test menu screen
    gameLoop();
    
    
    
    endwin();
    return 0;
}




