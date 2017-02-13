/*************************a1.c****************************
Student Name: Filip Hasson                   Student Number:  0878596
Date: 01/16/2015                             Course Name: CIS 2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
****************************************************************************/
#include "a1.h"

int main ()
{
    int i,j;
    int input='n';
    int resume=0;
    FILE *file;
    char fileName[] ="save.fil";
    char fileName1[40];
    char fileName2[40];
    char test[1];
    int savedGrid[7][7];

    /*Init ncruses */
    initscr();
    start_color();

    /*Set Up Color Pairs*/
    init_pair(1, COLOR_WHITE,COLOR_BLACK);
    init_pair(2, COLOR_RED,COLOR_BLACK);
    init_pair(3, COLOR_BLUE,COLOR_BLACK);
    attron(COLOR_PAIR(1));

    /*Create the saveGame directory if none exists*/
    file = fopen(fileName,"r");
    if (file==NULL)
    {
        file = fopen(fileName,"w+");
    }
    /*Scans file for mark that determines if there is a save game*/
    fscanf(file,"%s",test);
    if (test[0]=='1')
    {
        input='q';
        while (input != 'y'&& input!='Y' && input != 'n' && input != 'N')
        {
            clear();
            mvprintw (10,20,"We detected a game in progress, would you like to resume it? Y/N: ");
            input=getch();
            clear();
        }
    }
    /*Loads player names and game board*/
    if (input == 'y'|| input=='Y')
    {
        resume=1;
        fscanf(file, "%s ",fileName1);
        fscanf(file, "%s ",fileName2);
        for (i=1;i<7; i++)
        {
            for (j=1;j<7;j++)
            {
                fscanf(file,"%d",&savedGrid[i][j]);
            }
        }
    }
    /*Starts a new game*/
    else if (input=='n' || input == 'N')
    {
        resume=0;
        /*Asks Player Names/AI Option*/
        mvaddstr(10,20,"Enter a name for player one: ");
        getstr(fileName1);
        clear();
        mvaddstr(8,20,"Enter the name EDI to face the AI!");
        mvaddstr(10,20,"Enter a name for player two: ");
        getstr(fileName2);
        clear();

    }
    /*Initialize game, and endgame*/
    fclose(file);
    playGame (resume,fileName1,fileName2,savedGrid);
    refresh();
    getch();
    endwin();
    return 0;
}

