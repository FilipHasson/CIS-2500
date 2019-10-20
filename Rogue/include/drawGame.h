/*************************drawGame.h****************************
Student Name: Filip Hasson                   Student Number:  0878596
Date: 03/12/2015                             Course Name: CIS 2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
****************************************************************************/

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

typedef struct topLeftCorner
{
    int y;
    int x;
}topLeftCorner;


/*
initBoard: initializes the ncurses and the game board for the first time
in: rooms, monsters, player, devflags, and the grid
out nothing
post game board is created
*/
void initBoard(room rooms[6], int grid[50][100],monsters* mon,int devFlags[5],int* tMon, playerSt* hero);

/*
drawHalls pairs doors, and procedurally generates halls
in: rooms, grid, topleft corner, flags
out: none
post: hallways drawn and added to grid
*/
void drawHalls (room rooms[6], int grid[50][100], topLeftCorner* tl,int flag);

/*
drawRoom, draws a specific room with all the items in it
in: room, topleft corner, grid, monsters, totall monstes, monsters placed
out: returns the generated room
post: room saved, drawn, and stored in grid
*/
room drawRoom(room thisRoom, int tlx, int tly,int grid[50][100], monsters* mon,int* tMon,int* monPlaced);

/*
drawZoneLines, developer option to see potential room spawn area
in: none
out: none
post: spawn zone lines drawn
*/
void drawZoneLines ();

/*
randMovX, generats the random x displacement for a room
in roomWidth
out: room x displacement
post: int returned
*/
int randMovX (int roomW);

/*
randMovY, generates the random y displacement for a room
in: room length
out room y displacement
post int returned
*/
int randMovY (int roomL);

/*
clearScreen, cleans the game screen
in: none
out: none
post: gameboard erased
*/
void clearScreen (void);

/*
quickDraw, redraws the board solely from the grid
in grid
out none
post game board redrawn
*/
void quickDraw (int grid [50][100]);
