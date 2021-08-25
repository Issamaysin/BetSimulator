#pragma once

/* ******************************************************************************/
/* File name:        game_Dice.h                                                */
/* File description: Header file where dice game methods and types are declared */
/* Author name:      Renato Pepe       				                            */
/* Creation date:    20/08/2021                                                 */
/* Revision date:    24/08/2021                                                 */
/* ******************************************************************************/


/*
    Function declarations
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
void diceGameCommandsScreen(WINDOW *& gameWindow);

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
void diceGameRun(float& playerWallet, float& chipValue, WINDOW*& gameWindow);

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
void printDiceGameScreen(float playerWallet, float chipValue, float betValue, int playerBetNumber, int dieNumber, int playerBetHL, float thisRoundProfit, WINDOW*& gameWindow);

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
void getAndHandleInputDiceGame(int userInput, float& playerWallet, float& chipValue, float& betValue, int& playerBetNumber, int& dieNumber, int& playerBetHL, float& thisRoundProfit);








