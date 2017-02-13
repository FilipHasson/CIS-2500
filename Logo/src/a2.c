/*****************************************a2.c*********************************************
Student Name: Filip Hasson                   Student Number:  0878596
Date: 02/13/2015                             Course Name: CIS  2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
*******************************************************************************************/

#include "functions.h"

int main (void)
{
    int x = 0;
    int parsedVal=0;
    int parsedVal2=0;
    int penUp=0;
    int lines=0;
    int hide=0;
    char printBuffer[100][255];
    char part1[98];
    char part2[98];
    char part3[98];
    char save='n';
    FILE *file;
    cursorT * cursPtr=malloc(sizeof(cursorT));

    if (cursPtr==NULL)
    {
        mvprintw (46,1,"There is not enough memory to run the program!");
    };

    cursPtr->locX =48;
    cursPtr->locY =22;
    cursPtr->dir =0;
    cursPtr->color =1;

    initscr();
    start_color();
    init_pair(1, COLOR_WHITE,COLOR_WHITE);
    init_pair(2, COLOR_WHITE,COLOR_BLACK);
    init_pair(3, COLOR_BLUE,COLOR_BLACK);
    init_pair(4, COLOR_RED,COLOR_BLACK);
    init_pair(5, COLOR_YELLOW,COLOR_BLACK);
    init_pair(6, COLOR_GREEN,COLOR_BLACK);
    attron(COLOR_PAIR(1));
    for (x = 0; x < 100; x++)
    {
        mvaddch(0,x,' ');
        mvaddch(44,x,' ');
        mvaddch(54,x,' ');
    }
    for (x = 0; x <55; x++)
    {
        mvaddch(x,0,' ');
        mvaddch(x,100,' ');
    }
    attron(COLOR_PAIR(2));
    while (strcmp(part1,"quit")!=0)
    {
        attron(COLOR_PAIR(2));
        strcpy(part1,"");
        strcpy(part2,"");
        strcpy(part3,"");
        drawCursor (*cursPtr);
        if (hide==1)
            mvaddch(cursPtr->locY,cursPtr->locX,' ');
        attron(COLOR_PAIR(2));
        move(45,1);
        scanw ("%s %s %s",part1,part2,part3);
        strcpy (printBuffer[lines],part1);
        strcat (printBuffer[lines]," ");
        strcat (printBuffer[lines],part2);
        lines++;
        clearUserText ();
        clearMessageText();
        refresh();
        if (strcmp (part1,"setpencolor")==0)
        {
            if (strcmp(part2,"blue")==0)
                cursPtr->color=1;
            else if (strcmp(part2,"red")==0)
                cursPtr->color=2;
            else if (strcmp(part2,"yellow")==0)
                cursPtr->color=3;
            else if (strcmp(part2,"green")==0)
                cursPtr->color=4;
            else
                mvprintw (47,1,"Please only enter blue, red, yellow or green as a color");
            refresh();
        }
        else if (strcmp(part1,"fd")==0)
        {
            parsedVal = atoi(part2);
            if (parsedVal <= 0)
                mvprintw (47,1,"Please Enter A Positive Number");
            else
                forward (cursPtr, parsedVal, penUp);
        }
        else if (strcmp(part1,"bk")==0)
        {
            parsedVal = atoi(part2);
            if (parsedVal <= 0)
                mvprintw (47,1,"Please Enter A Positive Number");
            else
                back (cursPtr,parsedVal,penUp);
        }
        else if (strcmp(part1,"rt")==0)
        {
            parsedVal = atoi(part2);
            if (parsedVal <= 0)
                mvprintw (47,1,"Please Enter A Positive Number");
            else if (parsedVal != 30 && parsedVal != 90 && parsedVal != 45)
                mvprintw (47,1,"Please only use 30 and 90 degree values");
            else
                rotateRight(cursPtr,parsedVal);
        }
        else if (strcmp (part1,"lt")==0)
        {
            parsedVal = atoi (part2);
            if (parsedVal <=0)
                mvprintw (47,1,"Please Enter A Positive Number");
            else if (parsedVal != 30 && parsedVal != 90 && parsedVal != 45)
                mvprintw (47,1,"Please only use 30 and 90 degree values");
            else
                rotateLeft(cursPtr,parsedVal);
        }
        else if (strcmp (part1,"pd")==0)
        {
            penUp=0;
        }
        else if (strcmp (part1,"pu")==0)
        {
            penUp=1;
        }
        else if (strcmp (part1,"quit")==0)
        {
            clearMessageText();
            mvprintw (47,1,"Would you like to save your code? y/n ");
            save = getch();
            if (save == 'y' || save == 'Y')
            {
                file = fopen("code.logo","w+");
                for (x=0;x<=lines;x++)
                {
                    fprintf(file,"%s\n",printBuffer[x]);
                }
            }
            else
                mvprintw(47,1,"Thank you for playing!                       ");
	}
        else if (strcmp (part1,"ht")==0)
            hide=1;
        else if (strcmp (part1,"st")==0)
            hide=0;
        else if (strcmp (part1,"setxy")==0)
        {
            parsedVal = atoi (part2);
            parsedVal2 = atoi (part3);
            if (parsedVal >99 || parsedVal2 >43 || parsedVal==0 || parsedVal2==0)
                mvprintw (47,1,"Sorry this would take you out of the drawing board!");
            else if (parsedVal >0 && parsedVal2 >0)
            {
                mvaddch (cursPtr->locY,cursPtr->locX,' ');
                cursPtr->locX=parsedVal;
                cursPtr->locY=parsedVal2;
            }
            else
                mvprintw(47,1,"Please enter command as: setxy <x value> <y value>");
        }
        else if (strcmp (part1,"clean")==0)
            clean();
        else if (strcmp (part1,"home")==0)
        {
            cursPtr->locX=48;
            cursPtr->locY=22;
        }
        else
            mvprintw (47,1,"Please only enter a valid logo command");
        refresh();
    }

    file = fopen("assets/code.txt","w+");
    for (x=0;x<=lines;x++)
    {
        fprintf(file,"%s\n",printBuffer[x]);
    }
    fclose(file);
    getch();
    free(cursPtr);
    endwin();
    return 0;
}
