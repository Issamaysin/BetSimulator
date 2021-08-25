#pragma once

/* **************************************************************************/
/* File name:        gameRun.h                                              */
/* File description: Header file where main game loop, core initializations,*/
/*                     auxiliar methods and types are declared              */
/* Author name:      Renato Pepe       				                        */
/* Creation date:    16/08/2021                                             */
/* Revision date:    25/08/2021                                             */
/* **************************************************************************/


/*
    Defines and enums
*/
//States for the game loop state machine.
enum class gameState {MENU,      //Main menu where games are selected
                      GAME1,     //Dice game
                      GAME2,     //Loot box game
                      EXIT };    //State that can be set by the menu to end the program.

//Color pairs
#define CP_RED      1
#define CP_GREEN    2
#define CP_BLUE     3
#define CP_ORANGE   4
#define CP_PURPLE   5

//Screen proportions
#define screen_Height 20
#define screen_Width 60
//Number of games currently implemented
#define numberOfGames 2

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
Last modified:  24/08/2021
*/
void gameInit();

/*
Method name:    gameLoop
Description:    Loop where game happens, works like a state machine where the states are the games and main menu
Outputs:        n/a
Inputs:         n/a
Author:         Renato Pepe
Creation date:  18/08/2021
Last modified:  25/08/2021
*/
void gameLoop();

/*
Method name:    initColorPairs
Description:    Define the color pairs that will be used on all games.
Outputs:        n/a
Inputs:         n/a
Author:         Renato Pepe
Creation date:  22/08/2021
Last modified:  25/08/2021
*/
void initColorPairs();


/*
Method name:    changeChipValue
Description:    Increase or decrease the chip value according to user input
Outputs:        n/a
Inputs:         float chipValue: current chip value
                char increaseOrDecrease: flag to check it chip is gonna increase ('+') or decrease('-')
Author:         Renato Pepe
Creation date:  22/08/2021
Last modified:  22/08/2021
*/
void changeChipValue(float& chipValue, char increaseOrDecrease);

/*
Method name:    printDefeatScreen
Description:    Prints a screen to let player know he lost the game (wallet reached 0)
Outputs:        n/a
Inputs:         WINDOW gameWindow: game window where information will be printed
Author:         Renato Pepe
Creation date:  24/08/2021
Last modified:  24/08/2021
*/
void printDefeatScreen(WINDOW* gameWindow);


/*
Method name:    printVictoryScreen
Description:    Prints a screen to let player know he won the game (wallet reached max value o 999.999)
Outputs:        n/a
Inputs:         WINDOW gameWindow: game window where information will be printed
Author:         Renato Pepe
Creation date:  24/08/2021
Last modified:  24/08/2021
*/
void printVictoryScreen(WINDOW* gameWindow);

/*
Method name:    printStartScreen
Description:    Prints screen that introduces the simulator and displays Menu commands.
Outputs:        n/a
Inputs:         WINDOW gameWindow: game window where information will be printed
Author:         Renato Pepe
Creation date:  24/08/2021
Last modified:  25/08/2021
*/
void printStartScreen(WINDOW* gameWindow);

