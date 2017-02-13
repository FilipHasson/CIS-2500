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

void drawCursor (cursorT curs)
{
    attron (COLOR_PAIR(2));
    mvprintw (curs.locY, curs.locX, "+");
}

void clearUserText(void)
{
    int x=0;
    attron(COLOR_PAIR(2));
    for (x=1;x<100;x++)
        mvprintw(45,x," ");
    refresh();
}

void clearMessageText(void)
{
    int x=0;
    attron (COLOR_PAIR(2));
    for (x=1;x<100;x++)
        mvprintw(47,x," ");
    refresh();
}

void forward (cursorT * curs, int dist, int pu)
{
    int startX = curs->locX;
    int startY = curs->locY;
    int count = 0;
    if (curs->color ==1)
        attron (COLOR_PAIR(3));
    else if (curs->color ==2)
        attron (COLOR_PAIR(4));
    else if (curs->color ==3)
        attron (COLOR_PAIR(5));
    else if (curs->color ==4)
        attron (COLOR_PAIR(6));
    else
        attron (COLOR_PAIR(1));
    mvaddch (curs->locY,curs->locX,' ');
    if (curs->dir==0)
    {
        if (curs->locY - dist < 1)
            mvprintw(47,1,"Sorry this would take you out of bounds");
        else
        {
            curs->locY = curs->locY - dist;
            for (startY=startY; startY >= curs->locY; startY--)
                if (pu == 0)
                    fill (startX, startY);
        }
    }
    else if (curs->dir == 1)
    {
        if (curs->locX + (dist/3) > 99 || curs->locY - dist < 1)
            mvprintw(47,1,"Sorry this would take you out of bounds");
        else
        {
            curs->locX = curs->locX + (dist/3);
            curs->locY = curs->locY - dist;
            for (startX=startX; startX <=curs->locX; startX++)
            {
                count=0;
                for (startY=startY; startY >=curs->locY; startY--)
                {
                    if (pu == 0)
                        fill (startX, startY);
                    count++;
                    if (count==3)
                        break;
                }
            }
        }
    }
    else if (curs->dir == 2)
    {
        if (curs->locX + dist > 99 || curs->locY - (dist/3) < 1)
            mvprintw(47,1,"Sorry this would take you out of bounds");
        else
        {
            curs->locX = curs->locX + dist;
            curs->locY = curs->locY - (dist/3);
            for (startY=startY; startY >=curs->locY; startY--)
            {
                count=0;
                for (startX=startX; startX <=curs->locX; startX++)
                {
                    if (pu == 0)
                        fill (startX, startY);
                    count++;
                    if (count==3)
                        break;
                }
            }
        }
    }
    else if (curs->dir == 3)
    {
        if (curs->locX + dist > 99)
            mvprintw(47,1,"Sorry this would take you out of bounds");
        else
        {
            curs->locX = curs->locX + dist;
            for (startX=startX; startX <= curs->locX;startX++)
                if (pu == 0)
                    fill (startX,startY);
        }
    }
    else if (curs->dir == 4)
    {
        if (curs->locX + dist > 99 || curs->locY + (dist/3) > 43)
            mvprintw(47,1,"Sorry this would take you out of bounds");
        else
        {
            curs->locX = curs->locX + dist;
            curs->locY = curs->locY + (dist/3);
            for (startY=startY; startY <=curs->locY; startY++)
            {
                count=0;
                for (startX=startX; startX <=curs->locX; startX++)
                {
                    if (pu == 0)
                        fill (startX, startY);
                    count++;
                    if (count==3)
                        break;
                }
            }
        }
    }
    else if (curs->dir == 5)
    {
        if (curs->locX +(dist/3)> 99 || curs->locY +dist > 43)
            mvprintw(47,1,"Sorry this would take you out of bounds");
        else
        {
            curs->locX = curs->locX + (dist/3);
            curs->locY = curs->locY + dist;
            for (startX=startX; startX <=curs->locX; startX++)
            {
                count=0;
                for (startY=startY; startY <=curs->locY; startY++)
                {
                    if (pu == 0)
                        fill (startX, startY);
                    count++;
                    if (count==3)
                        break;
                }
            }
        }
    }
    else if (curs->dir == 6)
    {
        if (curs->locY + dist > 43)
            mvprintw(47,1,"Sorry this would take you out of bounds");
        else
        {
            curs->locY = curs->locY + dist;
            for (startY=startY; startY <= curs->locY; startY++)
                if (pu == 0)
                    fill (startX,startY);
        }
    }
    else if (curs->dir == 7)
    {
        if (curs->locY + dist > 43 || curs->locX - (dist/3) < 1)
            mvprintw(47,1,"Sorry this would take you out of bounds");
        else
        {
            curs->locX = curs->locX - (dist/3);
            curs->locY = curs->locY + dist;
            for (startX=startX; startX >=curs->locX; startX--)
            {
                count=0;
                for (startY=startY; startY <=curs->locY; startY++)
                {
                    if (pu == 0)
                        fill (startX, startY);
                    count++;
                    if (count==3)
                        break;
                }
            }
        }
    }
    else if (curs->dir == 8)
    {
        if (curs->locY + (dist/3) > 43 || curs->locX - dist < 1)
            mvprintw(47,1,"Sorry this would take you out of bounds");
        else
        {
            curs->locX = curs->locX - dist;
            curs->locY = curs->locY + (dist/3);
            for (startY=startY; startY <=curs->locY; startY++)
            {
                count=0;
                for (startX=startX; startX >=curs->locX; startX--)
                {
                    if (pu == 0)
                        fill (startX, startY);
                    count++;
                    if (count==3)
                        break;
                }
            }
        }
    }
    else if (curs->dir == 9)
    {
        if (curs->locX - dist < 1)
            mvprintw(47,1,"Sorry this would take you out of bounds");
        else
        {
            curs->locX = curs->locX - dist;
            for (startX=startX; startX >= curs->locX; startX--)
                if (pu == 0)
                    fill (startX,startY);
        }
    }
    else if (curs->dir == 10)
    {
        if (curs->locX - dist < 1 ||curs->locY - (dist/3) < 1)
            mvprintw(47,1,"Sorry this would take you out of bounds");
        else
        {
            curs->locX = curs->locX - dist;
            curs->locY = curs->locY - (dist/3);
            for (startY=startY; startY >=curs->locY; startY--)
            {
                count=0;
                for (startX=startX; startX >=curs->locX; startX--)
                {
                    if (pu == 0)
                        fill (startX, startY);
                    count++;
                    if (count==3)
                        break;
                }
            }
        }
    }
    else if (curs->dir ==11)
    {
        if ( curs->locX - (dist/3) < 1 ||curs->locY - dist < 1)
            mvprintw(47,1,"Sorry this would take you out of bounds");
        else
            {
            curs->locX = curs->locX - (dist/3);
            curs->locY = curs->locY - dist;
            for (startX=startX; startX >=curs->locX; startX--)
            {
                count=0;
                for (startY=startY; startY >=curs->locY; startY--)
                {
                    if (pu == 0)
                        fill (startX, startY);
                    count++;
                    if (count==3)
                        break;
                }
            }
        }
    }
    else if (curs->dir ==15)
    {
        if (curs->locX + dist > 99 ||curs->locY - dist < 1)
            mvprintw(47,1,"Sorry this would take you out of bounds");
        else
        {
            curs->locX = curs->locX + dist;
            curs->locY = curs->locY - dist;
            for (startX=startX; startX <=curs->locX; startX++)
            {
                count=0;
                for (startY=startY; startY >=curs->locY; startY--)
                {
                    if (pu == 0)
                        fill (startX, startY);
                    count++;
                    if (count==2)
                        break;
                }
            }
        }
    }
    else if (curs->dir ==45)
    {
        if (curs->locX + dist > 99 || curs->locY + dist > 43 )
            mvprintw(47,1,"Sorry this would take you out of bounds");
        else
        {
            curs->locX = curs->locX + dist;
            curs->locY = curs->locY + dist;
            for (startX=startX; startX <=curs->locX; startX++)
            {
                count=0;
                for (startY=startY; startY <=curs->locY; startY++)
                {
                    if (pu == 0)
                        fill (startX, startY);
                    count++;
                    if (count==2)
                        break;
                }
            }
        }
    }
    else if (curs->dir ==75)
    {
        if (curs->locY + dist > 43 || curs->locX - dist < 1)
            mvprintw(47,1,"Sorry this would take you out of bounds");
        else
        {
            curs->locX = curs->locX - dist;
            curs->locY = curs->locY + dist;
            for (startX=startX; startX >=curs->locX; startX--)
            {
                count=0;
                for (startY=startY; startY <=curs->locY; startY++)
                {
                    if (pu == 0)
                        fill (startX, startY);
                    count++;
                    if (count==2)
                        break;
                }
            }
        }
    }
    else if (curs->dir ==105)
    {
        if (curs->locX - dist < 1 ||curs->locY - dist < 1)
            mvprintw(47,1,"Sorry this would take you out of bounds");
        else
        {
            curs->locX = curs->locX - dist;
            curs->locY = curs->locY - dist;
            for (startX=startX; startX >=curs->locX; startX--)
            {
                count=0;
                for (startY=startY; startY >=curs->locY; startY--)
                {
                    if (pu == 0)
                        fill (startX, startY);
                    count++;
                    if (count==2)
                        break;
                }
            }
        }
    }
    else
    {
    }
}

