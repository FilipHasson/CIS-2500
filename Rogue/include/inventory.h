/*************************inventory.h****************************
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
openInv, opens the main inventory window
in inventory, grid, hero
out none
post inv open
*/
void openInv (inventory* inv,int grid[50][100],playerSt* hero);

/*
drawWepInv, opens the weapons tab of the inventory window
in inventory hero
out none
post weapons displayed
*/
void drawWepInv (inventory* inv,playerSt* hero);

/*
drawPotInv, opens the potions tab of the inventory window
in inventory, hero
out none
post potions displayed
*/
void drawPotInv (inventory*inv,playerSt* hero);

/*
drawMagInv, opens the magic tab of the inventory window
in inventory, hero
out none
post magic displayed
*/
void drawMagInv (inventory*inv,playerSt* hero);

/*
dumpInv, dumps all collected items at the end of the game
in inventory
out none
post game closes
*/
void dumpInv (inventory*inv);

/*
clearInvMenu, erases the weapons/potions/magic tab of the inventory
in none
out none
post tab cleared
*/
void clearInvMenu ();