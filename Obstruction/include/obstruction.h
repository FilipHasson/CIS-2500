#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_NAME 40
#define BOARD_SIZE 6
#define SCREEN_HEIGHT 48
#define SCREEN_WIDTH 96
#define BORDER '#'
#define COL_SIZE 16
#define ROW_SIZE 8

/*CONTROLS*/
#define KEY_QUIT 'q'
#define OB_KEY_UP 'i'
#define OB_KEY_DOWN 'k'
#define OB_KEY_LEFT 'j'
#define OB_KEY_RIGHT 'l'
#define OB_KEY_ENTER 'e'

#define CHAR_SELECTION '@'

#define OB_SAVE_FILE "ob.sav"

int play(bool ai);
void getPlayerNames(char**p1, char**p2);
void printUI(void);
void drawScreen(int **board);
int** initBoard();
void updateSelection(int row, int col, char c);
void printSelectedBox(int row, int col);
void clearSelection(int row, int col);
void drawX(int row, int col);
void drawO(int row, int col);
void drawBlock(int row, int col);
bool compareChNoCase(char a, char b);
int countSpaces(int **board);
void aiTurn(int **board);
void updateBoard(int **board, bool playerOne, int y, int x);