/********
playGame: This plays the whole game, essentially
In: int resume, char pOneName[40], pTwoName[40],int savedGrid[7][7]
Out: voided function does not return
Post: goes back to the main to end the game
********/
void playGame (int resume, char pOneName[40], char pTwoName[40],int savedGrid[7][7])
{
    FILE *file;
    FILE *scoreFile;
    char fileScore[]="scores.fil";
    char fileName[] ="save.fil";
    char names[40][100];
    int loadTurnBugFix=0;
    int pOneSaved=0;
    int pTwoSaved=0;
    int scores[100];
    int totalScores;
    int totalChanged=0;
    int scoreOne=0;
    int scoreTwo=0;
    int locX=1;
    int locY=1;
    int input;
    int playerTurn =1;
    int scrH = 48;
    int scrW = 96;
    int grid[7][7];
    int i,k;
    int endCount =196;
    int ai=0;
    int hintToggle=0;

    /*Create the score directory if none exists*/
    scoreFile = fopen(fileScore,"r");
    if (scoreFile==NULL)
    {
        scoreFile = fopen(fileScore,"w+");
        fprintf(scoreFile,"1\n");
        fprintf(scoreFile,("Default 1\n"));
        fclose(scoreFile);
        scoreFile=fopen(fileScore,"r");
    }

    /*Loads player win score*/
    fscanf(scoreFile, "%d",&totalScores);
    for (i=0; i<totalScores; i++)
    {
        fscanf(scoreFile, "%s %d",names[i],&scores[i]);
        if (strcmp(names[i],pOneName)==0)
        {
            pOneName=names[i];
            scoreOne=scores[i];
            i++;
        }
        if (strcmp(names[i],pTwoName)==0)
        {
            pTwoName=names[i];
            scoreTwo=scores[i];
        }
    }
    fclose(scoreFile);
    /*Resumes a quit game*/
    if (resume==1)
    {
        for (i=1; i<7; i++)
        {
            for (k=1; k<7; k++)
            {
                grid[i][k]=savedGrid[i][k];
                if (grid[i][k]==1 || grid[i][k]==2)
                    loadTurnBugFix++;
            }
        }
        if (loadTurnBugFix%2==0)
            playerTurn=1;
        else
            playerTurn=2;
        drawScreen(scrH,scrW,grid);
    }
    else
    {
        /*Sets Blank Grid*/
        for (i = 0;i<7; i++)
        {
            for (k=0; k<7; k++)
                grid[i][k]=0;
        }
    }

    /*Set Up Color Pairs*/
    init_pair(1, COLOR_WHITE,COLOR_BLACK);
    init_pair(2, COLOR_RED,COLOR_BLACK);
    init_pair(3, COLOR_BLUE,COLOR_BLACK);

    /*More Init ncruses*/
    cbreak();
    noecho();
    mvprintw(50,0,"Movement Keys:");
    mvprintw(51,15,"  I  ");
    mvprintw(52,15,"J K L");
    mvprintw(50,25,"Place Letter:");
    mvprintw(51,40,"E");
    mvprintw(50,50,"Quit:");
    mvprintw(51,57,"Q");
    mvprintw(50,65,"Quit + Delete Save:");
    mvprintw(51,87,"X");
    mvprintw(55,0,"%s: %d",pOneName,scoreOne);
    mvprintw(56,0,"%s: %d",pTwoName,scoreTwo);
    mvprintw(58,0,"For a hint from IDE press H:");

   /*Init AI*/
    if (strcmp (pTwoName, "EDI")== 0)
    {
        ai=1;
        mvaddstr(49,0,":EDI: Extremely Dumb Intelligence has been initiated.");
    }

    /*Runs the game*/
    while (input != 'q' && input != 'Q')
    {
        drawScreen(scrH,scrW,grid);

        /*Stops loop if game is over*/
        if (endCount==0)
            break;

        /*Sets player color*/
        if (playerTurn==1)
            attron(COLOR_PAIR(2));
        else
            attron(COLOR_PAIR(3));
        selectedBox(locX,locY);

        /*AI Thinking Process*/
        if (playerTurn==2 && ai==1)
        {
            for (i=1;i<7;i++)
            {
                for (k=1;k<7;k++)
                {
                    if (grid[i][k]==0)
                    {
                        grid[i][k]=2;
                        if (grid[i-1][k-1]==0)
                            grid[i-1][k-1]=3;
                        if (grid[i-1][k]==0)
                            grid[i-1][k]=3;
                        if (grid[i-1][k+1]==0)
                            grid[i-1][k+1]=3;
                        if (grid[i][k-1]==0)
                            grid[i][k-1]=3;
                        if (grid[i][k+1]==0)
                            grid[i][k+1]=3;
                        if (grid[i+1][k-1]==0)
                            grid[i+1][k-1]=3;
                        if (grid[i+1][k]==0)
                            grid[i+1][k]=3;
                        if (grid[i+1][k+1]==0)
                            grid[i+1][k+1]=3;
                        playerTurn=1;
                        k=8;
                        i=8;
                    }
                }
            }
            continue;
        }

        /*User Input Section*/
        input = getch();
        if ((input=='i'||input=='I') && locY!=1)
        {
            locY--;
            clearSelected (locX,locY,3);
            selectedBox(locX,locY);
        }
        else if ((input=='j'||input=='J') && locX !=1)
        {
            locX--;
            clearSelected(locX,locY,1);
            selectedBox(locX,locY);
        }
        else if ((input=='k'||input=='K') && locY!=6)
        {
            locY++;
            clearSelected(locX,locY,2);
            selectedBox(locX,locY);
        }
        else if ((input=='l'||input=='L') &&locX !=6)
        {
            locX++;
            clearSelected(locX,locY,0);
            selectedBox(locX,locY);
        }
        else if (input=='e'||input=='E')
        {
            /*filling grid values to new results*/
            if (grid[locY][locX]==0)
            {
                if (grid[locY-1][locX-1]==0)
                    grid[locY-1][locX-1]=3;
                if (grid[locY-1][locX]==0)
                    grid[locY-1][locX]=3;
                if (grid[locY-1][locX+1]==0)
                    grid[locY-1][locX+1]=3;
                if (grid[locY][locX-1]==0)
                    grid[locY][locX-1]=3;
                if (grid[locY][locX+1]==0)
                    grid[locY][locX+1]=3;
                if (grid[locY+1][locX-1]==0)
                    grid[locY+1][locX-1]=3;
                if (grid[locY+1][locX]==0)
                    grid[locY+1][locX]=3;
                if (grid[locY+1][locX+1]==0)
                    grid[locY+1][locX+1]=3;
                if (playerTurn==1)
                {
                   grid[locY][locX]=1;
                   playerTurn=2;
                }
                else if (playerTurn==2)
                {
                    grid[locY][locX]=2;
                    playerTurn=1;
                }
            }
        }

        /*Toggle Hint From IDE*/
        if (input=='h'||input=='H')
        {
            if (hintToggle==0)
            {
                hintToggle=1;
                for (i=1;i<7;i++)
                {
                    for (k=1;k<7;k++)
                    {
                        if (grid[i][k]==0)
                        {
                            attron(COLOR_PAIR(1));
                            mvprintw(59,0,"IDE believes that you should play on position: (%d,%d) (x,y)",k,i);
                        }
                    }
                }
            }
            else if (hintToggle==1)
            {
                hintToggle=0;
                mvprintw(59,0,"                                                                             ");
            }
        }
        else if (input=='x'||input=='X')
        {
            endCount=36;
            break;
        }

        /*Checks if there are any empty spaces*/
        endCount=0;
        for (i=1; i<7; i++)
        {
            for (k=1; k<7; k++)
                {
                    if (grid[i][k]==0)
                        endCount++;
                }
        }
    }
    /*Win Text*/
    if (endCount==0)
    {
        if (playerTurn==2)
        {
            mvprintw (55,20,"Congradulations %s!",pOneName);
            scoreOne++;
        }
        else
        {
            mvprintw (55,20,"Congradulations %s!",pTwoName);
            scoreTwo++;
        }

        /*delets temporary game save after game is won*/
        file=fopen(fileName,"r+");
        fprintf(file,"0\n");

        /*Opens score file and populates with new results*/
        scoreFile=fopen(fileScore,"w+");
        for (i=0;i<totalScores;i++)
        {
            if (strcmp(names[i],pOneName)==0)
            {
                fprintf(scoreFile,"%s %d\n",pOneName,scoreOne);
                pOneSaved=1;
                i++;
            }
            if (strcmp(names[i],pTwoName)==0)
            {
                fprintf(scoreFile,"%s %d\n",pTwoName,scoreTwo);
                pTwoSaved=1;
                i++;
            }
            fprintf(scoreFile,"%s %d\n",names[i],scores[i]);
        }
        /*Updates the total score of the score file*/
        if (totalScores<100)
        {
            if (pOneSaved==0)
            {
                fprintf(scoreFile,"%s %d\n",pOneName,scoreOne);
                totalScores++;
                totalChanged++;
            }
        }
        if (totalScores<100)
        {
            if (pTwoSaved==0)
            {
                fprintf(scoreFile,"%s %d\n",pTwoName,scoreTwo);
                totalScores++;
                totalChanged++;
            }
        }
        fclose(scoreFile);
    }
    if (totalChanged!=0)
    {
       scoreFile=fopen(fileScore,"r");
       fscanf(scoreFile,"%d",&i);
       for (k=0;k<i+totalChanged;k++)
       {
           fscanf(scoreFile,"%s %d",names[k],&scores[k]);
       }
       fclose(scoreFile);
       scoreFile=fopen(fileScore,"w+");
       fprintf(scoreFile,"%d\n",totalScores);
       for (k=0;k<totalScores;k++)
       {
           fprintf(scoreFile,"%s %d\n",names[k],scores[k]);
       }
       fclose(scoreFile);
    }
    /*Delete Save if user presses x*/
    if (endCount==36)
    {
        file=fopen(fileName,"r+");
        fprintf(file,"0\n");
        mvprintw (55,20,"Thanks for playing!");
    }
    /*Save Game In Progress*/
    else if (input=='q'||input=='Q')
    {
        attron(COLOR_PAIR(1));
        file=fopen(fileName,"r+");
        fprintf(file,"1\n");
        fprintf(file,"%s\n",pOneName);
        fprintf(file,"%s\n",pTwoName);
        for (i=1;i<7;i++)
        {
            for (k=1;k<7;k++)
            {
                fprintf(file,"%d\n",grid[i][k]);
            }
        }
        mvprintw (55,20,"Board saved, you will be able to resume the game upon restart.");
    }
    fclose(file);
}

