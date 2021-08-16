/* ********************************************************************** */
/* File name:        menu.cpp                                             */
/* File description: File where the methods of the game menu are defined  */
/*                    -menu let's user select and enter a game.           */
/* Author name:      Renato Pepe       				                      */
/* Creation date:    16/08/2021                                           */
/* Revision date:    16/08/2021                                           */
/* ************************************************************************/

/*
    Includes
*/
#include <iostream>
#include <conio.h>
#include <list>
#include <string>
#include "curses.h"
#include "menu.h"

/*
    Frequently used namespaces.
*/
using std::cout;
using std::list;
using std::string;

/*
Method name:    screen_Menu
Description:    Display the Menu where user can select the game they'll be playing, and run the selected game.
Outputs:        n/a
Inputs:         n/a
Author:         Renato Pepe
Creation date:  16/08/2021
Last modified:  16/08/2021
*/
void screen_Menu() {

    //Get size of the default curses screen (size of the terminal).
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);

    //Check if the terminal size is big enough to properly run the menu screen.
    if (xMax < menuScreen_Width || yMax < menuScreen_Height) {
        cout << "Ops, your terminal screen current size is less than the minimum size required for this game\n";
        return;
    }

    //Creates and configure menu window
    WINDOW* menuWin = newwin(menuScreen_Height, menuScreen_Width, 2, 2);
    keypad(menuWin, true);
    box(menuWin, 0, 0);
    wrefresh(menuWin);

    //Starts menu, prints Title and game list with a highlighted game.
    mvwprintw(menuWin, 1, 3, "Bet Simulator");

    /*  ~~ last edit ended here, everything below is the placeholder menu from other code. ~~*/

    string menu[4] = { "op1", "op2", "op3", "op4" };

    int highlight = 0;
    int key;
    while (1) {
        for (int i = 0; i < 4; i++) {
            if (i == highlight) {
                wattron(menuWin, A_REVERSE);
            }
            mvwprintw(menuWin, 3 + i, 1, menu[i].c_str());
            if (i == highlight) {
                wattroff(menuWin, A_REVERSE);
            }
        }

        key = wgetch(menuWin);

        if (key == KEY_DOWN) {
            highlight++;
            if (highlight > 3) {
                highlight = 0;
            }
        }
        else if (key == KEY_UP) {
            highlight--;
            if (highlight < 0) {
                highlight = 3;
            }
        }
        else if (key == 'q') {
            break;
        }
        else {
            //nothing
        }
    }
    refresh();
    mvprintw(3, 9, "You chose: %s ", menu[highlight].c_str());
    refresh();
    wgetch(menuWin);
    //_getch();


    delwin(menuWin);
}