void back (cursorT * curs, int dist, int pu)
{
    int count=0;
    int startX = curs->locX;
    int startY = curs->locY;
    if (curs->color ==1)
        attron (COLOR_PAIR(3));
    else if (curs->color ==2)
        attron (COLOR_PAIR(4));
    else if (curs->color ==3)
        attron (COLOR_PAIR(5));
    else if (curs->color ==4)
        attron (COLOR_PAIR(6));
    else
        attron (COLOR_PAIR(1));
    mvaddch (curs->locY,curs->locX,' ');
    if (curs->dir==0)
    {
        curs->locY = curs->locY + dist;
        for (startY=startY; startY <= curs->locY; startY++)
            if (pu == 0)
                fill (startX, startY);
    }
    else if (curs->dir == 1)
    {
        curs->locX = curs->locX - (dist/3);
        curs->locY = curs->locY + dist;
        for (startX=startX; startX >=curs->locX; startX--)
        {
            count=0;
            for (startY=startY; startY <=curs->locY; startY++)
            {
                if (pu == 0)
                    fill (startX, startY);
                count++;
                if (count==3)
                    break;
            }
        }
    }
    else if (curs->dir == 2)
    {
        curs->locX = curs->locX - dist;
        curs->locY = curs->locY + (dist/3);
        for (startY=startY; startY <=curs->locY; startY++)
        {
            count=0;
            for (startX=startX; startX >=curs->locX; startX--)
            {
                if (pu == 0)
                    fill (startX, startY);
                count++;
                if (count==3)
                    break;
            }
        }
    }
    else if (curs->dir == 3)
    {
        curs->locX = curs->locX - dist;
        for (startX=startX; startX >= curs->locX;startX--)
            if (pu == 0)
                fill (startX,startY);
    }
    else if (curs->dir == 4)
    {
        curs->locX = curs->locX - dist;
        curs->locY = curs->locY - (dist/3);
        for (startY=startY; startY >=curs->locY; startY--)
        {
            count=0;
            for (startX=startX; startX >=curs->locX; startX--)
            {
                if (pu == 0)
                    fill (startX, startY);
                count++;
                if (count==3)
                    break;
            }
        }
    }
    else if (curs->dir == 5)
    {
        curs->locX = curs->locX - (dist/3);
        curs->locY = curs->locY - dist;
        for (startX=startX; startX >=curs->locX; startX--)
        {
            count=0;
            for (startY=startY; startY >=curs->locY; startY--)
            {
                if (pu == 0)
                    fill (startX, startY);
                count++;
                if (count==3)
                    break;
            }
        }
    }
    else if (curs->dir == 6)
    {
        curs->locY = curs->locY - dist;
        for (startY=startY; startY >= curs->locY; startY--)
            fill (startX,startY);
    }
    else if (curs->dir == 7)
    {
        curs->locX = curs->locX + (dist/3);
        curs->locY = curs->locY - dist;
        for (startX=startX; startX <=curs->locX; startX++)
        {
            count=0;
            for (startY=startY; startY >=curs->locY; startY--)
            {
                if (pu == 0)
                    fill (startX, startY);
                count++;
                if (count==3)
                    break;
            }
        }
    }
    else if (curs->dir == 8)
    {
        curs->locX = curs->locX + dist;
        curs->locY = curs->locY - (dist/3);
        for (startY=startY; startY >=curs->locY; startY--)
        {
            count=0;
            for (startX=startX; startX <=curs->locX; startX++)
            {
                if (pu == 0)
                    fill (startX, startY);
                count++;
                if (count==3)
                    break;
            }
        }
    }
    else if (curs->dir == 9)
    {
        curs->locX = curs->locX + dist;
        for (startX=startX; startX <= curs->locX; startX++)
            if (pu == 0)
                fill (startX,startY);
    }
    else if (curs->dir == 10)
    {
        curs->locX = curs->locX + dist;
        curs->locY = curs->locY + (dist/3);
        for (startY=startY; startY <=curs->locY; startY++)
        {
            count=0;
            for (startX=startX; startX <=curs->locX; startX++)
            {
                if (pu == 0)
                    fill (startX, startY);
                count++;
                if (count==3)
                    break;
            }
        }
    }
    else if (curs->dir ==11)
    {
        curs->locX = curs->locX + (dist/3);
        curs->locY = curs->locY + dist;
        for (startX=startX; startX <=curs->locX; startX++)
        {
            count=0;
            for (startY=startY; startY <=curs->locY; startY++)
            {
                if (pu == 0)
                    fill (startX, startY);
                count++;
                if (count==3)
                    break;
            }
        }
    }
    else if (curs->dir ==75)
    {
        curs->locX = curs->locX + dist;
        curs->locY = curs->locY - dist;
        for (startX=startX; startX <=curs->locX; startX++)
        {
            count=0;
            for (startY=startY; startY >=curs->locY; startY--)
            {
                if (pu == 0)
                    fill (startX, startY);
                count++;
                if (count==2)
                    break;
            }
        }
    }
    else if (curs->dir ==105)
    {
        curs->locX = curs->locX + dist;
        curs->locY = curs->locY + dist;
        for (startX=startX; startX <=curs->locX; startX++)
        {
            count=0;
            for (startY=startY; startY <=curs->locY; startY++)
            {
                if (pu == 0)
                    fill (startX, startY);
                count++;
                if (count==2)
                    break;
            }
        }
    }
    else if (curs->dir ==15)
    {
        curs->locX = curs->locX - dist;
        curs->locY = curs->locY + dist;
        for (startX=startX; startX >=curs->locX; startX--)
        {
            count=0;
            for (startY=startY; startY <=curs->locY; startY++)
            {
                if (pu == 0)
                    fill (startX, startY);
                count++;
                if (count==2)
                    break;
            }
        }
    }
    else if (curs->dir ==45)
    {
        curs->locX = curs->locX - dist;
        curs->locY = curs->locY - dist;
        for (startX=startX; startX >=curs->locX; startX--)
        {
            count=0;
            for (startY=startY; startY >=curs->locY; startY--)
            {
                if (pu == 0)
                    fill (startX, startY);
                count++;
                if (count==2)
                    break;
            }
        }
    }
    else
    {
    }
}

