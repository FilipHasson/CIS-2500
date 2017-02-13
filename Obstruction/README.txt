****************************************************
Filip Hasson		0878596
CIS2500			Assignment 1 Obstruction
01/16/2015
****************************************************


************
Compilation
************
	gcc -Wall -pedantic -std=c99 ./src/a1.c -Iinclude -lncurses -o ./bin/output

***********************
Running the program(s)
***********************
	./bin/output


*****************
Known Limitations
*****************
Player name cannot be more than 40 characters
Score file will break if more than 100 lines are saved in it (this should never happen though)
If the user attempts to set the Save and Score files manually and starts the files with the appropriate program generated header
-errors may occur with the feature as the safe guards will not be triggered while files are truly corrupt


*****************
Testing Done
*****************
Board bounds tested
all buttons not used have no effect
game functions properly
save game function works
delete game in function works
scores are saved for players, can been seen again ingame if same names are entered
no errors if scores and save files are deleted, the program regenerates them if they are deleted or corrupt

****************
Bonus Objectives
****************
Has a working AI called EDI (Extremely Dumb Intelegence) that plays its turn in the first avaiable space
Has a working hint AI called IDE (Intelegence Dumb Extremely) that recommends playing in the last available space
-Note If you use the hints while facing the AI you will win every time! IDE>EDI
Has a working scores file named scores.fil
-this file saves the scores from previous matches
Has a working save file called save.fil
-this file will store the names and gameboard if a game in progress is quit useing the q key
Specific and helpful instructions for playing the game are located beneath the game board -a very accessible location
Game fully uses and implements COLOR!
-with a black background
-player one is red, player two is blue
-the gameboard and instructions are in white
-this provides the standard red vs blue gameplay
-and has the best level of contrast viewable by the human eye!
