/*************************parse.h****************************
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

typedef struct playerSt
{
    int locY;
    int locX;
    int level;
    int floor;
    int hp;
    int totalHp; //6+6*leve
    int str; //2*level + items
    int acc; //
    int xp;
    int xpTotal;
    int wepStr;
    int dam;
    int potDur;
    int potStr;
    char equippedWep[30];
}playerSt;

typedef struct monsters
{
    int startRoom;
    int rLocY;
    int rLocX;
    int locY;
    int locX;
    int tile;
    int monID;
    int monNum;
    int xpBoost;
    int hp;//    15  20  25  30  50  90
    int damage;// 3,  4,  5,  9, 15, 30
    int lastMove;
    char type;//  S,  B,  R,  G,  O,  E
    char name[20];
}monsters;

typedef struct door
{
    char wall;
    int dist;
    int room;
    int locX;
    int locY;
    int pLocX;
    int pLocY;
    int paired;
    int pRoom;
    int pNum;
}door;

typedef struct stair
{
    int room;
    int locY;
    int locX;
    int targetLevel;
}stair;

typedef struct roomItem
{
    char type;///////////ALL
    char name[50];///////ALL
    char wepType[10];////WEP
    int wType;///////////WEP
    int wMat;////////////WEP
    int value;///////////GOLD
    int room;////////////ALL?
    int locY;////////////ALL
    int locX;////////////ALL
    int wepStrModifier;//WEP
    int potHealth;///////POT
    int potStrModifier;//POT
    int potDuration;/////POT
    int magStrModifier;//MAG
    int magHpModifier;///MAG
}roomItem;

typedef struct room
{
    int dCnt;
    int iCnt;
    int sCnt;
    int mCnt;
    int length;
    int width;
    int monX [50];
    int monY [50];
    char monT [50];
    int monNT [50];
    roomItem rmItem [100];
    door doors[3];
    stair stairs [20];
}room;

typedef struct inventory
{
    int gold;
    int numP[8]; //8 types of pots
    roomItem pots[8]; //8 types of pots
    int numM[8];
    roomItem mags[8];
    int numW[45];
    roomItem weps[45];

}inventory;


/*
removeNewLine, removes the newline character from a string
in buffer
out none
post, string newline removed
*/
void removeNewline (char buf[150]);

/*
remCh, removes the first character of a string
in buffer
out buffer
post, string shortened
*/
char* remCh (char* buf2);

/*
getSeg, works similarly to strTok, in spliting a string by a certain unit
in buffer, index, buffer2, and seperator unit
out new string
post, separated string returned
*/
char* getSeg (char buff [150],int* index,char*buf2,char sepUnit);

/*
splitCom, splits a string by a comma
in buffer, length
out string
post, string split
*/
char* splitCom (char* buff2, int len);

/*
parseFunc, parses a line of text into a room
in, buffer, roomNum, hero, monsters, devflags, total monsters
out returns created room
post, room created
*/
room parseFunc (char buff[150], int roomNum, playerSt* hero, monsters* mon, int devFlag, int* tMon);

/*
createGold, gives each parsed gold field, a random value
in buffer, buffer2, index, roomnum
out roomItem gold
post gold item created
*/
roomItem createGold (char* buf2, char* buf3, int* in2, int roomNum);

/*
createMagic, generates random properties for each parsed magic field
in buffer, buffer2, index, roomnum
out roomItem magic
post, magic enchantment created
*/
roomItem createMagic (char* buf2, char* buf3, int* in2, int roomNum);

/*
createPotion, generates random properties for each parsed potion field
in buffer, buffer2, index roomnum
out roomItem potion
post, potion created
*/
roomItem createPotion (char* buf2, char* buf3, int* in2, int roomNum);

/*
createWeapn, generates a weapon with random properties for each parsed weapon field
in buffer, buffer2, index roomnum
out roomItem weapon
post, weapon created
*/
roomItem createWeapon (char* buf2, char* buf3, int* in2, int roomNum);

/*
genNum, generates a random number within a given maximum
in maximum
out random number
post, number generated
*/
int genNum (int max);