void rotateRight (cursorT * curs, int angle)
{
    if (angle == 90)
    {
        if (curs->dir == 0 || curs->dir == 3 || curs->dir==6)
            curs->dir = curs->dir+3;
        else if (curs->dir == 9)
            curs->dir =0;
	else if (curs->dir==15)
            curs->dir =45;
	else if (curs->dir==45)
            curs->dir =75;
	else if (curs->dir==75)
            curs->dir =105;
	else if (curs->dir==105)
            curs->dir =15;
    }
    if (angle == 30)
    {
        if (curs->dir >=0 && curs->dir <11)
            curs->dir = curs->dir+1;
        else if (curs->dir==11)
            curs->dir =0;
	else if (curs->dir==15)
            curs->dir =2;
	else if (curs->dir==45)
            curs->dir =5;
	else if (curs->dir==75)
            curs->dir =8;
	else if (curs->dir==105)
            curs->dir =11;
    }
    if (angle == 45)
    {
        if (curs->dir==0||curs->dir==1)
            curs->dir=15;
        else if (curs->dir==15 || curs->dir==2)
            curs->dir=3;
        else if (curs->dir==3 || curs->dir==4)
            curs->dir=45;
        else if (curs->dir==45 || curs->dir==5)
            curs->dir=6;
        else if (curs->dir==6 || curs->dir==7)
            curs->dir=75;
        else if (curs->dir==75 || curs->dir==8)
            curs->dir=9;
        else if (curs->dir==9 || curs->dir==10)
            curs->dir=105;
        else if (curs->dir==105 || curs->dir==11)
            curs->dir=0;
    }
}

