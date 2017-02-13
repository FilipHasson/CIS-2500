/*************************preGame.c****************************
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
#include "parse.h"
#include "drawGame.h"
#include "preGame.h"

room blankRoom (room myRoom)
{
    int x;
    myRoom.dCnt=0;
    myRoom.iCnt=0;
    myRoom.sCnt=0;
    myRoom.mCnt=0;
    myRoom.length=0;
    myRoom.width=0;
    for (x=0; x<50;x++)
    {
        myRoom.monX[x]=0;
        myRoom.monY[x]=0;
        myRoom.monT[x]='M';
        myRoom.monNT[x]=0;
    }
    for (x=0; x<100;x++)
    {
        myRoom.rmItem[x].type='i';
        myRoom.rmItem[x].wType=0;
        myRoom.rmItem[x].wMat=0;
        myRoom.rmItem[x].value=0;
        myRoom.rmItem[x].room=0;
        myRoom.rmItem[x].locY=0;
        myRoom.rmItem[x].locX=0;
        myRoom.rmItem[x].wepStrModifier=0;
        myRoom.rmItem[x].potHealth=0;
        myRoom.rmItem[x].potStrModifier=0;
        myRoom.rmItem[x].potDuration=0;
        myRoom.rmItem[x].magStrModifier=0;
        myRoom.rmItem[x].magHpModifier=0;
        strcpy(myRoom.rmItem[x].name,"0");
        strcpy(myRoom.rmItem[x].wepType,"0");
    }
    for (x=0; x<3;x++)
    {
        myRoom.doors[x].wall='0';
        myRoom.doors[x].dist=0;
        myRoom.doors[x].locX=0;
        myRoom.doors[x].locY=0;
        myRoom.doors[x].pLocY=0;
        myRoom.doors[x].pLocX=0;
        myRoom.doors[x].paired=0;
    }
    for (x=0; x<20;x++)
    {
        myRoom.stairs[x].room=0;
        myRoom.stairs[x].locY=0;
        myRoom.stairs[x].locX=0;
        myRoom.stairs[x].targetLevel=0;
    }
    return(myRoom);
}

void setZero(monsters* monster, playerSt* hero, int* tMon)
{
    int x;
    tMon[0]=0;
    hero->locX=0;
    hero->locY=0;
    hero->level=1;
    hero->hp=10+5*hero->level;
    hero->totalHp=10+5*hero->level;
    hero->str=6+2*hero->level;
    hero->xp=0;
    hero->xpTotal=15+10*hero->level;
    hero->acc=6;
    hero->floor=0;
    hero->wepStr=0;
    hero->dam=hero->wepStr+hero->str;
    hero->potDur=0;
    hero->potStr=0;
    strcpy (hero->equippedWep,"none");
    for (x=0;x<150;x++)
    {
        monster[x].startRoom=0;
        monster[x].rLocY=0;
        monster[x].rLocX=0;
        monster[x].locY=0;
        monster[x].locX=0;
        monster[x].hp=0;
        monster[x].damage=0;
        monster[x].type='M';
        monster[x].tile=0;
        monster[x].monID=0;
        monster[x].monNum=0;
        monster[x].xpBoost=0;
        monster[x].lastMove=0;
        strcpy(monster[x].name,"0");
    }
}

void initGrid(int grid[50][100])
{
    int x;
    int y;
    for (y = 0; y<50;y++)
        for (x=0; x<100; x++)
            grid[y][x]=9;
}

void initInv(inventory* inv)
{
    int x;
    int y;
    int z;
    int wepMult=0;
    inv->gold=0;
    for (x=0 ; x<8 ;x++)
    {
        inv->numP[x]=0;
        if (x==0)
        {
            strcpy(inv->pots[x].name, "Minor Health Potion");
            inv->pots[x].potHealth=10;
        }
        else if (x==1)
        {
            strcpy(inv->pots[x].name, "Lesser Health Potion");
            inv->pots[x].potHealth=15;
        }
        else if (x==2)
        {
            strcpy(inv->pots[x].name, "Greater Health Potion");
            inv->pots[x].potHealth=20;
        }
        else if (x==3)
        {
            strcpy(inv->pots[x].name, "Major Health Potion");
            inv->pots[x].potHealth=40;
        }
        else if (x==4)
        {
            strcpy(inv->pots[x].name, "Minor Potion of Strength");
            inv->pots[x].potStrModifier=5;
            inv->pots[x].potDuration=20;
        }
        else if (x==5)
        {
            strcpy(inv->pots[x].name, "Lesser Potion of Strength");
            inv->pots[x].potStrModifier=10;
            inv->pots[x].potDuration=40;
        }
        else if (x==6)
        {
            strcpy(inv->pots[x].name, "Potion of Strength");
            inv->pots[x].potStrModifier=15;
            inv->pots[x].potDuration=60;
        }
        else if (x==7)
        {
            strcpy(inv->pots[x].name, "Greater Potion of Strength");
            inv->pots[x].potStrModifier=25;
            inv->pots[x].potDuration=80;
        }
    }
    for (x=0 ; x<8 ;x++)
    {
        inv->numM[x]=0;
        if (x==0)
        {
            strcpy(inv->mags[x].name, "Minor Health Enchant");
            inv->mags[x].magHpModifier=5;
        }
        else if (x==1)
        {
            strcpy(inv->mags[x].name, "Lesser Health Enchant");
            inv->mags[x].magHpModifier=10;
        }
        else if (x==2)
        {
            strcpy(inv->mags[x].name, "Greater Health Enchant");
            inv->mags[x].magHpModifier=16;
        }
        else if (x==3)
        {
            strcpy(inv->mags[x].name, "Major Health Enchant");
            inv->mags[x].magHpModifier=22;
        }
        else if (x==4)
        {
            strcpy(inv->mags[x].name, "Minor Strength Enchant");
            inv->mags[x].magStrModifier=2;
        }
        else if (x==5)
        {
            strcpy(inv->mags[x].name, "Lesser Strength Enchant");
            inv->mags[x].magStrModifier=4;
        }
        else if (x==6)
        {
            strcpy(inv->mags[x].name, "Strength Enchant");
            inv->mags[x].magStrModifier=7;
        }
        else if (x==7)
        {
            strcpy(inv->mags[x].name, "Greater Strength Enchant");
            inv->mags[x].magStrModifier=10;
        }
    }
    z=0;
    for (x=0 ; x<5 ;x++)
    {
        for (y=0 ; y<9 ;y++)
        {
            if (x==0)
                strcpy(inv->weps[z].wepType,"Iron ");
            else if (x==1)
                strcpy(inv->weps[z].wepType,"Steel ");
            else if (x==2)
                strcpy(inv->weps[z].wepType,"Silver ");
            else if (x==3)
                strcpy(inv->weps[z].wepType,"Orcish ");
            else if (x==4)
                strcpy(inv->weps[z].wepType,"Elvish ");
            wepMult=x+1;
            if (y==0)
            {
                strcpy(inv->weps[z].name, "Dagger");
                inv->weps[z].wepStrModifier = 1*wepMult;
            }
            else if (y==1)
            {
                strcpy(inv->weps[z].name, "Short Sword");
                inv->weps[z].wepStrModifier = 2*wepMult;
            }
            else if (y==2)
            {
                strcpy(inv->weps[z].name, "Long Sword");
                inv->weps[z].wepStrModifier = 4*wepMult;
            }
            else if (y==3)
            {
                strcpy(inv->weps[z].name, "Claymore");
                inv->weps[z].wepStrModifier = 5*wepMult;
            }
            else if (y==4)
            {
                strcpy(inv->weps[z].name, "War Axe");
                inv->weps[z].wepStrModifier = 3*wepMult;
            }
            else if (y==5)
            {
                strcpy(inv->weps[z].name, "Battle Axe");
                inv->weps[z].wepStrModifier = 5*wepMult;
            }
            else if (y==6)
            {
                strcpy(inv->weps[z].name, "Mace");
                inv->weps[z].wepStrModifier = 3*wepMult;
            }
            else if (y==7)
            {
                strcpy(inv->weps[z].name, "War Hammer");
                inv->weps[z].wepStrModifier = 5*wepMult;
            }
            else if (y==8)
            {
                strcpy(inv->weps[z].name, "Spear");
                inv->weps[z].wepStrModifier = 4*wepMult;
            }
            inv->numW[z]=0;
            z++;
        }
    }
}
