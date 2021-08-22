#pragma once

/* ******************************************************************************/
/* File name:        game_Dice.h                                                */
/* File description: Header file where dice game methods and types are declared */
/* Author name:      Renato Pepe       				                            */
/* Creation date:    20/08/2021                                                 */
/* Revision date:    22/08/2021                                                 */
/* ******************************************************************************/


/*
    Defines and enums
*/



/*
    Function declarations
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
void diceGameCommandsScreen(WINDOW *& gameWindow);

/*
Method name:    diceGameRun
Description:    Main dice game method, initialize game parameters and start the game loop (where the other methods will be called)
Outputs:        n/a
Inputs:         n/a
Author:         Renato Pepe
Creation date:  20/08/2021
Last modified:  22/08/2021
*/
void diceGameRun(float& playerWallet, float& chipValue, WINDOW*& gameWindow);

/*
Method name:    printDiceGameScreen
Description:    Prints dice game data on the screen.
Outputs:        n/a
Inputs:         n/a
Author:         Renato Pepe
Creation date:  20/08/2021
Last modified:  22/08/2021
*/
void printDiceGameScreen(float playerWallet, float chipValue, float betValue, int playerBetNumber, int dieNumber, int playerBetHL, float thisRoundProfit, WINDOW*& gameWindow);











