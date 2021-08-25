#pragma once

/* **********************************************************************************/
/* File name:        game_LootBox.h                                                 */
/* File description: Header file where loot box game methods and types are declared */
/* Author name:      Renato Pepe       				                                */
/* Creation date:    24/08/2021                                                     */
/* Revision date:    24/08/2021                                                     */
/* **********************************************************************************/


/*
    Function declarations
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
void lootBoxGameCommandsScreen(WINDOW*& gameWindow);



/*
Method name:    lootBoxGameRun
Description:    Main loot box game method, initialize game parameters and start the game loop (where the other methods will be called)
Outputs:        n/a
Inputs:         float playerWallet: Player's current cash
                float chipValue: Current chip value
                WINDOW gameWindow: curses window where game happens
Author:         Renato Pepe
Creation date:  24/08/2021
Last modified:  24/08/2021
*/
void lootBoxGameRun(float& playerWallet, float& chipValue, WINDOW*& gameWindow);



void printLootBoxGameScreen(bool prizesStatus[4], float playerWallet, float chipValue, float betValue, float thisRoundProfit[5], WINDOW*& gameWindow);
