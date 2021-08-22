/* ***********************************************************************/
/* File name:        gameRun.cpp                                         */
/* File description: Cpp file where main game loop, core initializations */
/*                    and auxiliar methods are defined                   */
/* Author name:      Renato Pepe       				                     */
/* Creation date:    16/08/2021                                          */
/* Revision date:    22/08/2021                                          */
/* ***********************************************************************/


/*
    Includes
*/
#include <iostream>
#include <conio.h>
#include <list>
#include <string>
#include "curses.h"
#include "gameRun.h"
#include "menu.h"
#include "game_Dice.h"

/*
    Frequently used namespaces.
*/
using std::cout;
using std::list;
using std::string;

/*
    gameRun functions
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
Method name:    gameInit
Description:    Initialize game, set up curses default screen and random number generator.
Outputs:        n/a
Inputs:         n/a
Author:         Renato Pepe
Creation date:  18/08/2021
Last modified:  22/08/2021
*/
void gameInit() {

    //Tells user to maximize terminal screen so curses can work properly
    cout << "Maximize your terminal screen for a better performance then press any key \n";
    _getch();

    //Start random number generator, give it a seed based on the user's PC time;
    srand(static_cast<unsigned int>(std::time(nullptr)));
    //Throws the first random number away (since the first rand is not reliable)
    rand();

    //Setup the curses screen
    startCurses();

    //Set up curses color pairs
    initColorPairs();
}

/*
Method name:    gameLoop
Description:    Loop where game happens, works like a state machine where the states are the games and main menu
Outputs:        n/a
Inputs:         n/a
Author:         Renato Pepe
Creation date:  18/08/2021
Last modified:  20/08/2021
*/
void gameLoop() {

    //Get size of the default curses screen (size of the terminal at the initscreen moment).
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);

    //Check if the terminal size is big enough to properly run the menu screen.
    if (xMax < (screen_Width+3) || yMax < (screen_Height+3)) {
        cout << "Ops, your terminal screen current size is less than the minimum required for this game, try to maximize your terminal screen and run the game again\n";
        return;
    }

    //Creates and configure window
    WINDOW* gameWindow = newwin(screen_Height, screen_Width, 2, 2);
    keypad(gameWindow, true);
    wrefresh(gameWindow);

    /*
        Declarations and definition of variables.
    */

    //Game state that defines what is running (what game or menu)
    gameState currentState = gameState::MENU;
    //Player cash, starts as $2000.00
    float playerWallet = 2000.0f;
    //Chip value starts at $100.
    float chipValue = 100.0f;

    //Main loop.
    while (gameState::EXIT != currentState) {
        switch (currentState) {
        case gameState::MENU:
            screen_Menu(playerWallet, chipValue, currentState, gameWindow);;
            break;
        case gameState::GAME1:
            diceGameRun(playerWallet, chipValue, gameWindow);
            currentState = gameState::MENU;
            break;
        case gameState::GAME2:
            cout << "\nTEST game2\n";
            currentState = gameState::EXIT;
            //run game 2
            break;

        default:
            //should never enter here (I will think of an appropriate response)
            break;
        }

    }

    //Delete screen (free memory)
    delwin(gameWindow);

}


/*
Method name:    initColorPairs
Description:    Define the color pairs that will be used on all games.
Outputs:        n/a
Inputs:         n/a
Author:         Renato Pepe
Creation date:  22/08/2021
Last modified:  22/08/2021
*/
void initColorPairs() {

    init_pair(CP_RED, COLOR_RED, COLOR_BLACK);
    init_pair(CP_GREEN, COLOR_GREEN, COLOR_BLACK);
}

/*
Method name:    changeChipValue
Description:    Increase or decrease the chip value according to user input
Outputs:        n/a
Inputs:         n/a
Author:         Renato Pepe
Creation date:  22/08/2021
Last modified:  22/08/2021
*/
void changeChipValue(float &chipValue, char increaseOrDecrease) {

    float availableChips[9] = { 10.0f, 25.0f, 50.0f, 100.0f, 250.0f, 500.0f, 1000.0f, 2500.0f, 5000.0f };

    //Find current chip value position in the array.
    int currentArrayPosition = 0;
    switch ((int)chipValue) {
    case 25:
        currentArrayPosition = 1;
        break;
    case 50:
        currentArrayPosition = 2;
        break;
    case 100:
        currentArrayPosition = 3;
        break;
    case 250:
        currentArrayPosition = 4;
        break;
    case 500:
        currentArrayPosition = 5;
        break;
    case 1000:
        currentArrayPosition = 6;
        break;
    case 2500:
        currentArrayPosition = 7;
        break;
    case 5000:
        currentArrayPosition = 8;
        break;
    default:
        currentArrayPosition = 0;
        break;
    }

    //Change value accordingly
    if ('-' == increaseOrDecrease && 0 != currentArrayPosition) {
        chipValue = availableChips[currentArrayPosition-1];
    }
    else if ('+' == increaseOrDecrease && 8 != currentArrayPosition) {
        chipValue = availableChips[currentArrayPosition + 1];
    }
}
