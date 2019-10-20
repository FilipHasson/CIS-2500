/*************************drawGame.c****************************
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
#include "gameplay.h"

void initBoard(room rooms[6], int grid[50][100], monsters* mon, int devFlags[5], int* tMon, playerSt* hero)
{
    topLeftCorner* tl;
    int mod=2;
    int mod2=2;
    int* monPlaced=malloc(sizeof(int));
    *monPlaced=0;
    tl=malloc(sizeof(topLeftCorner)*6);

    char* args[1] = {""};
    execvp("reset",args);

    initscr();
    start_color();
    attron (COLOR_PAIR(0));
    cbreak();
    noecho();
    curs_set(0);

    initGrid (grid);
    drawZoneLines(devFlags[1]);

    mod = randMovX(rooms[0].width);
    mod2 = randMovY(rooms[0].length);
    tl[0].x=mod;
    tl[0].y=mod2;
    rooms[0]=drawRoom(rooms[0], tl[0].x, tl[0].y, grid,mon,tMon,monPlaced);

    mod = randMovX(rooms[1].width);
    mod2 = randMovY(rooms[1].length);
    tl[1].x=mod+33;
    tl[1].y=mod2;
    rooms[1]=drawRoom(rooms[1], tl[1].x, tl[1].y, grid,mon,tMon,monPlaced);

    mod = randMovX(rooms[2].width);
    mod2 = randMovY(rooms[2].length);
    tl[2].x=mod+66;
    tl[2].y=mod2;
    rooms[2]=drawRoom(rooms[2], tl[2].x, tl[2].y, grid,mon,tMon,monPlaced);

    mod = randMovX(rooms[3].width);
    mod2 = randMovY(rooms[3].length);
    tl[3].x=mod;
    tl[3].y=mod2+25;
    rooms[3]=drawRoom(rooms[3], tl[3].x, tl[3].y, grid,mon,tMon,monPlaced);

    mod = randMovX(rooms[4].width);
    mod2 = randMovY(rooms[4].length);
    tl[4].x=mod+33;
    tl[4].y=mod2+25;
    rooms[4]=drawRoom(rooms[4], tl[4].x, tl[4].y, grid,mon,tMon,monPlaced);

    mod = randMovX(rooms[5].width);
    mod2 = randMovY(rooms[5].length);
    tl[5].x=mod+66;
    tl[5].y=mod2+25;
    rooms[5]=drawRoom(rooms[5], tl[5].x, tl[5].y, grid,mon,tMon,monPlaced);

    drawHalls (rooms, grid, tl,devFlags[3]);
    hero->locY=tl[0].y+hero->locY;
    hero->locX=tl[0].x+hero->locX;
    refresh();
}

void quickDraw (int grid[50][100])
{
    int x;
    int y;
    int monV;
    for (x=0;x<100;x++)
    {
        for (y=0;y<50;y++)
        {
            if (grid[y][x]==0)
            mvaddch(y,x,'.');
            else if (grid[y][x]==1)
            mvaddch(y,x,'-');
            else if (grid[y][x]==2)
            mvaddch(y,x,'|');
            else if (grid[y][x]==3)
            mvaddch(y,x,'+');
            else if (grid[y][x]==4)
            mvaddch(y,x,'#');
            else if (grid[y][x]==5)
            mvaddch(y,x,'%');
            else if (grid[y][x]==9)
            mvaddch(y,x,' ');
            else if (grid[y][x] >= 100000 && grid[y][x] < 200000)
            mvaddch(y,x,'*');
            else if (grid[y][x] >= 200000 && grid[y][x] < 300000)
            mvaddch(y,x,'!');
            else if (grid[y][x] >= 300000 && grid[y][x] < 400000)
            mvaddch(y,x,'$');
            else if (grid[y][x] >= 400000 && grid[y][x] < 500000)
            mvaddch(y,x,')');
            else if (grid[y][x] >= 500000 && grid[y][x] < 600000)
            {
                monV = grid[y][x]-500000;
                if (monV >=10000 && monV < 20000)
                    mvaddch(y,x,'S');
                else if (monV >=20000 && monV < 30000)
                    mvaddch(y,x,'B');
                else if (monV >=30000 && monV < 40000)
                    mvaddch(y,x,'R');
                else if (monV >=40000 && monV < 50000)
                    mvaddch(y,x,'G');
                else if (monV >=50000 && monV < 60000)
                    mvaddch(y,x,'O');
                else if (monV >=60000 && monV < 70000)
                    mvaddch(y,x,'E');
            }
        }
    }
}

void drawHalls (room rooms[6], int grid[50][100], topLeftCorner* tl, int flag)
{
    int x;
    int y;
    int z;
    int i;
    int spX;
    int epX;
    int spY;
    int epY;
    int lastX=1000;
    int lastY=1000;
    double sDist=100;
    double nDist;
    int xDist;
    int yDist;
    int pRm;
    int pNum;
    int totalD=0;
    for (x=0;x<6;x++)
        totalD = totalD + rooms[x].dCnt;
    for (x=0;x<6;x++)
    {
        for (y=0; y<rooms[x].dCnt;y++)
        {
            if (rooms[x].doors[y].paired==0)//Door Has No Partner
            {
                for (z=0;z<6;z++)
                {
                    if (x != z)
                    {
                        for (i=0;i<rooms[z].dCnt;i++)
                        {
                            if (rooms[z].doors[i].paired==0)
                            {
                                xDist=(rooms[x].doors[y].locX)-(rooms[z].doors[i].locX);
                                yDist=rooms[x].doors[y].locY-rooms[z].doors[i].locY;
                                nDist = sqrt((xDist*xDist)+(yDist*yDist));
                                if (nDist < sDist)
                                {
                                    sDist=nDist;
                                    pRm = z;
                                    pNum = i;
                                }
                            }
                        }
                    }
                }
                rooms[x].doors[y].paired=1;
                rooms[pRm].doors[pNum].paired=1;
                rooms[x].doors[y].pLocX=rooms[pRm].doors[pNum].locX;
                rooms[x].doors[y].pLocY=rooms[pRm].doors[pNum].locY;
                rooms[pRm].doors[pNum].pLocX=rooms[x].doors[y].locX;
                rooms[pRm].doors[pNum].pLocY=rooms[x].doors[y].locY;
                rooms[x].doors[y].pNum=pNum;
                rooms[x].doors[y].pRoom=pRm;
                rooms[pRm].doors[pNum].pNum=y;
                rooms[pRm].doors[pNum].pRoom=x;
                sDist=100;
            }
        }
    }
    for (y=0;y<50;y++)
    {
        for (x=0;x<100;x++)
        {
            if (grid[y][x]==3)
            {
                for (z=0;z<6;z++)
                {
                    for (i=0;i<rooms[z].dCnt;i++)
                    {
                        if (rooms[z].doors[i].locX == x && rooms[z].doors[i].locY == y)
                        {
                            if (rooms[z].doors[i].paired==1)
                            {
                                lastX=1000;
                                lastY=1000;
                                spX=x;
                                spY=y;
                                epX=rooms[z].doors[i].pLocX;
                                epY=rooms[z].doors[i].pLocY;
                                if (rooms[z].doors[y].wall=='N')
                                {
                                    spY--;
                                }
                                else if (rooms[z].doors[y].wall=='S')
                                {
                                    spY++;
                                }
                                else if (rooms[z].doors[y].wall=='E')
                                {
                                    spX++;
                                }
                                else if (rooms[z].doors[y].wall=='W')
                                {
                                    spX--;
                                }
                                while (spY != epY || spX != epX)
                                {
                                    if (spY > epY && spX > epX)
                                    {
                                        if ((grid[spY][spX-1]==9 || grid[spY][spX-1]==4) && spX-1 >=0 && spX-1 != lastX)
                                        {
                                            spX--;
                                            lastX=spX+1;
                                            lastY=1000;
                                        }
                                        else if ((grid[spY-1][spX]==9||grid[spY-1][spX]==4) && spY-1 >=0 && spY-1 !=lastY)
                                        {
                                            spY--;
                                            lastY=spY+1;
                                            lastX=1000;
                                        }
                                        else if ((grid[spY][spX+1]==9||grid[spY][spX+1]==4 )&& spX+1 <100 && spX+1 != lastX)
                                        {
                                            spX++;
                                            lastX=spX-1;
                                            lastY=1000;
                                        }
                                        else if ((grid[spY+1][spX]==9||grid[spY+1][spX]==4) && spY+1 <100 && spY+1 !=lastY)
                                        {
                                            spY++;
                                            lastY=spY-1;
                                            lastX=1000;
                                        }
                                    }
                                    else if (spY == epY && spX > epX)
                                    {
                                        if ((grid[spY][spX-1]==9||grid[spY][spX-1]==4) && spX-1 >=0 && spX-1 != lastX)
                                        {
                                            spX--;
                                            lastX=spX+1;
                                            lastY=1000;
                                        }
                                        else if ((grid[spY-1][spX]==9||grid[spY-1][spX]==4) && spY-1 >=0 && spY-1 !=lastY)
                                        {
                                            spY--;
                                            lastY=spY+1;
                                            lastX=1000;
                                        }
                                        else if ((grid[spY+1][spX]==9||grid[spY+1][spX]==4) && spY+1 <100 && spY+1 !=lastY)
                                        {
                                            spY++;
                                            lastY=spY-1;
                                            lastX=1000;
                                        }
                                        else if ((grid[spY][spX+1]==9||grid[spY][spX+1]==4) && spX+1 <100 && spX+1 != lastX)
                                        {
                                            spX++;
                                            lastX=spX-1;
                                            lastY=1000;
                                        }
                                    }
                                    else if (spY > epY && spX == epX)
                                    {
                                        if ((grid[spY-1][spX]==9||grid[spY-1][spX]==4) && spY-1 >=0 && spY-1 !=lastY)
                                        {
                                            spY--;
                                            lastY=spY+1;
                                            lastX=1000;
                                        }
                                        else if ((grid[spY][spX-1]==9||grid[spY][spX-1]==4) && spX-1 >=0 && spX-1 != lastX)
                                        {
                                            spX--;
                                            lastX=spX+1;
                                            lastY=1000;
                                        }
                                        else if ((grid[spY][spX+1]==9||grid[spY][spX+1]==4) && spX+1 <100 && spX+1 != lastX)
                                        {
                                            spX++;
                                            lastX=spX-1;
                                            lastY=1000;
                                        }
                                        else if ((grid[spY+1][spX]==9||grid[spY+1][spX]==4) && spY+1 <100 && spY+1 !=lastY)
                                        {
                                            spY++;
                                            lastY=spY-1;
                                            lastX=1000;
                                        }
                                    }
                                    else if (spY < epY && spX < epX)
                                    {
                                        if ((grid[spY][spX+1]==9||grid[spY][spX+1]==4) && spX+1 <100 && spX+1 != lastX)
                                        {
                                            spX++;
                                            lastX=spX-1;
                                            lastY=1000;
                                        }
                                        else if ((grid[spY+1][spX]==9||grid[spY+1][spX]==4) && spY+1 <100 && spY+1 !=lastY)
                                        {
                                            spY++;
                                            lastY=spY-1;
                                            lastX=1000;
                                        }
                                        else if ((grid[spY][spX-1]==9||grid[spY][spX-1]==4) && spX-1 >=0 && spX-1 != lastX)
                                        {
                                            spX--;
                                            lastX=spX+1;
                                            lastY=1000;
                                        }
                                        else if ((grid[spY-1][spX]==9||grid[spY-1][spX]==4) && spY-1 >=0 && spY-1 !=lastY)
                                        {
                                            spY--;
                                            lastY=spY+1;
                                            lastX=1000;
                                        }
                                    }
                                    else if (spY == epY && spX < epX)
                                    {

                                        if ((grid[spY][spX+1]==9||grid[spY][spX+1]==4) && spX+1 <100 && spX+1 != lastX)
                                        {
                                            spX++;
                                            lastX=spX-1;
                                            lastY=1000;
                                        }
                                        else if ((grid[spY+1][spX]==9||grid[spY+1][spX]==4) && spY+1 <100 && spY+1 !=lastY)
                                        {
                                            spY++;
                                            lastY=spY-1;
                                            lastX=1000;
                                        }
                                        else if ((grid[spY-1][spX]==9||grid[spY-1][spX]==4) && spY-1 >=0 && spY-1 !=lastY)
                                        {
                                            spY--;
                                            lastY=spY+1;
                                            lastX=1000;
                                        }
                                        else if ((grid[spY][spX-1]==9||grid[spY][spX-1]==4) && spX-1 >=0 && spX-1 != lastX)
                                        {
                                            spX--;
                                            lastX=spX+1;
                                            lastY=1000;
                                        }
                                    }
                                    else if (spY < epY && spX == epX)
                                    {
                                        if ((grid[spY+1][spX]==9||grid[spY+1][spX]==4) && spY+1 <100 && spY+1 !=lastY)
                                        {
                                            spY++;
                                            lastY=spY-1;
                                            lastX=1000;
                                        }
                                        else if ((grid[spY][spX-1]==9||grid[spY][spX-1]==4) && spX-1 >=0 && spX-1 != lastX)
                                        {
                                            spX--;
                                            lastX=spX+1;
                                            lastY=1000;
                                        }
                                        else if ((grid[spY][spX+1]==9||grid[spY][spX+1]==4) && spX+1 <100 && spX+1 != lastX)
                                        {
                                            spX++;
                                            lastX=spX-1;
                                            lastY=1000;
                                        }
                                        else if ((grid[spY-1][spX]==9||grid[spY-1][spX]==4) && spY-1 >=0 && spY-1 !=lastY)
                                        {
                                            spY--;
                                            lastY=spY+1;
                                            lastX=1000;
                                        }
                                    }
                                    else if (spY > epY && spX < epX)
                                    {
                                        if ((grid[spY-1][spX]==9||grid[spY-1][spX]==4) && spY-1 >=0 && spY-1 !=lastY)
                                        {
                                            spY--;
                                            lastY=spY+1;
                                            lastX=1000;
                                        }
                                        else if ((grid[spY][spX+1]==9||grid[spY][spX+1]==4) && spX+1 <100 && spX+1 != lastX)
                                        {
                                            spX++;
                                            lastX=spX-1;
                                            lastY=1000;
                                        }
                                        else if ((grid[spY+1][spX]==9||grid[spY+1][spX]==4) && spY+1 <100 && spY+1 !=lastY)
                                        {
                                            spY++;
                                            lastY=spY-1;
                                            lastX=1000;
                                        }
                                        else if ((grid[spY][spX-1]==9||grid[spY][spX-1]==4) && spX-1 >=0 && spX-1 != lastX)
                                        {
                                            spX--;
                                            lastX=spX+1;
                                            lastY=1000;
                                        }
                                    }
                                    else if (spY < epY && spX > epX)
                                    {
                                        if ((grid[spY+1][spX]==9||grid[spY+1][spX]==4) && spY+1 <100 && spY+1 !=lastY)
                                        {
                                            spY++;
                                            lastY=spY-1;
                                            lastX=1000;
                                        }
                                        else if ((grid[spY][spX-1]==9||grid[spY][spX-1]==4) && spX-1 >=0 && spX-1 != lastX)
                                        {
                                            spX--;
                                            lastX=spX+1;
                                            lastY=1000;
                                        }
                                        else if ((grid[spY-1][spX]==9||grid[spY-1][spX]==4) && spY-1 >=0 && spY-1 !=lastY)
                                        {
                                            spY--;
                                            lastY=spY+1;
                                            lastX=1000;
                                        }
                                        else if ((grid[spY][spX+1]==9||grid[spY][spX+1]==4) && spX+1 <100 && spX+1 != lastX)
                                        {
                                            spX++;
                                            lastX=spX-1;
                                            lastY=1000;
                                        }
                                    }
                                    grid[spY][spX]=4;
                                    mvaddch(spY,spX,'#');
                                    if (flag == 1)
                                    {
                                        mvprintw(61,0,"current  loc: %d,%d, %d",spY,spX,grid[spY][spX]);
                                        mvprintw(62,0,"going to loc: %d,%d, %d",epY,epX,grid[epY][epX]);
                                        mvprintw(60,51,"%d",grid[spY-1][spX]);
                                        mvprintw(61,49,"%d",grid[spY][spX-1]);
                                        mvprintw(61,51,"%d",grid[spY][spX]);
                                        mvprintw(62,51,"%d",grid[spY+1][spX]);
                                        mvprintw(61,53,"%d",grid[spY][spX+1]);
                                        refresh();
                                    }
                                    if (((epY-1==spY || epY+1 ==spY) && epX==spX)||((epX+1==spX ||epX-1==spX) && epY==spY))
                                    {
                                        rooms[z].doors[i].paired=2;
                                        rooms[rooms[z].doors[i].pRoom].doors[rooms[z].doors[i].pNum].paired=2;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    refresh();
    if (totalD < 12)
    {
        refresh();
        for (x=33; x < 67; x++)
        {
            mvaddch(25,x,'#');
            grid[25][x]=4;
        }
        for (x=0;x<6;x++)
        {
            spX=rooms[x].doors[0].locX;
            spY=rooms[x].doors[0].locY;
            if (rooms[x].doors[0].wall=='n')
                spY--;
            else if (rooms[x].doors[0].wall=='s')
                spY++;
            else if (rooms[x].doors[0].wall=='e')
                spX++;
            else if (rooms[x].doors[0].wall=='w')
                spX--;
            if (flag==1)
                mvprintw (50,0, "Room# %d, Door 0, Wall: %c",x,rooms[x].doors[0].wall);
            if (x==0)
            {
                epX=33;
                epY=25;
                while (spX != epX || spY != epY)
                {
                    if (spY < epY)
                    {
                        if (spX == epX)
                        {
                            if ((grid[spY+1][spX] == 9 || grid[spY+1][spX]==4))
                                spY++;
                            else
                                mvprintw (1,1,"STOP BEING FUCKING LAZY");
                        }
                        else if (spX < epX)
                        {
                           if (grid[spY+1][spX]==9 || grid[spY+1][spX]==4)
                               spY++;
                           else if (grid[spY][spX+1]==9||grid[spY][spX+1])
                              spX++;
                           else
                              mvprintw(0,1,"YOU ARE BEING FUCKING LAZY");
                        }
                    }
                    else if (spY == epY)
                    {
                        if (spX < epX)
                        {
                           if (grid[spY][spX+1]==9 || grid[spY][spX+1]==4)
                               spX++;
                           else
                               mvprintw (2,1,"MORE BLATANT FUCKING LAZYNESS");
                        }
                    }
                    mvaddch(spY,spX,'#');
                    grid[spY][spX]=4;
                    refresh();
                }
            }
            else if (x==3)
            {
                epX=33;
                epY=25;
                while (spX != epX || spY != epY)
                {
                    if (spY > epY)
                    {
                        if (spX == epX)
                        {
                            if ((grid[spY-1][spX] == 9 || grid[spY-1][spX]==4))
                                spY--;
                            else
                                mvprintw (1,1,"STOP BEING FUCKING LAZY3");
                        }
                        else if (spX < epX)
                        {
                           if (grid[spY-1][spX]==9 || grid[spY-1][spX]==4)
                               spY--;
                           else if (grid[spY][spX+1]==9||grid[spY][spX+1])
                              spX++;
                           else
                              mvprintw(0,1,"YOU ARE BEING FUCKING LAZY3");
                        }
                    }
                    else if (spY == epY)
                    {
                        if (spX < epX)
                        {
                           if (grid[spY][spX+1]==9 || grid[spY][spX+1]==4)
                               spX++;
                           else
                               mvprintw (2,1,"MORE BLATANT FUCKING LAZYNESS3");
                        }
                    }
                    mvaddch(spY,spX,'#');
                    grid[spY][spX]=4;
                    refresh();
                }
            }
            else if (x==2)
            {
                epX=66;
                epY=25;
                while (spX != epX || spY != epY)
                {
                    if (spY < epY)
                    {
                        if (spX == epX)
                        {
                            if ((grid[spY+1][spX] == 9 || grid[spY+1][spX]==4))
                                spY++;
                            else
                                mvprintw (1,1,"STOP BEING FUCKING LAZY2");
                        }
                        else if (spX > epX)
                        {
                           if (grid[spY+1][spX]==9 || grid[spY+1][spX]==4)
                               spY++;
                           else if (grid[spY][spX+1]==9||grid[spY][spX+1])
                              spX--;
                           else
                              mvprintw(0,1,"YOU ARE BEING FUCKING LAZY2");
                        }
                    }
                    else if (spY == epY)
                    {
                        if (spX > epX)
                        {
                           if (grid[spY][spX-1]==9 || grid[spY][spX-1]==4)
                               spX--;
                           else
                               mvprintw (2,1,"MORE BLATANT FUCKING LAZYNESS2");
                        }
                    }
                    mvaddch(spY,spX,'#');
                    grid[spY][spX]=4;
                    refresh();
                }
            }
            else if (x==5)
            {
                epX=66;
                epY=25;
                while (spX != epX || spY != epY)
                {
                    if (spY > epY)
                    {
                        if (spX == epX)
                        {
                            if ((grid[spY-1][spX] == 9 || grid[spY-1][spX]==4))
                                spY--;
                            else
                                mvprintw (1,1,"STOP BEING FUCKING LAZY5");
                        }
                        else if (spX > epX)
                        {
                           if (grid[spY-1][spX]==9 || grid[spY-1][spX]==4)
                               spY--;
                           else if (grid[spY][spX-1]==9||grid[spY][spX-1])
                              spX--;
                           else if (grid[spY+1][spX]==9||grid[spY+1][spX]==4)
                              spY++;
                           else
                              mvprintw(0,1,"YOU ARE BEING FUCKING LAZY5");
                        }
                    }
                    else if (spY == epY)
                    {
                        if (spX > epX)
                        {
                           if (grid[spY][spX-1]==9 || grid[spY][spX-1]==4)
                               spX--;
                           else
                               mvprintw (2,1,"MORE BLATANT FUCKING LAZYNESS5");
                        }
                    }
                    mvaddch(spY,spX,'#');
                    grid[spY][spX]=4;
                    refresh();
                }
            }
        }
    }
    refresh();
}

room drawRoom(room thisRoom, int tlx, int tly,int grid[50][100], monsters* mon, int* tMon, int* monPlaced)
{
    int x=0;
    int y=0;
    int dX=0;
    int dY=0;
    int itemCode=0;
    //Draw & Save Floor
    for (x = tlx ; x < thisRoom.width+tlx ; x++)
    {
        for (y = tly ; y < thisRoom.length+tly ; y++)
        {
            mvaddch(y,x,'.');
            grid[y][x]=0;
        }
    }    
    //Draw & Save E/W Wall
    for (y = tly-1; y < thisRoom.length+tly+1; y++)
    {
        mvaddch(y,tlx-1,'|');
        mvaddch(y,tlx+thisRoom.width,'|');
        grid[y][tlx-1]=2;
        grid[y][tlx+thisRoom.width]=2;
    }
    //Draw & Save N/S Wall
    for (x = tlx-1; x < thisRoom.width+tlx+1 ;x++)
    {
        mvaddch(tly-1,x,'-');
        mvaddch(tly+thisRoom.length,x,'-');
        grid[tly-1][x]=1;
        grid[tly+thisRoom.length][x]=1;
    }
    //Draw & Save Doors
    if (thisRoom.dCnt > 0)
    {
        for (x = 0; x < thisRoom.dCnt; x++)
        {
            if (thisRoom.doors[x].wall == 'n')
            {
                dY =tly-1;
                dX =tlx+thisRoom.doors[x].dist;
            }
            else if (thisRoom.doors[x].wall == 's')
            {
                dY =tly+thisRoom.length;
                dX =tlx+thisRoom.doors[x].dist;
            }
            else if (thisRoom.doors[x].wall == 'e')
            {
                dY =tly+thisRoom.doors[x].dist;
                dX =tlx+thisRoom.width;
            }
            else if (thisRoom.doors[x].wall == 'w')
            {
                dY =tly+thisRoom.doors[x].dist;
                dX =tlx-1;
            }
            thisRoom.doors[x].locY=dY;
            thisRoom.doors[x].locX=dX;
            mvaddch(dY,dX,'+');
            grid[dY][dX]=3;
        }
    }
    //Draw & Save Items
    if (thisRoom.iCnt > 0)
    {
        for (x=0; x < thisRoom.iCnt; x++)
        {
            if (thisRoom.rmItem[x].type == 'g')
            {   
                dY=tly+thisRoom.rmItem[x].locY;
                dX=tlx+thisRoom.rmItem[x].locX;
                if (grid[dY][dX]!=0)
                   dY++;
                if (grid[dY][dX]!=0)
                   dY=dY-2;
                if (grid[dY][dX]!=0)
                {
                   dY++;
                   dX++;
                }
                if (grid[dY][dX]!=0)
                   dX=dX-2;
                if (grid[dY][dX]!=0)
                   dX++;
                
                mvaddch(dY,dX,'*');
                itemCode = 100000+thisRoom.rmItem[x].value;
                grid[dY][dX]=itemCode;
            }
            else if (thisRoom.rmItem[x].type == 'p')
            {
                dY=tly+thisRoom.rmItem[x].locY;
                dX=tlx+thisRoom.rmItem[x].locX;
                if (grid[dY][dX]!=0)
                   dY++;
                if (grid[dY][dX]!=0)
                   dY=dY-2;
                if (grid[dY][dX]!=0)
                {
                   dY++;
                   dX++;
                }
                if (grid[dY][dX]!=0)
                   dX=dX-2;
                if (grid[dY][dX]!=0)
                   dX++;
                mvaddch(dY,dX,'!');
                if (thisRoom.rmItem[x].potHealth > 0)
                    itemCode = 220000+thisRoom.rmItem[x].potHealth;
                else
                    itemCode = 210000+100*thisRoom.rmItem[x].potStrModifier+thisRoom.rmItem[x].potDuration;
                grid[dY][dX]=itemCode;
            }
            else if (thisRoom.rmItem[x].type == 'm')
            {
                dY=tly+thisRoom.rmItem[x].locY;
                dX=tlx+thisRoom.rmItem[x].locX;
                if (grid[dY][dX]!=0)
                   dY++;
                if (grid[dY][dX]!=0)
                   dY=dY-2;
                if (grid[dY][dX]!=0)
                {
                   dY++;
                   dX++;
                }
                if (grid[dY][dX]!=0)
                   dX=dX-2;
                if (grid[dY][dX]!=0)
                   dX++;
                mvaddch(dY,dX,'$');
                if (thisRoom.rmItem[x].magStrModifier > 0)
                    itemCode = 300100+thisRoom.rmItem[x].magStrModifier;
                else
                    itemCode = 300200+thisRoom.rmItem[x].magHpModifier;
                grid[dY][dX]=itemCode;
            }
            else if (thisRoom.rmItem[x].type == 'w')
            {
                dY=tly+thisRoom.rmItem[x].locY;
                dX=tlx+thisRoom.rmItem[x].locX;
                if (grid[dY][dX]!=0)
                   dY++;
                if (grid[dY][dX]!=0)
                   dY=dY-2;
                if (grid[dY][dX]!=0)
                {
                   dY++;
                   dX++;
                }
                if (grid[dY][dX]!=0)
                   dX=dX-2;
                if (grid[dY][dX]!=0)
                   dX++;
                mvaddch(dY,dX,')');
                itemCode = 400000+10000*thisRoom.rmItem[x].wType+1000*thisRoom.rmItem[x].wMat+thisRoom.rmItem[x].wepStrModifier;
                grid[dY][dX]=itemCode;
            }
        }
    }
    //Draw & Save Monsters
    if (thisRoom.mCnt > 0)
    {
        y=0;
        for (x=0; x < thisRoom.mCnt ; x++)
        {
            dY=tly+thisRoom.monY[x];
            dX=tlx+thisRoom.monX[x];
            if (grid[dY][dX]!=0)
               dY++;
            if (grid[dY][dX]!=0)
               dY=dY-2;
            if (grid[dY][dX]!=0)
            {
               dY++;
               dX++;
            }
            if (grid[dY][dX]!=0)
               dX=dX-2;
            if (grid[dY][dX]!=0)
               dX++;
            mvaddch(dY,dX,thisRoom.monT[x]);
            mon[*monPlaced+x-y].locY = dY;
            mon[*monPlaced+x-y].locX = dX;
            mon[*monPlaced+x-y].monID = *monPlaced+x-y;
            itemCode = 500000 + 10000*thisRoom.monNT[x] + mon[*monPlaced+x-y].monID;
            grid[dY][dX]=itemCode;
            *monPlaced=*monPlaced+1;
            y++;
        }
    }
    //Draw & Save Stairs
    if (thisRoom.sCnt > 0)
    {
        for (x=0; x < thisRoom.sCnt; x++)
        {
            dY=tly+thisRoom.stairs[x].locY;
            dX=tlx+thisRoom.stairs[x].locX;
            if (grid[dY][dX]!=0)
               dY++;
            if (grid[dY][dX]!=0)
               dY=dY-2;
            if (grid[dY][dX]!=0)
            {
               dY++;
               dX++;
            }
            if (grid[dY][dX]!=0)
               dX=dX-2;
            if (grid[dY][dX]!=0)
               dX++;
            mvaddch(dY,dX,'%');
            grid[dY][dX]=5;
        }
    }
    refresh();
    return(thisRoom);
}

void drawZoneLines (int mode)
{
    int x =0;
    for (x = 0; x < 100; x++)
    {
        if (mode >0)
            mvaddch(50,x,'_');
        if (mode >1)
            mvaddch(25,x,'0');
        if (mode >2)
        {
            mvaddch(0,x,'0');
            mvaddch(49,x,'0');
            if (x % 5 == 0)
                mvprintw(52,x,"%d",x);
        }
    }
    for (x = 0; x <50; x++)
    {
        if (mode >0)
            mvaddch(x,100,'|');
        if (mode >1)
        {
            mvaddch(x,33,'0');
            mvaddch(x,66,'0');
        }
        if (mode >2)
        {
            mvaddch(x,0,'0');
            mvaddch(x,99,'0');
	    mvprintw(x,101,"%d",x);
        }
    }
    refresh();
}

int randMovX (int roomW)
{
    int x;
    int y = 30 - roomW;
    srand(time(NULL));
    x = (rand() %y) +2;
    return(x);
}

int randMovY (int roomL)
{
    int x;
    int y = 22 - roomL;
    srand(time(NULL));
    x = (rand() %y) +2;
    return(x);
}

void clearScreen(void)
{
    int x;
    int y;
    for (x=0; x < 100; x++)
       for (y=0; y < 50; y++)
          mvaddch(y,x,' ');
}
