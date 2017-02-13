/*************************preGame.h****************************
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

/*
setZero, initializes all values for monster, hero, and totalMonster pointers
int monster, hero, totalMonsters
out none
post, all pointers initialized
*/
void setZero(monsters* monster, playerSt* hero, int* tMon);

/*
blankRoom, initializes all values of a room
in room
out same room
post, room now has initilized values
*/
room blankRoom (room myRoom);

/*
initGrid, initializes the grid array
in, grid
out none
post, all values of array are initialized
*/
void initGrid(int grid[50][100]);

/*
initInv, initializes all values of the inventory
in, inventory
out none
post inventory initialized
*/
void initInv(inventory* inv);
