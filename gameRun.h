#pragma once

/* **************************************************************************/
/* File name:        gameRun.h                                              */
/* File description: Header file where main game loop, core initializations */
/*                    and auxiliar methods are declared                     */
/* Author name:      Renato Pepe       				                        */
/* Creation date:    16/08/2021                                             */
/* Revision date:    18/08/2021                                             */
/* **************************************************************************/


/*
    Defines and enums
*/
//States for the game loop state machine.
enum class gameState {MENU,      //Main menu where games are selected
                      GAME1,     //Dice game
                      GAME2,     //Loot box game
                      EXIT };    //State that can be set by the menu to end the program.

/*
    Function declarations
*/
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
int startCurses();

/*
Method name:    gameInit
Description:    Initialize game, set up curses default screen and random number generator.
Outputs:        n/a
Inputs:         n/a
Author:         Renato Pepe
Creation date:  18/08/2021
Last modified:  18/08/2021
*/
void gameInit();

/*
Method name:    gameLoop
Description:    Loop where game happens, works like a state machine where the states are the games and main menu
Outputs:        n/a
Inputs:         n/a
Author:         Renato Pepe
Creation date:  18/08/2021
Last modified:  18/08/2021
*/
void gameLoop();
