/*************************a1.c****************************
Student Name: Filip Hasson                   Student Number:  0878596
Date: 01/16/2015                            Course Name: CIS  2500
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

void playGame (int resume, char pOneName[40], char pTwoName[40],int savedGrid[7][7]);
void drawScreen (int height, int width, int grid[7][7]);
void selectedBox (int collumn, int row);
void clearSelected (int collumn, int row, int last);
void drawX (int collumns, int rows);
void drawO (int collomns, int rows);
void drawBlock (int collumns, int rows);
