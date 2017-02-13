/*************************gameplay.c****************************
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
#include <math.h>

void playGame (int grid[50][100],monsters* monster, playerSt* hero, int* tMon)
{
    char input = ' ';
    int hX=0;
    int hY=0;
    int quitSure=0;
    inventory* inv = malloc(sizeof(inventory));
    initInv(inv);
    init_pair (1, COLOR_WHITE,COLOR_BLACK);
    init_pair (2, COLOR_BLACK,COLOR_WHITE);
    init_pair (3, COLOR_BLACK,COLOR_GREEN);
    init_pair (4, COLOR_BLACK,COLOR_YELLOW);
    init_pair (5, COLOR_BLACK,COLOR_RED);
    while (quitSure == 0)
    {
        attron (COLOR_PAIR(1));
        hX = hero->locX;
        hY = hero->locY;
        if (hero->hp <=0)//Death
            break;
        if (hero->xp >= hero->xpTotal)//Level Up
        {
            hero->level=hero->level+1;
            hero->xp=0;
            hero->xpTotal=15+10*hero->level;
            hero->totalHp=hero->totalHp+5;
            hero->hp=hero->hp+5;
            hero->str=hero->str+2;
        }
        if (hero->potDur > 0)
        {
            hero->potDur--;
        }
        else
        {
            hero->potStr=0;
        }
        updateStats(hero);
        drawHero(hY, hX);
        input = getch();
        mvprintw (51,10,"                                                  ");
        refresh();
        if (input == 'w' || input == 'W')
        {
            playerMove (hY-1, hX, hY,hX,hero,grid,inv,monster);
        }
        else if (input == 'a' || input == 'A')
        {
            playerMove (hY, hX-1, hY,hX,hero,grid,inv,monster);
        }
        else if (input == 's' || input == 'S')
        {
            playerMove (hY+1, hX, hY,hX,hero,grid,inv,monster);
        }
        else if (input == 'd' || input == 'D')
        {
            playerMove (hY, hX+1, hY,hX,hero,grid,inv,monster);
        }
        else if (input == 'i' || input == 'I')
        {
            openInv(inv,grid,hero);
        }
        else if (input == 'z')
            hero->hp=hero->hp-1;
        else if (input == 'x')
            hero->xp=hero->xp+2;
        else if (input == 'q' || input == 'Q')
        {
            clearScreen();
            mvprintw (20,20,"Are you sure you want to quit? (y/n): ");
            input = getch();
            if (input == 'y' || input == 'Y')
                quitSure =1;
        }
        monMove (monster, tMon, grid,hero);
        quickDraw(grid);
    }
    clearScreen();
    dumpInv(inv);
    getch();
}

void monMove (monsters* monster, int* tMon, int grid[50][100], playerSt* hero)
{
    int x;
    int mY=0;
    int mX=0;
    int tempCode;
    for (x=0; x< *tMon; x++)
    {
        mY=monster[x].locY;
        mX=monster[x].locX;
        tempCode = grid[mY][mX];
        if (monster[x].type == 'B')
        {
            if (monster[x].lastMove == 0)
            {
               mY++;
               monster[x].lastMove =1;
            }
            else if (monster[x].lastMove==1)
            {
               mX--;
               monster[x].lastMove =2;
            }
            else if (monster[x].lastMove==2)
            {
               mY--;
               monster[x].lastMove =3;
            }
            else if (monster[x].lastMove==3)
            {
               mX++;
               monster[x].lastMove =0;
            }
            if (grid[mY][mX]==0  || grid[mY][mX]==3  || grid[mY][mX]==4  || grid[mY][mX]==5)
            {
                if (hero->locY != mY || hero->locX != mX)
                {
                    grid[monster[x].locY][monster[x].locX]=monster[x].tile;
                    monster[x].tile = grid[mY][mX];
                    monster[x].locX=mX;
                    monster[x].locY=mY;
                    grid[mY][mX]=tempCode;
                }
            }
            else
            {
                if (monster[x].lastMove == 0)
                   monster[x].lastMove =1;
                else if (monster[x].lastMove==1)
                   monster[x].lastMove =2;
                else if (monster[x].lastMove==2)
                   monster[x].lastMove =3;
                else if (monster[x].lastMove==3)
                   monster[x].lastMove =0;
            }
        }
        else if (monster[x].type == 'R')
        {
            monster[x].lastMove = rand() % 4;
            if (monster[x].lastMove == 0)
            {
               mY++;
               monster[x].lastMove =1;
            }
            else if (monster[x].lastMove==1)
            {
               mX--;
               monster[x].lastMove =2;
            }
            else if (monster[x].lastMove==2)
            {
               mY--;
               monster[x].lastMove =3;
            }
            else if (monster[x].lastMove==3)
            {
               mX++;
               monster[x].lastMove =0;
            }
            if (grid[mY][mX]==0  || grid[mY][mX]==3  || grid[mY][mX]==4  || grid[mY][mX]==5)
            {
                if (hero->locY != mY || hero->locX != mX)
                {
                    grid[monster[x].locY][monster[x].locX]=monster[x].tile;
                    monster[x].tile = grid[mY][mX];
                    grid[mY][mX]=tempCode;
                    monster[x].locX=mX;
                    monster[x].locY=mY;
                }
            }
        }
        else if (monster[x].type == 'G')
        {
            if (monster[x].lastMove == 0)
            {
               mY++;
            }
            else if (monster[x].lastMove==1)
            {
               mY--;
            }
            if (grid[mY][mX]==0  || grid[mY][mX]==3  || grid[mY][mX]==4  || grid[mY][mX]==5)
            {
                if (hero->locY != mY || hero->locX != mX)
                {
                    grid[monster[x].locY][monster[x].locX]=monster[x].tile;
                    monster[x].tile = grid[mY][mX];
                    grid[mY][mX]=tempCode;
                    monster[x].locX=mX;
                    monster[x].locY=mY;
                }
            }
            else
            {
                if (monster[x].lastMove == 0)
                    monster[x].lastMove =1;
                else
                    monster[x].lastMove =0;
            }
        }
        else if (monster[x].type == 'O')
        {
            if (monster[x].lastMove == 0)
            {
               mX++;
            }
            else if (monster[x].lastMove==1)
            {
               mX--;
            }
            if (grid[mY][mX]==0  || grid[mY][mX]==3  || grid[mY][mX]==4  || grid[mY][mX]==5)
            {
                if (hero->locY != mY || hero->locX != mX)
                {
                    grid[monster[x].locY][monster[x].locX]=monster[x].tile;
                    monster[x].tile = grid[mY][mX];
                    grid[mY][mX]=tempCode;
                    monster[x].locX=mX;
                    monster[x].locY=mY;
                }
            }
            else
            {
                if (monster[x].lastMove == 0)
                    monster[x].lastMove =1;
                else
                    monster[x].lastMove =0;
            }
        }
        else if (monster[x].type == 'E')
        {
            if (monster[x].lastMove == 0)
            {
               mX++;
            }
            else if (monster[x].lastMove==1)
            {
               mY--;
            }
            else if (monster[x].lastMove==2)
            {
               mX--;
            }
            else if (monster[x].lastMove==1)
            {
               mY++;
            }
            if (grid[mY][mX]==0  || grid[mY][mX]==3  || grid[mY][mX]==4  || grid[mY][mX]==5)
            {
                if (hero->locY != mY || hero->locX != mX)
                {
                    grid[monster[x].locY][monster[x].locX]=monster[x].tile;
                    monster[x].tile = grid[mY][mX];
                    grid[mY][mX]=tempCode;
                    monster[x].locX=mX;
                    monster[x].locY=mY;
                }
            }
            else
            {
                if (monster[x].lastMove == 0)
                    monster[x].lastMove =1;
                else if (monster[x].lastMove == 1)
                    monster[x].lastMove =2;
                else if (monster[x].lastMove == 2)
                    monster[x].lastMove =3;
                else
                    monster[x].lastMove =0;
            }
        }
    }
}


void updateStats (playerSt* hero)
{
    int x;
    int y;
    double hpPct;
    double hp;
    double hpT;
    attron(COLOR_PAIR(1));
    for (x=0;x<100;x++)
    {
        mvaddch(54,x,' ');
        mvaddch(55,x,' ');
        mvaddch(56,x,' ');
    }
    hero->dam = hero->str + hero->wepStr + hero->potStr;

    hp = hero->hp;
    hpT = hero->totalHp;
    hpPct = (hp/hpT)*100;

    mvprintw(55,15,"Health: %d/%d",hero->hp,hero->totalHp);
    mvprintw(54,15,"Level: %d",hero->level);
    mvprintw(55,40,"Str: %d",hero->str);
    mvprintw(56,40,"Acc: %d",hero->acc);
    mvprintw(54,50,"Wep: %s",hero->equippedWep);
    mvprintw(55,50,"Dam: %d",hero->dam);
    mvprintw(56,50,"Dur: %d",hero->potDur);
    mvprintw(55,60,"Experience: %d/%d",hero->xp,hero->xpTotal);
    mvprintw(56,60,"Floor: %d",hero->floor+1);

    if (hpPct > 70)
        attron(COLOR_PAIR(3));
    else if (hpPct > 40)
        attron(COLOR_PAIR(4));
    else
        attron(COLOR_PAIR(5));
    y=15;
    for (x=0; x<hpPct; x=x+5)
    {
        mvaddch(56,y,' ');
        y++;
    }
    attron(COLOR_PAIR(1));
}

void playerMove (int nY, int nX, int hY, int hX,playerSt* hero,int grid[50][100],inventory* inv,monsters*mon)
{
    int iVal=0;
    int wType=0;
    int wMat=0;
    int monA;
    int mID;
    int x;
    int y;
    if (grid[nY][nX]==0 || grid[nY][nX]==4 || grid[nY][nX]==3 || grid[nY][nX]==5)
    {
        drawLast(hY,hX,grid[hY][hX]);
        drawHero(nY,nX);
        hero->locX = nX;
        hero->locY = nY;
    }
    else if (grid[nY][nX] >=  100000 && grid[nY][nX] < 200000)
    {
        inv->gold=inv->gold+grid[nY][nX]-100000;
        mvprintw (51,10,"You picked up %d gold coins!",grid[nY][nX]-100000);
        grid[nY][nX]=0;
        drawLast(hY,hX,grid[hY][hX]);
        drawHero(nY,nX);
        hero->locX = nX;
        hero->locY = nY;
    }
    else if (grid[nY][nX] >= 200000 && grid[nY][nX] < 300000)
    {
        grid[nY][nX]=grid[nY][nX]-200000;
        if (grid[nY][nX] >=10000 && grid[nY][nX] < 20000)
        {
            grid[nY][nX]=grid[nY][nX]-10000;
            if (grid[nY][nX] == 520)
                iVal=4;
            else if (grid[nY][nX] == 1040)
                iVal=5;
            else if (grid[nY][nX] == 1560)
                iVal=6;
            else if (grid[nY][nX] == 2580)
                iVal=7;
        }
        else
        {
            grid[nY][nX]=grid[nY][nX]-10000;
            if (grid[nY][nX] == 10)
                iVal=0;
            else if (grid[nY][nX] == 15)
                iVal=1;
            else if (grid[nY][nX] == 20)
                iVal=2;
            else if (grid[nY][nX] == 40)
                iVal=3;
        }
        grid[nY][nX]=0;
        inv->numP[iVal]++;
        mvprintw (51,10,"You picked up a %s",inv->pots[iVal].name);
        drawLast(hY,hX,grid[hY][hX]);
        drawHero(nY,nX);
        hero->locX = nX;
        hero->locY = nY;
    }
    else if (grid[nY][nX] >= 300000 && grid[nY][nX] < 400000)
    {
        grid[nY][nX]=grid[nY][nX]-300000;
        if (grid[nY][nX] >=100 && grid[nY][nX] < 200)
        {
            grid[nY][nX]=grid[nY][nX]-100;
            if (grid[nY][nX] == 2)
                iVal=4;
            else if (grid[nY][nX] == 4)
                iVal=5;
            else if (grid[nY][nX] == 7)
                iVal=6;
            else if (grid[nY][nX] == 10)
                iVal=7;
        }
        else
        {
            grid[nY][nX]=grid[nY][nX]-200;
            if (grid[nY][nX] == 5)
                iVal=0;
            else if (grid[nY][nX] == 10)
                iVal=1;
            else if (grid[nY][nX] == 16)
                iVal=2;
            else if (grid[nY][nX] == 22)
                iVal=3;
        }
        grid[nY][nX]=0;
        inv->numM[iVal]++;
        mvprintw (51,10,"You picked up a %s",inv->mags[iVal].name);
        drawLast(hY,hX,grid[hY][hX]);
        drawHero(nY,nX);
        hero->locX = nX;
        hero->locY = nY;
    }
    else if (grid[nY][nX] >= 400000 && grid[nY][nX] < 500000)
    {
        iVal=0;
        grid[nY][nX]=grid[nY][nX]-400000;
        if (grid[nY][nX] >=10000 && grid[nY][nX] < 20000)
        {
            grid[nY][nX] = grid[nY][nX]-10000;
            wType=0;
        }
        else if (grid[nY][nX] >=20000 && grid[nY][nX] < 30000)
        {
            grid[nY][nX] = grid[nY][nX]-20000;
            wType=1;
        }
        else if (grid[nY][nX] >=30000 && grid[nY][nX] < 40000)
        {
            grid[nY][nX] = grid[nY][nX]-30000;
            wType=2;
        }
        else if (grid[nY][nX] >=40000 && grid[nY][nX] < 50000)
        {
            grid[nY][nX] = grid[nY][nX]-40000;
            wType=3;
        }
        else if (grid[nY][nX] >=50000 && grid[nY][nX] < 60000)
        {
            grid[nY][nX] = grid[nY][nX]-50000;
            wType=4;
        }
        else if (grid[nY][nX] >=60000 && grid[nY][nX] < 70000)
        {
            grid[nY][nX] = grid[nY][nX]-60000;
            wType=5;
        }
        else if (grid[nY][nX] >=70000 && grid[nY][nX] < 80000)
        {
            grid[nY][nX] = grid[nY][nX]-70000;
            wType=6;
        }
        else if (grid[nY][nX] >=80000 && grid[nY][nX] < 90000)
        {
            grid[nY][nX] = grid[nY][nX]-80000;
            wType=7;
        }
        else if (grid[nY][nX] >=90000 && grid[nY][nX] < 100000)
        {
            grid[nY][nX] = grid[nY][nX]-90000;
            wType=8;
        }
        if (grid[nY][nX] >=1000 && grid[nY][nX] < 2000)
        {
            grid[nY][nX] = grid[nY][nX]-1000;
            wMat=0;
        }
        else if (grid[nY][nX] >=2000 && grid[nY][nX] < 3000)
        {
            grid[nY][nX] = grid[nY][nX]-2000;
            wMat=1;
        }
        else if (grid[nY][nX] >=3000 && grid[nY][nX] < 4000)
        {
            grid[nY][nX] = grid[nY][nX]-3000;
            wMat=2;
        }
        else if (grid[nY][nX] >=4000 && grid[nY][nX] < 5000)
        {
            grid[nY][nX] = grid[nY][nX]-4000;
            wMat=3;
        }
        else if (grid[nY][nX] >=5000 && grid[nY][nX] < 6000)
        {
            grid[nY][nX] = grid[nY][nX]-5000;
            wMat=4;
        }
        for (x=0;x<wMat+1;x++)
        {
            for (y=0;y<9;y++)
            {
                iVal++;
                if (x==wMat && y==wType)
                {
                    x=100;
                    y=100;
                }
            }
        }
        iVal--;
        grid[nY][nX]=0;
        inv->numW[iVal]=inv->numW[iVal]+1;
        mvprintw (51,10,"You picked up a %s%s",inv->weps[iVal].wepType,inv->weps[iVal].name);
        drawLast(hY,hX,grid[hY][hX]);
        drawHero(nY,nX);
        hero->locX = nX;
        hero->locY = nY;
    }
    else if (grid[nY][nX] >= 500000 && grid[nY][nX] < 600000)
    {
        monA = grid[nY][nX]-500000;
        if (monA >=10000 && monA <20000)
        {
            mID = monA - 10000;
        }
        else if (monA >=20000 && monA <30000)
        {
            mID = monA - 20000;
        }
        else if (monA >=30000 && monA <40000)
        {
            mID = monA - 30000;
        }
        else if (monA >=40000 && monA <50000)
        {
            mID = monA - 40000;
        }
        else if (monA >=50000 && monA <60000)
        {
            mID = monA - 50000;
        }
        else if (monA >=60000 && monA <70000)
        {
            mID = monA - 60000;
        }
        mon[mID].hp = mon[mID].hp - hero->dam;
        if (mon[mID].hp <= 0)//Mon Dies
        {
            grid[nY][nX]=0;
            mvprintw (51,15,"You and %s exchange blows!",mon[mID].name);
            combatPause();
            mvprintw (51,15,"You have slain %s!",mon[mID].name);
            hero->xp = hero->xp+mon[mID].xpBoost;
            grid[nY][nX]=mon[mID].tile;
            drawLast(nY,nX,grid[nY][nX]);
            hero->hp = hero->hp-mon[mID].damage;
        }
        else
        {
            hero->hp = hero->hp-mon[mID].damage;
            mvprintw (51,15,"You and %s exchange blows!",mon[mID].name);
        }
        updateStats(hero);
        combatPause();
    }
}


void combatPause()
{
    mvprintw (52,15,"<press key to continue>");
    getch();
    mvprintw (51,15,"                                                              ");
    mvprintw (52,15,"                           ");
}

void drawHero(int y,int x)
{
    mvaddch (y,x,'@');
}

void drawLast(int y, int x, int last)
{
    if (last == 0)
        mvaddch (y,x,'.');
    else if (last==3)
        mvaddch(y,x,'+');
    else if (last==4)
        mvaddch(y,x,'#');
    else if (last==5)
        mvaddch(y,x,'%');
}