void rotateLeft (cursorT * curs, int angle)
{
    if (angle == 90)
    {
        if (curs->dir == 9 || curs->dir == 3 || curs->dir==6)
            curs->dir = curs->dir-3;
        else if (curs->dir == 0)
            curs->dir =9;
	else if (curs->dir==15)
            curs->dir =105;
	else if (curs->dir==45)
            curs->dir =15;
	else if (curs->dir==75)
            curs->dir =45;
	else if (curs->dir==105)
            curs->dir =75;
    }
    if (angle == 30)
    {
        if (curs->dir >0 && curs->dir <=11)
            curs->dir = curs->dir-1;
        else if (curs->dir==0)
            curs->dir =11;
	else if (curs->dir==15)
            curs->dir =1;
	else if (curs->dir==45)
            curs->dir =4;
	else if (curs->dir==75)
            curs->dir =7;
	else if (curs->dir==105)
            curs->dir =10;
    }
    if (angle == 45)
    {
        if (curs->dir==0||curs->dir==11)
            curs->dir=105;
        else if (curs->dir==105 || curs->dir==10)
            curs->dir=9;
        else if (curs->dir==9 || curs->dir==8)
            curs->dir=75;
        else if (curs->dir==75 || curs->dir==7)
            curs->dir=6;
        else if (curs->dir==6 || curs->dir==5)
            curs->dir=45;
        else if (curs->dir==45 || curs->dir==4)
            curs->dir=3;
        else if (curs->dir==3 || curs->dir==12)
            curs->dir=15;
        else if (curs->dir==15 || curs->dir==1)
            curs->dir=0;
    }
}

void fill (int locX, int locY)
{
    mvaddch (locY, locX, '#');
}

void clean(void)
{
    int x =0;
    int y =0;
    for (x=1;x<100;x++)
        for (y=1;y<44;y++)
            mvaddch (y,x,' ');
}


