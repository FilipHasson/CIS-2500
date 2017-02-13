/*************************parse.c****************************
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

void removeNewline (char buf[150])
{
    buf[strlen(buf)-1]='\0';
}

room parseFunc (char buffer[150], int roomNum, playerSt* hero, monsters* mon, int devFlag, int* tMon)
{
    int n =0;
    int m =0;
    int y =0;
    room myRoom;
    char* buf2=malloc(sizeof(char)*11);
    char* buf3=malloc(sizeof(char)*7);
    int *index=NULL;
    int *in2=NULL;
    index =&n;
    in2 =&m;
    *index=0;
    *in2=0;
    myRoom = blankRoom(myRoom);
    if (devFlag > 0)
    {
        printf("___________________________________________________________\n");
        printf("%s\n",buffer);
    }
    //get length
    *buf2 = *getSeg(buffer, index, buf2, 'X');
    myRoom.length = atoi(buf2);
    buf2[0]='\0';
    //get width
    *buf2 =*getSeg(buffer, index, buf2,' ');
    myRoom.width = atoi(buf2);
    buf2[0]='\0';
    removeNewline(buf2);
    if (devFlag > 0)
        printf("Room    #%d | length=       %d | width=  %d |\n",roomNum,myRoom.length,myRoom.width);
    while (buffer[*index] != '\0' && *index < 150)
    {
        buf2 = getSeg(buffer,index,buf2,' ');
        if (buf2[0]=='d')//DOOR
        {
            myRoom.doors[myRoom.dCnt].wall = buf2[1];
            for (y=0;y<strlen(buf2)-2;y++)
                buf2[y]=buf2[y+2];
            buf2[y+1]='\0';
            if (atoi(buf2)>99)
                buf2[y]='\0';
            myRoom.doors[myRoom.dCnt].dist = atoi(buf2);
            if (myRoom.doors[myRoom.dCnt].wall == 'e' || myRoom.doors[myRoom.dCnt].wall == 'w')
                if (myRoom.doors[myRoom.dCnt].dist >= myRoom.length)
                    myRoom.doors[myRoom.dCnt].dist = myRoom.length-1;
            if (myRoom.doors[myRoom.dCnt].wall == 'n' || myRoom.doors[myRoom.dCnt].wall == 's')
                if (myRoom.doors[myRoom.dCnt].dist >= myRoom.width)
                    myRoom.doors[myRoom.dCnt].dist = myRoom.width-1;
            if (devFlag > 0)
                printf("Door    #%d | door: Wall=   %c | Dist=   %d |\n",myRoom.dCnt,myRoom.doors[myRoom.dCnt].wall,myRoom.doors[myRoom.dCnt].dist);
            myRoom.doors[myRoom.dCnt].room=roomNum;
            myRoom.dCnt++;
            if (myRoom.doors[myRoom.dCnt-1].dist > 9)
                buf2[y]='\0';
        }
        else if (buf2[0]=='s')//STAIRS!
        {
            *buf2 = *remCh(buf2);
            *buf3 = *getSeg(buf2,in2,buf3,',');
            myRoom.stairs[myRoom.sCnt].room=roomNum;
            myRoom.stairs[myRoom.sCnt].locY=atoi(buf3);
            *buf2 = *splitCom (buf2,atoi(buf3));
            *buf3 = *getSeg(buf2,in2,buf3,'\n');
            myRoom.stairs[myRoom.sCnt].locX=atoi(buf3);
            myRoom.stairs[myRoom.sCnt].targetLevel=myRoom.sCnt+1;
            if (devFlag > 0)
            {
                printf("Stair   #%d | stair: room=  %d | loc = %d,%d | targetLevel = %d |\n",myRoom.sCnt,myRoom.stairs[myRoom.sCnt].room,
                myRoom.stairs[myRoom.sCnt].locY,myRoom.stairs[myRoom.sCnt].locX,myRoom.stairs[myRoom.sCnt].targetLevel);
            }
            myRoom.sCnt++;
        }
        else if (buf2[0]=='g')//GOLD!
        {
            myRoom.rmItem[myRoom.iCnt]=createGold(buf2, buf3, in2,roomNum);
            if (devFlag > 0)
            {
                printf("itemNum #%d | item: name=   %s | loc = %d,%d | value = %d|\n",myRoom.iCnt,myRoom.rmItem[myRoom.iCnt].name,
                myRoom.rmItem[myRoom.iCnt].locY,myRoom.rmItem[myRoom.iCnt].locX,myRoom.rmItem[myRoom.iCnt].value);
            }
            myRoom.iCnt++;
        }
        else if (buf2[0]=='m')//magic!
        {
            myRoom.rmItem[myRoom.iCnt]=createMagic(buf2, buf3, in2,roomNum);
            if (devFlag > 0)
            {
                printf("itemNum #%d | item: %s | loc = %d,%d |\n",myRoom.iCnt,myRoom.rmItem[myRoom.iCnt].name,
                myRoom.rmItem[myRoom.iCnt].locY,myRoom.rmItem[myRoom.iCnt].locX);
            }
            myRoom.iCnt++;
        }

        else if (buf2[0]=='p')//POTION
        {
            myRoom.rmItem[myRoom.iCnt]=createPotion(buf2, buf3, in2,roomNum);
            if (devFlag > 0)
            {
                printf("itemNum #%d | item: %s | loc = %d,%d |\n",myRoom.iCnt,myRoom.rmItem[myRoom.iCnt].name,
                myRoom.rmItem[myRoom.iCnt].locY,myRoom.rmItem[myRoom.iCnt].locX);
            }
            myRoom.iCnt++;
        }
        else if (buf2[0]=='w')//WEAPON
        {
            myRoom.rmItem[myRoom.iCnt]=createWeapon(buf2, buf3, in2,roomNum);
            if (devFlag > 0)
            {
                printf("itemNum #%d | %s%s: loc = %d,%d | str =   %d | \n",myRoom.iCnt,myRoom.rmItem[myRoom.iCnt].wepType,
                myRoom.rmItem[myRoom.iCnt].name,
                myRoom.rmItem[myRoom.iCnt].locY,myRoom.rmItem[myRoom.iCnt].locX,
                myRoom.rmItem[myRoom.iCnt].wepStrModifier);
            }
            myRoom.iCnt++;
        }
        else if (buf2[0]=='M')//MONSTER
        {
            mon[tMon[0]].startRoom=roomNum;
            *buf2 = *remCh(buf2);
            *buf3 = *getSeg(buf2,in2,buf3,',');
            mon[tMon[0]].rLocY=atoi(buf3);
            *in2=0;
            *buf3 = *getSeg(buf2,in2,buf3,'\n');
            if (atoi(buf3)>9)
                for (y=0;y<3;y++)
                    remCh(buf3);
            else
                for (y=0;y<2;y++)
                    remCh(buf3);
            mon[tMon[0]].rLocX=atoi(buf3);
            myRoom.monX[myRoom.mCnt]=mon[tMon[0]].rLocX;
            myRoom.monY[myRoom.mCnt]=mon[tMon[0]].rLocY;
            y=genNum(110);
            if (y < 40)
            {
                strcpy(mon[tMon[0]].name, "Snake");
                mon[tMon[0]].hp = 15;
                mon[tMon[0]].damage = 3;
                mon[tMon[0]].type = 'S';
                mon[tMon[0]].monNum =tMon[0];
                mon[tMon[0]].xpBoost = 5;
                myRoom.monT[myRoom.mCnt]='S';
                myRoom.monNT[myRoom.mCnt]=1;
            }
            else if (y < 70)
            {
                strcpy(mon[tMon[0]].name, "Bat");
                mon[tMon[0]].hp = 20;
                mon[tMon[0]].damage = 4;
                mon[tMon[0]].type = 'B';
                mon[tMon[0]].monNum =tMon[0];
                mon[tMon[0]].xpBoost = 7;
                myRoom.monT[myRoom.mCnt]='B';
                myRoom.monNT[myRoom.mCnt]=2;
            }
            else if (y < 90)
            {
                strcpy(mon[tMon[0]].name, "Giant Rat");
                mon[tMon[0]].hp = 25;
                mon[tMon[0]].damage = 5;
                mon[tMon[0]].type = 'R';
                mon[tMon[0]].monNum =tMon[0];
                mon[tMon[0]].xpBoost = 13;
                myRoom.monT[myRoom.mCnt]='R';
                myRoom.monNT[myRoom.mCnt]=3;
            }
            else if (y < 100)
            {
                strcpy(mon[tMon[0]].name, "Goblin");
                mon[tMon[0]].hp = 30;
                mon[tMon[0]].damage = 9;
                mon[tMon[0]].type = 'G';
                mon[tMon[0]].monNum =tMon[0];
                mon[tMon[0]].xpBoost = 25;
                myRoom.monT[myRoom.mCnt]='G';
                myRoom.monNT[myRoom.mCnt]=4;
            }
            else if (y < 107)
            {
                strcpy(mon[tMon[0]].name, "Orc");
                mon[tMon[0]].hp = 50;
                mon[tMon[0]].damage = 15;
                mon[tMon[0]].type = 'O';
                mon[tMon[0]].monNum =tMon[0];
                mon[tMon[0]].xpBoost = 50;
                myRoom.monT[myRoom.mCnt]='O';
                myRoom.monNT[myRoom.mCnt]=5;
            }
            else
            {
                strcpy(mon[tMon[0]].name, "Corrupt Elf");
                mon[tMon[0]].hp = 90; mon[tMon[0]].damage = 30;
                mon[tMon[0]].type = 'E'; mon[tMon[0]].monNum =tMon[0];
                mon[tMon[0]].xpBoost = 80; myRoom.monT[myRoom.mCnt]='E';
                myRoom.monNT[myRoom.mCnt]=6;
            }
            if (devFlag > 0)
            {
                printf ("Monster #%d\t| %s   \t|startLoc    %d,%d\t| HP:  %d | Dmg: %d |\n",tMon[0], mon[tMon[0]].name,
                mon[tMon[0]].rLocY,mon[tMon[0]].rLocX,mon[tMon[0]].hp,mon[tMon[0]].damage);
            }
            tMon[0]++;
            myRoom.mCnt++;
        }
        else if (buf2[0]=='h')//hero
        {
            if (roomNum ==0)
            {
                *buf2 = *remCh(buf2);
                *buf3 = *getSeg(buf2,in2,buf3,',');
                hero->locY=atoi(buf3);
                *in2=0;
                *buf3 = *getSeg(buf2,in2,buf3,'\n');
                if (atoi(buf3)>9)
                    for (y=0;y<3;y++)
                        remCh(buf3);
                else
                    for (y=0;y<2;y++)
                        remCh(buf3);
                hero->locX=atoi(buf3);
            }
            if (devFlag > 0)
                printf ("HERO: %d,%d | lvl %d | hp %d | str %d | acc %d |\n",hero->locY,hero->locX,hero->level,hero->hp,hero->str,hero->acc);
        }
        *in2=0;
    }
    free(buf2);
    free(buf3);
    if (myRoom.dCnt==0)
    {
        myRoom.doors[0].wall='e';
        myRoom.doors[0].dist=0;
        myRoom.dCnt++;
    }
    return myRoom;
}

roomItem createGold (char* buf2, char* buf3, int* in2, int roomNum)
{
    int y=0;
    roomItem myGold;
    *buf2 = *remCh(buf2);
    *buf3 = *getSeg(buf2,in2,buf3,',');
    myGold.locY=atoi(buf3);
    *in2=0;
    *buf3 = *getSeg(buf2,in2,buf3,'\n');
    if (atoi(buf3)>9)
        for (y=0;y<3;y++)
            remCh(buf3);
    else
        for (y=0;y<2;y++)
            remCh(buf3);
    myGold.locX=atoi(buf3);
    myGold.type = 'g';
    y = genNum (100);
    if (y < 50)
        y=genNum(55)+20;
    else if (y < 80)
        y=genNum (90)+60;
    else
        y=genNum (150)+100;
    myGold.value=y;
    strcpy(myGold.name, "Gold");
    return(myGold);
}

roomItem createPotion (char* buf2, char* buf3, int* in2, int roomNum)
{
    int y=0;
    roomItem myPotion;
    *buf2 = *remCh(buf2);
    *buf3 = *getSeg(buf2,in2,buf3,',');
    myPotion.room=roomNum;
    myPotion.locY=atoi(buf3);
    *in2=0;
    *buf3 = *getSeg(buf2,in2,buf3,'\n');
    if (atoi(buf3)>9)
        for (y=0;y<3;y++)
            remCh(buf3);
    else
        for (y=0;y<2;y++)
            remCh(buf3);
    myPotion.locX=atoi(buf3);
    myPotion.type = 'p';
    y = genNum (100);
    if (y < 70)
    {
        y=genNum(100);
        if (y < 50)
        {
            strcpy(myPotion.name, "Minor Health Potion");
            myPotion.potHealth = 10;
            myPotion.potStrModifier = 0;
            myPotion.potDuration = 0;
        }
        else if (y < 75)
        {
            strcpy(myPotion.name, "Lesser Health Potion");
            myPotion.potHealth = 15;
            myPotion.potStrModifier = 0;
            myPotion.potDuration = 0;
        }
        else if (y < 85)
        {
            strcpy(myPotion.name, "Greater Health Potion");
            myPotion.potHealth = 20;
            myPotion.potStrModifier = 0;
            myPotion.potDuration = 0;
        }
        else
        {
            strcpy(myPotion.name, "Major Health Potion");
            myPotion.potHealth = 40;
            myPotion.potStrModifier = 0;
            myPotion.potDuration = 0;
        }
    }
    else
    {
        y=genNum (100);
        if (y < 50)
        {
            strcpy(myPotion.name, "Minor Potion of Strength");
            myPotion.potHealth = 0;
            myPotion.potStrModifier = 5;
            myPotion.potDuration = 20;
        }
        else if (y < 75)
        {
            strcpy(myPotion.name, "Lesser Potion of Strength");
            myPotion.potHealth = 0;
            myPotion.potStrModifier = 10;
            myPotion.potDuration = 40;
        }
        else if (y < 85)
        {
            strcpy(myPotion.name, "Potion of Strength");
            myPotion.potHealth = 0;
            myPotion.potStrModifier = 15;
            myPotion.potDuration = 60;
        }
        else
        {
            strcpy(myPotion.name, "Greater Potion of Strength");
            myPotion.potHealth = 0;
            myPotion.potStrModifier = 25;
            myPotion.potDuration = 80;
        }
    }
    return(myPotion);
}

roomItem createMagic (char* buf2, char* buf3, int* in2, int roomNum)
{
    int y=0;
    roomItem myMagic;
    *buf2 = *remCh(buf2);
    *buf3 = *getSeg(buf2,in2,buf3,',');
    myMagic.room=roomNum;
    myMagic.locY=atoi(buf3);
    *in2=0;
    *buf3 = *getSeg(buf2,in2,buf3,'\n');
    if (atoi(buf3)>9)
        for (y=0;y<3;y++)
            remCh(buf3);
    else
        for (y=0;y<2;y++)
            remCh(buf3);
    myMagic.locX=atoi(buf3);
    myMagic.type = 'm';
    y = genNum (100);
    if (y < 70)
    {
        y=genNum(100);
        if (y < 50)
        {
            strcpy(myMagic.name, "Minor Health Enchant");
            myMagic.magHpModifier = 5;
            myMagic.magStrModifier = 0;
        }
        else if (y < 75)
        {
            strcpy(myMagic.name, "Lesser Health Enchant");
            myMagic.magHpModifier = 10;
            myMagic.magStrModifier = 0;
        }
        else if (y < 85)
        {
            strcpy(myMagic.name, "Greater Health Enchant");
            myMagic.magHpModifier = 16;
            myMagic.magStrModifier = 0;
        }
        else
        {
            strcpy(myMagic.name, "Major Health Enchant");
            myMagic.magHpModifier = 22;
            myMagic.magStrModifier = 0;
        }
    }
    else
    {
        y=genNum (100);
        if (y < 50)
        {
            strcpy(myMagic.name, "Minor Strength Enchant");
            myMagic.magHpModifier = 0;
            myMagic.magStrModifier = 2;
        }
        else if (y < 75)
        {
            strcpy(myMagic.name, "Lesser Strength Enchant");
            myMagic.magHpModifier = 0;
            myMagic.magStrModifier = 4;
        }
        else if (y < 85)
        {
            strcpy(myMagic.name, "Strength Enchant");
            myMagic.magHpModifier = 0;
            myMagic.magStrModifier = 7;
        }
        else
        {
            strcpy(myMagic.name, "Greater Strength Enchant");
            myMagic.magHpModifier = 0;
            myMagic.magStrModifier = 10;
        }
    }
    return(myMagic);
}

roomItem createWeapon (char* buf2, char* buf3, int* in2, int roomNum)
{
    int y=0;
    int x=0;
    int baseDmg=0;
    roomItem myWeapon;
    *buf2 = *remCh(buf2);
    *buf3 = *getSeg(buf2,in2,buf3,',');
    myWeapon.room=roomNum;
    myWeapon.locY=atoi(buf3);
    *in2=0;
    *buf3 = *getSeg(buf2,in2,buf3,'\n');
    if (atoi(buf3)>9)
        for (y=0;y<3;y++)
            remCh(buf3);
    else
        for (y=0;y<2;y++)
            remCh(buf3);
    myWeapon.locX=atoi(buf3);
    myWeapon.type = 'w';
    //Generate Weapon specs
    y = genNum(110);
    if (y < 25)     ///1.dagger
    {
        baseDmg=1;
        strcpy(myWeapon.name," Dagger");
        myWeapon.wType = 1;
    }
    else if (y < 45)///2.short sword
    {
        baseDmg=2;
        strcpy(myWeapon.name," Short Sword");
        myWeapon.wType = 2;
    }
    else if (y < 55)///3.long sword
    {
        baseDmg=4;
        strcpy(myWeapon.name," Long Sword");
        myWeapon.wType = 3;
    }
    else if (y < 60)///4.claymore
    {
        baseDmg=5;
        strcpy(myWeapon.name," Claymore");
        myWeapon.wType = 4;
    }
    else if (y < 75)///5.war axe
    {
        baseDmg=3;
        strcpy(myWeapon.name," War Axe");
        myWeapon.wType = 5;
    }
    else if (y < 80)///6.battle axe
    {
        baseDmg=5;
        strcpy(myWeapon.name," Battle Axe");
        myWeapon.wType = 6;
    }
    else if (y < 95)///7.mace
    {
        baseDmg=3;
        strcpy(myWeapon.name," Mace");
        myWeapon.wType = 7;
    }
    else if (y < 100)//8.war hammer
    {
        baseDmg=5;
        strcpy(myWeapon.name," War Hammer");
        myWeapon.wType = 8;
    }
    else // (y < 110)//9.spear
    {
        baseDmg=4;
        strcpy(myWeapon.name," Spear");
        myWeapon.wType = 9;
    }
    x = genNum(100);
    if (x < 40)////////1.Iron
    {
        myWeapon.wepStrModifier=baseDmg;
        strcpy(myWeapon.wepType, "Iron");
        myWeapon.wMat = 1;
    }
    else if (x < 65)///2.Steel
    {
        myWeapon.wepStrModifier=baseDmg*2;
        strcpy(myWeapon.wepType, "Steel");
        myWeapon.wMat = 2;
    }
    else if (x < 85)///3.Silver
    {
        myWeapon.wepStrModifier=baseDmg*3;
        strcpy(myWeapon.wepType, "Silver");
        myWeapon.wMat = 3;
    }
    else if (x < 95)///4.Orcish
    {
        myWeapon.wepStrModifier=baseDmg*4;
        strcpy(myWeapon.wepType, "Orcish");
        myWeapon.wMat = 4;
    }
    else // (y < 100)//5.Elvish
    {
        myWeapon.wepStrModifier=baseDmg*5;
        strcpy(myWeapon.wepType, "Elvish");
        myWeapon.wMat = 5;
    }
    return(myWeapon);
}

int genNum(int max)
{
    int x;
    x= rand()%max;
    return(x);
}

char* remCh (char* buf2)
{
    int y;
    for (y=0;y<strlen(buf2);y++)
        buf2[y]=buf2[y+1];
    buf2[y+1]='\0';
    return (buf2);
}

char* splitCom (char* buf2, int len)
{
    int y=0;
    if (len>9)
        for (y=0;y<strlen(buf2)-3;y++)
            buf2[y]=buf2[y+3];
    else
        for (y=0;y<strlen(buf2)-2;y++)
            buf2[y]=buf2[y+2];
    return (buf2);
}

char* getSeg (char buff[150],int*index,char* buf2,char sepUnit)
{
    int sp=0;
    int ep=0;
    int y=0;
    sp=*index;
    while (buff[*index]!=sepUnit && *index < 150 && buff[*index] !='\0')
    {
        ep=*index;
        *index=*index+1;
    }
    ep=ep-sp+1;
    for (y=0;y<ep;y++)
    {
        buf2[y]=buff[sp+y];
    }
    buf2[y]='\0';
    *index=*index+1;
    return (buf2);
}
