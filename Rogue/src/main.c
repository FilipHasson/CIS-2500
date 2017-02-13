/*************************main.c****************************
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
#include "drawGame.h"
#include "debug.h"
#include "gameplay.h"

int main (int argc, char*argv[])
{
    int x=0;
    int grid[50][100];
    int devFlags[5];
    char buffer[150];
    room rooms[6];
    playerSt* hero =malloc(sizeof(playerSt));
    monsters* monster =malloc(sizeof(monsters)*150);
    int* tMon =malloc(sizeof(int));
    srand(time(NULL));

    for (x=0;x<6;x++)
        rooms[x]=blankRoom(rooms[x]);
    setZero(monster, hero, tMon);
    for (x=0;x<5;x++)
        devFlags[x]=0;

    if (argc < 2)
        printf("usage: %s filename", argv[0]);
    else
    {
        FILE *file = fopen (argv[1],"r");
        if (file == 0)
        {
            printf("Could not open file\n");
            printf("Please enter flags as ./run <filePath> <debugF>");
        }
        else
        {
            for (x=1;x<argc;x++)
            {
                if (strcmp(argv[x],"-p")==0)
                    devFlags[0]=1;
                else if (strcmp(argv[x],"-b1")==0)
                    devFlags[1]=1;
                else if (strcmp(argv[x],"-b2")==0)
                    devFlags[1]=2;
                else if (strcmp(argv[x],"-b3")==0)
                    devFlags[1]=3;
                else if (strcmp(argv[x],"-d")==0)
                    devFlags[2]=1;
                else if (strcmp(argv[x],"-h")==0)
                    devFlags[3]=1;
            }
            for (x=0;x<6;x++)
            {
                fgets(buffer, 150, file);
                removeNewline (buffer);
                rooms[x]=parseFunc(buffer,x,hero,monster,devFlags[0],tMon);
            }
            initBoard(rooms,grid,monster,devFlags,tMon,hero);
            playGame(grid,monster,hero,tMon);
        }
    }
    if (devFlags[2]==1)
    {
        fileDump(rooms, monster, hero, tMon, grid);
        mvprintw(51,0,"Took a nice old dump :)");
    }
    refresh();
    endwin();
    free(hero);
    free(monster);
    free(tMon);
    return(0);
}
