#pragma once
/* ********************************************************************** */
/* File name:        menu.h                                               */
/* File description: File where the methods of the game menu are declared */
/*                    -menu let's user select and enter a game.           */
/* Author name:      Renato Pepe       				                      */
/* Creation date:    16/08/2021                                           */
/* Revision date:    20/08/2021                                           */
/* ************************************************************************/

//#include "gameRun.h"

/*
	Defines and enums
*/
#define screen_Height 20
#define screen_Width 60
#define numberOfGames 2

/*
Method name:    screen_Menu
Description:    Display the Menu where user can select the game they'll be playing, and run the selected game.
Outputs:        n/a
Inputs:         n/a
Author:         Renato Pepe
Creation date:  16/08/2021
Last modified:  20/08/2021
*/
void screen_Menu(float& playerWallet, float& chipValue, gameState& state, WINDOW*& gameWindow);