#include "obstruction.h"

int main(int argc, char**argv) {
    bool ai = FALSE;
    int winner = 0;
    char **players = malloc(sizeof(char*)*2);
    for (int i = 0; i < 2; i++)
        players[i] = malloc(sizeof(char)*MAX_NAME);

    /*Init ncruses */
    initscr();
    start_color();

    /*Set Up Color Pairs*/
    init_pair(1, COLOR_WHITE,COLOR_BLACK);
    init_pair(2, COLOR_RED,COLOR_BLACK);
    init_pair(3, COLOR_BLUE,COLOR_BLACK);
    attron(COLOR_PAIR(1));

    getPlayerNames(&players[0],&players[1]);
    if (!strcmp(players[1],"EDI")) ai=TRUE;

    cbreak();
    noecho();

    printUI();
    winner = play(ai);

    attron(COLOR_PAIR(1));
    if (!winner) mvprintw (55,20,"Game Terminated, It's a draw!");
    else mvprintw (55,20,"Congradulations %s!",players[winner-1]);
    refresh();
    getch();

    endwin();
    for (int i = 0; i < 2; i++)
        free(players[i]);
    free(players);

    return 0;
}

int play(bool ai){
    bool pOneTurn = TRUE;
    int **board = initBoard();
    int x = 0;
    int y = 0;
    int input = 0;
    
    drawScreen(board);

    while (!compareChNoCase(input,KEY_QUIT)){   
        if (pOneTurn) attron(COLOR_PAIR(2));
        else attron(COLOR_PAIR(3));

        printSelectedBox(y,x);

        if (!pOneTurn && ai){
            clearSelection(y,x);
            aiTurn(board);
            drawScreen(board);
            if (!countSpaces(board)) break;
            pOneTurn = !pOneTurn;
            continue;
        }

        input = getch();
        if (compareChNoCase(input,OB_KEY_UP)){
            clearSelection(y,x);
            if (y-1 >= 0) y--;
            printSelectedBox(y,x);
        } else if (compareChNoCase(input,OB_KEY_DOWN)) {
            clearSelection(y,x);
            if (y+1 < BOARD_SIZE) y++;
            printSelectedBox(y,x);
        } else if (compareChNoCase(input,OB_KEY_LEFT)) {
            clearSelection(y,x);
            if (x-1 >= 0) x--;
            printSelectedBox(y,x);
        } else if (compareChNoCase(input,OB_KEY_RIGHT)) {
            clearSelection(y,x);
            if (x+1 < BOARD_SIZE) x++;
            printSelectedBox(y,x);
        } else if (compareChNoCase(input,OB_KEY_ENTER)) {
            if(!board[y][x]){
                updateBoard(board,pOneTurn,y,x);
                if (!countSpaces(board)) break;  
                pOneTurn = !pOneTurn;
            }
        }
        drawScreen(board);
    }


    drawScreen(board);

    for (int i = 0; i < BOARD_SIZE; i++) free(board[i]);
    free(board);
    if (compareChNoCase(input,KEY_QUIT)) return 0;
    if (pOneTurn) return 1;
    return 2;
}

void drawScreen(int **board){
    attron(COLOR_PAIR(1));
    for (int i = 0; i <= SCREEN_WIDTH; i++){
        mvaddch (0, i, BORDER);
        mvaddch (ROW_SIZE, i, BORDER);
        mvaddch (ROW_SIZE*2, i, BORDER);
        mvaddch (ROW_SIZE*3, i, BORDER);
        mvaddch (ROW_SIZE*4, i, BORDER);
        mvaddch (ROW_SIZE*5, i, BORDER);
        mvaddch (SCREEN_HEIGHT, i, BORDER);
    }

    for (int i = 0; i <= SCREEN_HEIGHT; i++){
        mvaddch (i, 0, BORDER);
        mvaddch (i, COL_SIZE, BORDER);
        mvaddch (i, COL_SIZE*2, BORDER);
        mvaddch (i, COL_SIZE*3, BORDER);
        mvaddch (i, COL_SIZE*4, BORDER);
        mvaddch (i, COL_SIZE*5, BORDER);
        mvaddch (i, SCREEN_WIDTH, BORDER);
    }

    for (int i = 0; i <BOARD_SIZE ; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if (board[j][i] == 2){
                attron(COLOR_PAIR(3));
                drawO(j,i);
            } else if (board[j][i] == 1){
                attron(COLOR_PAIR(2));
                drawX(j,i);            
            } else if (board[j][i] == 3){
                attron(COLOR_PAIR(1));
                drawBlock (j,i);
            }
        }
    }

    refresh();
}

