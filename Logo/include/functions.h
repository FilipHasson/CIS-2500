#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cursorS
{
    int locX;
    int locY;
    int dir;
    int color;
}cursorT;

/*
drawCursor: draws the cursor on the screen
In: the cursor struct
Out: void
post returns to where called
*/
void drawCursor (cursorT curs);


/*
clearUserText: clears the users entered text
in: void
out: void
post: program keeps running
*/
void clearUserText (void);


/*
clearMessageText: clears programm messages to the user
in: void
out void
post keeps running
*/
void clearMessageText (void);


/*
forward: moves the character forward and draws the line if pen is down
in: cursorT * curs, int dist, in pu
out void
post line and new cursor are drawn
*/
void forward (cursorT * curs, int dist,int pu);


/*
back: moves the character back and draws the line if pen is down
in: cursorT * curs, int dist, in pu
out: void
post: line and new cursor are drawn
*/
void back (cursorT * curs, int dist,int pu);


/*
rotateRight: rotates the cursor's aim right by an angle
in: cursorT * curs, int angle
out: void
post: next forward or back will be at a new angle
*/
void rotateRight (cursorT * curs, int angle);


/*
rotateLeft: rotates the cursor's aim right by an angle
in: cursorT * curs, int angle
out: void
post: next forward or back will be at a new angle
*/
void rotateLeft (cursorT * curs, int angle);


/*
fill: draws the line
in: int locX, int locY
out: void
post: #'s are drawn
*/
void fill (int locX, int locY);


/*
clean: cleans the board but leaves cursor on
in: void
out: void
post: board is clean
*/
void clean (void);