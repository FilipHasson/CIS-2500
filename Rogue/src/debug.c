/*************************debug.c****************************
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
#include "debug.h"

void fileDump (room myRoom[6], monsters* myMon, playerSt* myHero, int* tMon, int grid[50][100])
{
    int x;
    int y;
    FILE *f = fopen ("dump.txt","w+");
    FILE *fcsv = fopen ("dump.csv","w+");
    FILE *fm = fopen ("dumpMon.txt","w+");
    if (f != 0)
    {
        for (x=0;x<6;x++)
        {
            fprintf(f,"______________________ROOM #%d_____________________\n",x);
            fprintf(f,"Dimensions: Length: %d, Width %d\n",myRoom[x].length,myRoom[x].width);
            fprintf(f,"TOTAL: Doors: %d, Items: %d, Stairs: %d, Monsters: %d\n",myRoom[x].dCnt,myRoom[x].iCnt,
            myRoom[x].sCnt,myRoom[x].mCnt);
            fprintf(f,"______________________ITEMS_____________________\n");
            for (y = 0; y<myRoom[x].iCnt;y++)
            {
                if (myRoom[x].rmItem[y].type=='w')
                    fprintf(f,"Type: w, Name: %s%s, Dam: %d, wType: %d, wMat %d, LOC: %d,%d\n",myRoom[x].rmItem[y].wepType,
                    myRoom[x].rmItem[y].name,myRoom[x].rmItem[y].wepStrModifier,myRoom[x].rmItem[y].wType,
                    myRoom[x].rmItem[y].wMat,myRoom[x].rmItem[y].locY,myRoom[x].rmItem[y].locX);
                else if (myRoom[x].rmItem[y].type=='p')
                    fprintf(f,"Type: p, Name: %s, Heals: %d OR str: %d duration: %d, LOC: %d,%d\n",myRoom[x].rmItem[y].name,
                    myRoom[x].rmItem[y].potHealth,myRoom[x].rmItem[y].potStrModifier,myRoom[x].rmItem[y].potDuration,
                    myRoom[x].rmItem[y].locY,myRoom[x].rmItem[y].locX);
                else if (myRoom[x].rmItem[y].type=='m')
                    fprintf(f,"Type: m, Name: %s, ENCH: Health: %d OR str: %d, LOC: %d,%d\n",myRoom[x].rmItem[y].name,
                    myRoom[x].rmItem[y].magHpModifier,myRoom[x].rmItem[y].magStrModifier,myRoom[x].rmItem[y].locY,
                    myRoom[x].rmItem[y].locX);
                else if (myRoom[x].rmItem[y].type=='g')
                    fprintf(f,"Type: g, Name: %s, Val: %d, LOC: %d%d\n",myRoom[x].rmItem[y].name,myRoom[x].rmItem[y].value,
                    myRoom[x].rmItem[y].locY,myRoom[x].rmItem[y].locX);
            }
            fprintf(f,"______________________STAIRS_____________________\n");
            for (y = 0; y<myRoom[x].sCnt;y++)
            {
                fprintf(f,"Room: %d, LOC: %d%d\n",myRoom[x].stairs[y].room,myRoom[x].stairs[y].locY,
                myRoom[x].stairs[y].locX);
            }
            fprintf(f,"____________________DOORS______________________\n");
            for (y=0;y<myRoom[x].dCnt;y++)
            {
                fprintf(f,"Room: %d, Wall: %c, dist: %d\n",x,myRoom[x].doors[y].wall,myRoom[x].doors[y].dist);
            }
            fprintf(f,"______________________MONSTERS___________________\n");
            for (y = 0; y < myRoom[x].mCnt; y++)
            {
                fprintf(f,"Type: %c, numT: %d, LOC: %d,%d | num: %d\n",myRoom[x].monT[y],myRoom[x].monNT[y],
                myRoom[x].monY[y],myRoom[x].monX[y],y);
            }
        }
        fclose(f);
    }
    if (fm !=0)
    {
        fprintf(f,"___________________MONSTER_POINTER______________________\n");
        for (y=0; y<tMon[0]; y++)
        {
            fprintf(fm,"Name: %s\t\tType %c, hp: %d, dam: %d ",myMon[y].name,myMon[y].type,myMon[y].hp,myMon[y].damage);
            fprintf(fm,"Room #%d,    StartLoc: %d,%d,    realLoc, %d,%d\n",myMon[y].startRoom,myMon[y].rLocY,myMon[y].rLocX,
            myMon[y].locY,myMon[y].locX);
            }
    fclose(fm);
    }
    if (fcsv != 0)
    {
        for (y=0; y<50; y++)
        {
            for (x=0; x< 100; x++)
            {
                fprintf(fcsv,"%d,",grid[y][x]);
            }
            fprintf(fcsv,"\n");
        }
    }
}
