/* ***********************************************************************/
/* File name:        gameRun.cpp                                         */
/* File description: Cpp file where main game loop, core initializations */
/*                    and auxiliar methods are defined                   */
/* Author name:      Renato Pepe       				                     */
/* Creation date:    16/08/2021                                          */
/* Revision date:    24/08/2021                                          */
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
#include "game_LootBox.h"

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
    keypad(stdscr, TRUE);

    return 1;
}

/*
Method name:    gameInit
Description:    Initialize game, set up curses default screen and random number generator.
Outputs:        n/a
Inputs:         n/a
Author:         Renato Pepe
Creation date:  18/08/2021
Last modified:  24/08/2021
*/
void gameInit() {

    //Tells user to maximize terminal screen so curses can work properly
    cout << "Maximize your terminal screen for a better performance, then press any key to continue \n";
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
Last modified:  24/08/2021
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
    keypad(gameWindow, TRUE);
    wrefresh(gameWindow);

    //print here the introduction, talking about the simulator and menu commands.
    printStartScreen(gameWindow);

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
        //check if player lost (Wallet = 0), print a defeat screen, reset values to default, and start again
        if (0 >= playerWallet) {
            //Print defeat screen
            printDefeatScreen(gameWindow);

            //Reset values to default so it can start again.
            playerWallet = 2000.0f;
            chipValue = 100.0f;
        }
        //check if player won (Wallet = 999999), print a victory screen, reset values to default, and start again
        if (999999 <= playerWallet) {
            //Print victory screen
            printVictoryScreen(gameWindow);

            //Reset values to default so it can start again.
            playerWallet = 2000.0f;
            chipValue = 100.0f;
        }

        //Enter Menu or game
        switch (currentState) {
        case gameState::MENU:
            screen_Menu(playerWallet, chipValue, currentState, gameWindow);;
            break;
        case gameState::GAME1:
            diceGameRun(playerWallet, chipValue, gameWindow);
            currentState = gameState::MENU;
            break;
        case gameState::GAME2:
            lootBoxGameRun(playerWallet, chipValue, gameWindow);
            currentState = gameState::MENU;
            break;
        default:
            //should never enter here
            currentState = gameState::MENU;
            break;
        }

        //Change rand() seed to maximize randomness.
        srand(static_cast<unsigned int>(std::time(nullptr)));
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
    init_pair(CP_ORANGE, 202, COLOR_BLACK);
    init_pair(CP_PURPLE, 13, COLOR_BLACK);
    init_pair(CP_BLUE, COLOR_BLUE, COLOR_BLACK);

}

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

/*
Method name:    printDefeatScreen
Description:    Prints a screen to let player know he lost the game (wallet reached 0)
Outputs:        n/a
Inputs:         WINDOW gameWindow: game window where information will be printed
Author:         Renato Pepe
Creation date:  24/08/2021
Last modified:  24/08/2021
*/
void printDefeatScreen(WINDOW* gameWindow) {
    //Clear what was previously printed on the screen and box the screen
    wclear(stdscr);
    wrefresh(stdscr);
    wclear(gameWindow);
    wrefresh(gameWindow);
    box(gameWindow, 0, 0);

    //Writes "you lost" text
    int line = 2;
    wattron(gameWindow, COLOR_PAIR(CP_RED));
    mvwprintw(gameWindow, line++, 18, "G A M E   O V E R");
    wattroff(gameWindow, COLOR_PAIR(CP_RED));
    line++;
    mvwprintw(gameWindow, line++, 7, "You gambled all your money away and lost.");
    chtype sadFaceAux = ' ' | A_REVERSE;
    mvwaddch(gameWindow, 10, 24, sadFaceAux);
    mvwaddch(gameWindow, 12, 24, sadFaceAux);
    mvwaddch(gameWindow, 10, 27, sadFaceAux);
    mvwaddch(gameWindow, 11, 27, sadFaceAux);
    mvwaddch(gameWindow, 12, 27, sadFaceAux);
    mvwaddch(gameWindow, 9, 28, sadFaceAux);
    mvwaddch(gameWindow, 8, 29, sadFaceAux);
    mvwaddch(gameWindow, 13, 28, sadFaceAux);
    mvwaddch(gameWindow, 14, 29, sadFaceAux);
    mvwprintw(gameWindow, screen_Height - 2, 15, "(press any key to start over)");
    
    //Waits for user to press any key to continue
    wgetch(gameWindow);
}


/*
Method name:    printVictoryScreen
Description:    Prints a screen to let player know he won the game (wallet reached max value o 999.999)
Outputs:        n/a
Inputs:         WINDOW gameWindow: game window where information will be printed
Author:         Renato Pepe
Creation date:  24/08/2021
Last modified:  24/08/2021
*/
void printVictoryScreen(WINDOW* gameWindow) {
    //Clear what was previously printed on the screen and box the screen
    wclear(stdscr);
    wrefresh(stdscr);
    wclear(gameWindow);
    wrefresh(gameWindow);
    box(gameWindow, 0, 0);

    //Writes "you won" text
    int line = 2;
    int auxCongratulationsXPosition = 15;
    wattron(gameWindow, COLOR_PAIR(CP_GREEN));
    mvwprintw(gameWindow, line++, auxCongratulationsXPosition, "C O N G R A T U L A T I O N S");
    wattroff(gameWindow, COLOR_PAIR(CP_GREEN));
    line++;
    mvwprintw(gameWindow, line++, 5, "You have become a millionaire!");
    line++;
    mvwprintw(gameWindow, line++, 5, "Unfortunately the cassino can't handle any more loses");
    mvwprintw(gameWindow, line++, 2, "and it's kicking you out. Go enjoy your new fortune!");

    mvwprintw(gameWindow, screen_Height - 2, 15, "(press any key to start over)");
    //Waits for user to press any key to continue (twice so user don't skip this screen acidentally, since it's really hard to get here)
    wgetch(gameWindow);
    wgetch(gameWindow);
}



/*
Method name:    printStartScreen
Description:    Prints screen that introduces the simulator and displays Menu commands.
Outputs:        n/a
Inputs:         WINDOW gameWindow: game window where information will be printed
Author:         Renato Pepe
Creation date:  24/08/2021
Last modified:  24/08/2021
*/
void printStartScreen(WINDOW* gameWindow) {
    //Clear what was previously printed on the screen and box the screen
    wclear(stdscr);
    wrefresh(stdscr);
    wclear(gameWindow);
    wrefresh(gameWindow);
    box(gameWindow, 0, 0);

    int line = 2;
    mvwprintw(gameWindow, line++, 12, "Welcome to the Bet simulator");
    line++;
    mvwprintw(gameWindow, line++, 1, "-You can select between the available games to make bets.");
    line++;
    mvwprintw(gameWindow, line++, 1, "-Menu controls:");
    mvwprintw(gameWindow, line++, 2, "UP/DOWN arrows: select between games");
    mvwprintw(gameWindow, line++, 2, "E:              enter a game");
    mvwprintw(gameWindow, line++, 2, "X:              exit simulator");
    line++;
    mvwprintw(gameWindow, line++, 2, "(w/a/s/d will work the same as arrows)");

    mvwprintw(gameWindow, screen_Height - 2, 15, "(press any key to continue)");
    wgetch(gameWindow);
}