int countSpaces(int **board){
    int emptySpaces = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (board[i][j] == 0) emptySpaces++;

    return emptySpaces;
}

void updateBoard(int **board, bool playerOne, int y, int x){
    if (playerOne) board[y][x] = 1;
    else board[y][x] = 2;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if(y+i >= 0 && x+j >= 0 && y+i < BOARD_SIZE && x+j < BOARD_SIZE)
                if(board[y+i][x+j] == 0) board[y+i][x+j] = 3;
}

void aiTurn(int **board){
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j <BOARD_SIZE; j++){
            if(!board[i][j]){
                updateBoard(board,FALSE,i,j);
                drawScreen(board);
                return;
            }
        }
    }
}

void updateSelection(int row, int col, char c){
    int x = COL_SIZE*(col+1) - (COL_SIZE-1);
    int y = ROW_SIZE*(row+1) - (ROW_SIZE-1);
    for (int i = 0; i < (COL_SIZE-1); i++){
        mvaddch (y, x+i, c);
        mvaddch (y+(ROW_SIZE-2), x+i, c);
    }

    for (int i=0;i<(ROW_SIZE-1);i++)
    {
        mvaddch (y+i, x, c);
        mvaddch (y+i, x+COL_SIZE-2, c);
    }
}

void clearSelection (int row, int col){
    updateSelection(row, col, ' ');
}

void printSelectedBox (int row, int col){
    updateSelection(row, col, CHAR_SELECTION);
}

void printUI (void){
    mvprintw(50,0,"Movement Keys:");
    mvprintw(51,15,"  I  ");
    mvprintw(52,15,"J K L");
    mvprintw(50,25,"Place Letter:");
    mvprintw(51,40,"E");
    mvprintw(50,50,"Quit:");
    mvprintw(51,57,"Q");
}

int** initBoard(){
    int **board = malloc(sizeof(int*)*BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++){
        board[i]=malloc(sizeof(int)*BOARD_SIZE);
        for (int j = 0; j < BOARD_SIZE; j++) board[i][j]=0;
    }

    return board;
}

void getPlayerNames(char**p1, char**p2){
    mvprintw(10,20,"Enter a name for player one (max length of %d characters): ",MAX_NAME);
    getstr(*p1);
    clear();
    mvprintw(8,20,"Enter the name EDI to face the AI!");
    mvprintw(10,20,"Enter a name for player two (max length of %d characters): ",MAX_NAME);
    getstr(*p2);
    clear();
}

void drawX (int row, int col){
    int x = (COL_SIZE*(col+1)-(COL_SIZE-1))+1;
    int y = (ROW_SIZE*(row+1)-(ROW_SIZE-1))+1;

    mvaddstr (y, x, "XXX       XXX");
    mvaddstr (y+1,x,"  XXX   XXX");
    mvaddstr (y+2,x,"     XXX");
    mvaddstr (y+3,x,"  XXX   XXX");
    mvaddstr (y+4,x,"XXX       XXX");
}

void drawO (int row, int col){
    int x = (COL_SIZE*(col+1)-(COL_SIZE-1))+1;
    int y = (ROW_SIZE*(row+1)-(ROW_SIZE-1))+1;

    mvaddstr (y, x, "   OOOOOOO");
    mvaddstr (y+1,x," OOO     OOO");
    mvaddstr (y+2,x,"OOO       OOO");
    mvaddstr (y+3,x," OOO     OOO");
    mvaddstr (y+4,x,"   OOOOOOO");
}

void drawBlock (int row, int col){
    int x = (COL_SIZE*(col+1)-(COL_SIZE-1))+1;
    int y = (ROW_SIZE*(row+1)-(ROW_SIZE-1))+1;
    
    for (int i = 0; i < 5; i++) mvaddstr (y+i, x, "-------------");
}

bool compareChNoCase(char a, char b){
    a = tolower(a);
    b = tolower(b);
    if (a == b) return TRUE;
    return FALSE;
}