/*
drawScreen: takes in values and then updates/draws the board
In: int height, int width, int grid[7][7]
Out: none its a voided function
Post: screen gets updated
*/
void drawScreen (int height, int width,int grid[7][7])
{
    int x=0;
    int y=0;
    char border ='#';
    init_pair (1,COLOR_WHITE, COLOR_BLACK);
    init_pair (2, COLOR_RED, COLOR_BLACK);
    init_pair (3, COLOR_BLUE, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    /*Draw Game boarder*/
    for (x=0 ; x<width+1 ; x++)
    {
        mvaddch (y, x, border);
        mvaddch (height, x, border);
        mvaddch (8, x, border);
        mvaddch (16, x, border);
        mvaddch (24, x, border);
        mvaddch (32, x, border);
        mvaddch (40, x, border);
    }
    for (y=1; y < height ; y++)
    {
        mvaddch (y, 0, border);
        mvaddch (y, width, border);
        mvaddch (y, 16, border);
        mvaddch (y, 32, border);
        mvaddch (y, 48, border);
        mvaddch (y, 64, border);
        mvaddch (y, 80, border);
    }
    /*Draws specifc units X, O and -*/
    for (x=1; x<7; x++)
    {
        for (y=1; y<7; y++)
        {
            if (grid[y][x]==2)
                {
                attron(COLOR_PAIR(3));
                drawO(y,x);
                }
            else if (grid[y][x]==1)
                {
                attron(COLOR_PAIR(2));
                drawX(y,x);
                }
            else if (grid[y][x]==3)
                {
                attron(COLOR_PAIR(1));
                drawBlock (y,x);
                }
        }
    }
    refresh();
}

/*
selectedBox: draws the selection box made of @ signs
In: int collumn, int row
Out: none its a void
Post: the selection box is drawn in the newly moved square
*/
void selectedBox (int collumn, int row)
{
    int x = 16*collumn-15;
    int y = 8*row-7;
    int i;
    for (i=0; i<15; i++)
    {
        mvaddch (y, x+i, '@');
        mvaddch (y+6, x+i, '@');
    }
    for (i=0;i<7;i++)
    {
        mvaddch (y+i, x, '@');
        mvaddch (y+i, x+14, '@');
    }
}

/*
clearSelected: clears the selection box from the last square that it was in
In: int collumn, int row, int last
out: non another voided method!
Post: the old selection box is erased
*/
void clearSelected (int collumn, int row, int last)
{
    int x;
    int y;
    int i;
    if (last==0)
        collumn--;
    else if (last==1)
        collumn++;
    else if (last==2)
        row--;
    else if (last==3)
        row++;
    x=16*collumn-15;
    y=8*row-7;
    for (i=0;i<15;i++)
    {
        mvaddch(y, x+i, ' ');
        mvaddch(y+6, x+i, ' ');
    }
    for (i=0; i<7; i++)
    {
        mvaddch(y+i, x, ' ');
        mvaddch(y+i, x+14, ' ');
    }
}

/*
drawX: draws a beautiful ascii art x
in: int collums, int rows
out: lol once again none as it is voided
post: an x is drawn
*/
void drawX (int collumns, int rows)
{
    int x;
    int y;
    x= (16*rows-15)+1;
    y= (8*collumns-7)+1;
    mvaddstr (y, x, "XXX       XXX");
    mvaddstr (y+1,x,"  XXX   XXX");
    mvaddstr (y+2,x,"     XXX");
    mvaddstr (y+3,x,"  XXX   XXX");
    mvaddstr (y+4,x,"XXX       XXX");
}

/*
drawO: draws a beautiful ascii art o
in: int collumns, int rows
out: guess? yup VOIDED!
post: an o is drawn
*/
void drawO (int collumns, int rows)
{
    int x;
    int y;
    x= (16*rows-15)+1;
    y= (8*collumns-7)+1;
    mvaddstr (y, x, "   OOOOOOO");
    mvaddstr (y+1,x," OOO     OOO");
    mvaddstr (y+2,x,"OOO       OOO");
    mvaddstr (y+3,x," OOO     OOO");
    mvaddstr (y+4,x,"   OOOOOOO");
}

/*
drawBlock: draws a big nast block of -'s
in: int collumns, int rows
out: na na na na na na na na voided! VOIDED!
post: a big block is drawn.
*/
void drawBlock (int collumns, int rows)
{
    int x=0;
    int y=0;
    x= (16*rows-15)+1;
    y= (8*collumns-7)+1;
    mvaddstr (y, x, "-------------");
    mvaddstr (y+1,x,"-------------");
    mvaddstr (y+2,x,"-------------");
    mvaddstr (y+3,x,"-------------");
    mvaddstr (y+4,x,"-------------");
}
