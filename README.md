 (under construction)

  Welcome to Bet simulator, a simple game developed in C++, using the Visual Studio IDE and the PDcurses library (https://github.com/wmcbrine/PDCurses), that simulates betting on a variety of different games of chance. 

  User starts with $1000 on the wallet and can select between the available games to bet, the wallet is shared between games, which means user can go back to the main menu and switch between games but keep the profits. User can select the bet value through a,s,d,w and arrow keys, where w/up and s/down will increase/decrease the bet ammount, a/left and d/right will decrease/increase the chip value (chip vaule is the ammount that will be increased/decreased with the a/s/up/down commands).

 Controls: 

+Main menu (menu where game is selected):

  w / up_key    => scrolls up through menu

  s / down_key  => scrolls down through menu

  e / enter     => starts selected (highlighted) game

  x             => exit program

+Game 1 (Dice) :

  a / left_key  => lower chips value

  d / right_key => increases chips value

  w / up_key    => increases bet (ammount increase = chip value)

  s / down_key  => decreases bet (ammount decrease = chip value)

  e / enter     => make a bet

  q             => exit to main menu

  1/2/3/4/5/6   => place a number bet

  h/l           => place a High/Low bet

  0             => withdraw both number and H/L bets


+Game 2 (Loot Box) :

  a / left_key  => lower chips value

  d / right_key => increases chips value

  w / up_key    => increases bet (ammount increase = chip value)

  s / down_key  => decreases bet (ammount decrease = chip value)

  e / enter     => make a bet

  q             => exit to main menu
  

  Game descriptions:
 
 Game 1: Dice

  Bet on a dice roll: User can bet on a number of the dice, which has a 1/6 chance and will reward 6x the bet ammount if sucessfull, or/and High/Low (High = #4 or #5 or #6 and Low = #1 or #2 or #3) which has a 1/2 chance and will reward 2X the bet. 
   obs: If user place a number and a H/L bet the bet ammount will be split in half for each mode.

 Game 2: Loot Box

  In this game the user can bet on a 4 'box' roll, each box is represented by a color and has a different chance and a different reward, a bet will roll the 4 boxes at once and independently, the reward will be the sum of the rewards of each box.
    -Orange: 1/50 chance, 10x payout 
    -Purple: 1/10 chance, 4x payout
    -Blue:   1/4 chance,  1x payout
    -Green:  1/2 chance,  0.3x payout



	
	

