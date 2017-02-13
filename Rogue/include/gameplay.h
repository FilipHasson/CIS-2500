/*************************gameplay.h****************************
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
playGame, runs gameplay once the game is fully initialized
in, grid, monsters, player, totalMonsters
out, none
post, game over
*/
void playGame (int grid[50][100],monsters* monster, playerSt* hero, int* tMon);

/*
drawHero, draws the hero
in, x and y coord
out none
post, heroes new position is drawn
*/
void drawHero(int x,int y);

/*
playerMove determines what should happen when the player moves
in, new x and y coordinate, original cordinates her, grid, inventory, monsters
out none
post, player moves, OR attacks monster, OR picks up item, OR nothing
*/
void playerMove (int nY, int nX, int hY, int hX,playerSt* hero, int grid[50][100],inventory* inv,monsters*mon);

/*
draws the floor behind player or monster
in x y and last tile unit
out none
post, redraw after movement
*/
void drawLast(int y, int x, int last);

/*
updates the player stats, healthbar and other information at the bottom of the screen
in hero
out none
post stats updated
*/
void updateStats (playerSt* hero);

/*
combatPause, pauses game during combat
in none
out none
post, things can continue
*/
void combatPause();

/*
monMove, the AI for each type of monster
in monsters, total monsters, grid, hero
out none
post monsters move
*/
void monMove (monsters* monster, int* tMon, int grid[50][100], playerSt* hero);
