****************************************************
Filip Hasson		0878596
CIS2500			Assignment 2 Logo
01/16/2015
****************************************************


************
Compilation
************
	gcc -Wall -pedantic -std=c99 ./src/a2.c ./src/functions.c -Iinclude -lncurses -o ./bin/runMe

***********************
Running the program(s)
***********************
	./bin/runMe


*****************
Known Limitations
*****************
User cannot enter text more than 100 characters long, or more than 98 without a single space
rt and lt will round to the nearest 45 degree angle when rotating amongst different degrees, 30/45 ie: rt 30 + rt 45 = rt 45
fw will not let you go out of bounds


*****************
Testing Done
*****************
all angles, and colors work
all implemented commands work (fd, bk, rt, lt, st, ht, setxy, clean, setpencolor)
successfully saves user made code


****************
Bonus Objectives
****************
Implemented setxy, st, ht, and clean
