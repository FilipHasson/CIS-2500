/*************************inventory.c****************************
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
#include "preGame.h"
#include "gameplay.h"
#include "drawGame.h"
#include "inventory.h"

void openInv(inventory* inv, int grid[50][100],playerSt* hero)
{
    int x;
    int menuY=0;
    char input = ' ';
    clearScreen();
    init_pair (1, COLOR_WHITE,COLOR_BLACK);
    init_pair (2, COLOR_BLACK,COLOR_WHITE);

    attron (COLOR_PAIR(2));
    mvprintw (6,10,"Gold");
    attron (COLOR_PAIR(1));
    mvprintw (8,10,"Weapons");
    mvprintw (10,10,"Potions");
    mvprintw (12,10,"Magical");
    mvprintw (4,21, "E: Select | R: Back");
    for (x=6; x<13; x++)
        mvaddch (x,20,'|');
    while (input != 'r' && input != 'R')
    {
        refresh();
        attron (COLOR_PAIR(1));
        input=getch();
        if (input == 'w' || input == 'W')
        {
            if (menuY > 0)
                menuY--;
            else
                menuY=3;
        }
        else if (input == 's' || input == 'S')
        {
            if (menuY < 3)
                menuY++;
            else
                menuY=0;
        }
        else if (input == 'e' || input == 'E')
        {
            if (menuY == 0)
            {
                if (inv->gold > 0)
                {
                    attron (COLOR_PAIR(2));
                    mvprintw (6,30,"Gold:\t%d",inv->gold);
                }
                else
                    mvprintw (6,30,"empty");
                while (input != 'r' && input != 'R')
                    input=getch();
                input = ' ';
                clearInvMenu();
            }
            else if (menuY == 1)
                drawWepInv (inv,hero);
            else if (menuY == 2)
                drawPotInv (inv,hero);
            else if (menuY ==3 )
                drawMagInv(inv,hero);
            refresh();
        }
        attron (COLOR_PAIR(1));
        mvprintw (6,10,"Gold");
        mvprintw (8,10,"Weapons");
        mvprintw (10,10,"Potions");
        mvprintw (12,10,"Magical");
        attron (COLOR_PAIR(2));
        if (menuY == 0)
            mvprintw (6,10,"Gold");
        else if (menuY == 1)
            mvprintw (8,10,"Weapons");
        else if (menuY == 2)
            mvprintw (10,10,"Potions");
        else if (menuY == 3)
            mvprintw (12,10,"Magical");
    }
    attron (COLOR_PAIR(1));
    clearScreen();
    quickDraw(grid);
}

void dumpInv (inventory*inv)
{
    int x;
    int wCnt=0;
    int mCnt=0;
    int pCnt=0;
    mvprintw (3,20,"Thank you for playing! This is what you collected:");
    mvprintw (5,10, "Weapons:");
    mvprintw (5,40, "Potions:");
    mvprintw (5,70, "Magic:");
    mvprintw (5,90, "Gold:");
    mvprintw (6,91, "%d",inv->gold);
    for (x=0;x<8;x++)
    {
        if (inv->numM[x]>0)
        {
            mvprintw (7+mCnt,71,"%s",inv->mags[x].name);
            mCnt++;
        }
    }
    for (x=0;x<8;x++)
    {
        if (inv->numP[x]>0)
        {
            mvprintw (7+pCnt,41,"%s",inv->pots[x].name);
            pCnt++;
        }
    }
    for (x=0;x<45;x++)
    {
        if (inv->numW[x]>0)
        {
            mvprintw (7+wCnt,11,"%s",inv->weps[x].name);
            wCnt++;
        }
    }
}


void drawMagInv (inventory*inv,playerSt* hero)
{
    int x;
    int selectedMag=0;
    int magsY=6;
    int lineNum=6;
    int maxYCol1=6;
    int diffItems=0;
    char input = ' ';
    attron(COLOR_PAIR(1));

    for (x=0;x<8;x++)
    {
        if (inv->numM[x]>0)
            diffItems++;
    }

    maxYCol1 = 6+(diffItems*2)-2;

    while (input != 'r' && input !='R')
    {
        if (diffItems ==0)
        {
            mvprintw (6,30,"empty");
        }
        lineNum=6;
        for (x=0;x<8;x++)
        {
            if (inv->numM[x] > 0)
            {
                if (magsY == lineNum)
                {
                    attron(COLOR_PAIR(2));
                    selectedMag=x;
                }
                else
                    attron(COLOR_PAIR(1));

                if (strlen(inv->mags[x].name) < 22)
                {
                    if (x < 4)
                    {
                        mvprintw (lineNum,30,"%d |%s:\t\t| Hp Boost: %d",inv->numM[x],inv->mags[x].name,inv->mags[x].magHpModifier);
                    }
                    else
                        mvprintw (lineNum,30,"%d |%s:\t\t| Str Boost: %d",inv->numM[x],inv->mags[x].name,inv->mags[x].magStrModifier);
                }
                else
                {
                    if (x < 4)
                        mvprintw (lineNum,30,"%d |%s:\t| Hp Healed: %d",inv->numM[x],inv->mags[x].name,inv->mags[x].magHpModifier);
                    else
                        mvprintw (lineNum,30,"%d |%s:\t| Str Boost: %d",inv->numM[x],inv->mags[x].name,inv->mags[x].magStrModifier);
                }
                refresh();
                lineNum = lineNum+2;
            }
        }
        input = getch();
        if (input == 'w' || input == 'W')
        {
            if (magsY > 6)
                magsY = magsY - 2;
            else
                magsY = maxYCol1;

        }
        else if (input == 's' || input == 'S')
        {
            if (magsY < maxYCol1)
                magsY = magsY + 2;
            else
                magsY = 6;
        }
        else if (input == 'e'||input == 'E')
        {
            if (selectedMag <4)
            {
                hero->hp= hero->hp + inv->mags[selectedMag].magHpModifier;
                hero->totalHp=hero->totalHp + inv->mags[selectedMag].magHpModifier;
                inv->numM[selectedMag]--;
            }
            else
            {
                hero->str= hero->str + inv->mags[selectedMag].magStrModifier;
                inv->numM[selectedMag]--;
            }
            if (inv->numM[selectedMag]==0)
            {
                maxYCol1=maxYCol1-2;
                if (magsY > 6)
                    magsY=magsY-2;
                diffItems--;
            }
            updateStats(hero);
            clearInvMenu();
        }
    }
    clearInvMenu ();
}

void drawPotInv (inventory*inv,playerSt* hero)
{
    int x;
    int selectedPot=0;
    int potsY=6;
    int lineNum=6;
    int maxYCol1=6;
    int diffItems=0;
    char input = ' ';
    attron(COLOR_PAIR(1));

    for (x=0;x<8;x++)
    {
        if (inv->numP[x]>0)
            diffItems++;
    }

    maxYCol1 = 6+(diffItems*2)-2;

    while (input != 'r' && input !='R')
    {
        if (diffItems ==0)
        {
            mvprintw (6,30,"empty");
        }
        lineNum=6;
        for (x=0;x<8;x++)
        {
            if (inv->numP[x] > 0)
            {
                if (potsY == lineNum)
                {
                    attron(COLOR_PAIR(2));
                    selectedPot=x;
                }
                else
                    attron(COLOR_PAIR(1));

                if (strlen(inv->pots[x].name) < 22)
                {
                    if (x < 4)
                        mvprintw (lineNum,30,"%d |%s:\t\t| Hp Healed: %d",inv->numP[x],inv->pots[x].name,inv->pots[x].potHealth);
                    else
                        mvprintw (lineNum,30,"%d |%s:\t\t| Str Boost: %d  Duration: %d",inv->numP[x],inv->pots[x].name,inv->pots[x].potStrModifier,inv->pots[x].potDuration);
                }
                else
                {
                    if (x < 4)
                        mvprintw (lineNum,30,"%d |%s:\t| Hp Healed: %d",inv->numP[x],inv->pots[x].name,inv->pots[x].potHealth);
                    else
                        mvprintw (lineNum,30,"%d |%s:\t| Str Boost: %d  Duration: %d",inv->numP[x],inv->pots[x].name,inv->pots[x].potStrModifier,inv->pots[x].potDuration);
                }
                refresh();
                lineNum = lineNum+2;
            }
        }
        input = getch();
        if (input == 'w' || input == 'W')
        {
            if (potsY > 6)
                potsY = potsY - 2;
            else
                potsY = maxYCol1;

        }
        else if (input == 's' || input == 'S')
        {
            if (potsY < maxYCol1)
                potsY = potsY + 2;
            else
                potsY = 6;
        }
        else if (input == 'e'||input == 'E')
        {
            if (selectedPot <4)
            {
                hero->hp= hero->hp + inv->pots[selectedPot].potHealth;
                if (hero->hp > hero->totalHp)
                    hero->hp = hero->totalHp;
                inv->numP[selectedPot]--;
            }
            else
            {
                hero->potStr= hero->potStr + inv->pots[selectedPot].potStrModifier;
                hero->potDur= hero->potDur + inv->pots[selectedPot].potDuration;
                inv->numP[selectedPot]--;
            }
            if (inv->numP[selectedPot]==0)
            {
                maxYCol1=maxYCol1-2;
                if (potsY > 6)
                    potsY=potsY-2;
                diffItems--;
            }
            updateStats(hero);
            clearInvMenu();
        }
    }
    clearInvMenu ();
}

void drawWepInv (inventory*inv,playerSt* hero)
{
    int x;
    int selectedWep=0;
    int wepsY=6;
    int wepsX=30;
    int lineNum=6;
    int colNum=30;
    int maxYCol1=6;
    int maxYCol2=6;
    int diffItems=0;
    char input = ' ';
    attron(COLOR_PAIR(1));
    for (x=0;x<45;x++)
    {
        if (inv->numW[x]>0)
            diffItems++;
    }
    if (diffItems < 22)
       maxYCol1 = 6+(diffItems*2)-2;
    else if (diffItems == 22)
       maxYCol1 = diffItems*2+6;
    else
    {
       maxYCol1 = 50;
       maxYCol2 = 6+(diffItems-22)*2-4;
    }
    while (input != 'r' && input !='R')
    {
        if (diffItems ==0)
        {
            mvprintw (6,30,"empty");
        }
        lineNum=6;
        colNum=30;
        for (x=0;x<45;x++)
        {
            if (inv->numW[x] > 0)
            {
                if (wepsY == lineNum && wepsX == colNum)
                {
                    attron(COLOR_PAIR(2));
                    selectedWep=x;
                }
                else
                    attron(COLOR_PAIR(1));

                if (strlen(inv->weps[x].wepType)+strlen(inv->weps[x].name) < 14)
                    mvprintw (lineNum,colNum,"%d |%s%s:\t\t| Damage: %d",inv->numW[x],inv->weps[x].wepType,inv->weps[x].name,inv->weps[x].wepStrModifier);
                else
                    mvprintw (lineNum,colNum,"%d |%s%s:\t| Damage: %d",inv->numW[x],inv->weps[x].wepType,inv->weps[x].name,inv->weps[x].wepStrModifier);
                refresh();
                lineNum = lineNum+2;
                if (lineNum > 50)
                {
                    lineNum =6;
                    if (colNum==30)
                        colNum =75;
                    else
                        colNum=110;
                }
            }
        }
        input = getch();
        if (input == 'w' || input == 'W')
        {
            if (wepsY > 6)
                wepsY = wepsY - 2;
            else
            {
                if (wepsX == 30)
                   wepsY = maxYCol1;
                else
                   wepsY = maxYCol2;
            }
        }
        else if (input == 's' || input == 'S')
        {
            if (wepsX == 30)
            {
                if (wepsY < maxYCol1)
                    wepsY = wepsY + 2;
                else
                    wepsY = 6;
            }
            else
            {
                if (wepsY < maxYCol2)
                    wepsY = wepsY + 2;
                else
                    wepsY = 6;
            }
        }
        else if (input == 'd' || input == 'D')
        {
            if (diffItems > 22)
            {
                if (wepsX == 30)
                {
                    wepsX =75;
                    if (wepsY> maxYCol2)
                        wepsY = maxYCol2;
                }
                else
                {
                    wepsX =30;
                }
            }
        }
        else if (input == 'a' || input == 'A')
        {
            if (diffItems > 22)
            {
                if (wepsX == 30)
                {
                    wepsX =75;
                    if (wepsY> maxYCol2)
                        wepsY = maxYCol2;
                }
                else
                {
                    wepsX =30;
                }
            }
        }
        else if (input == 'e'||input == 'E')
        {
            hero->wepStr= inv->weps[selectedWep].wepStrModifier;
            strcpy (hero->equippedWep,inv->weps[selectedWep].wepType);
            strcat (hero->equippedWep,inv->weps[selectedWep].name);
            updateStats(hero);
            clearInvMenu();
        }
    }
    clearInvMenu ();
}

void clearInvMenu ()
{
    int x;
    int y;
    attron(COLOR_PAIR(1));
    for (x=30;x<141;x++)
    {
        for (y=6;y<51;y++)
        mvaddch (y,x,' ');
    }
}
