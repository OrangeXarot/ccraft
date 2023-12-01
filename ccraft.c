#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HEIGHT 30
#define WIDTH 127

#define UP_ARROW 65
#define DOWN_ARROW 66
#define RIGHT_ARROW 67
#define LEFT_ARROW 68
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define RED "\e[1;31m"
#define GRN "\e[1;32m"
#define YEL "\e[1;33m"
#define BLU "\e[1;34m"
#define MAG "\e[1;35m"
#define CYN "\e[1;36m"


char map[HEIGHT][WIDTH];
char pChar = 'O';
char blocks[] = {'#', '$', '/', '\\', '|', '[', ']', '-', '+', '=', '<', '>'};
int totBlocks = sizeof(blocks)/sizeof(blocks[0]);
int idxBlocks = 0;
char bChar;
char cChar = ' ';
char input;
int x, y;
char color[9];
char reset[] = "\e[0m";

void init_color();
void splash();
void setup();
void printScreen();
void movement();

void init_color() {
  srand(time(NULL));
  int random = rand() % 6;
  switch(random) {
    case 0:
      strcpy(color, RED);
      break;
    case 1:
      strcpy(color, GRN);
      break;
    case 2:
      strcpy(color, YEL);
      break;
    case 3:
      strcpy(color, BLU);
      break;
    case 4:
      strcpy(color, MAG);
      break;
    case 5:
      strcpy(color, CYN);
      break;
  }

}

void splash() {

  printf("\e[?25l\b \n%s ________                ________  ________  ________  ________ __________\n", color);
  printf("|\\   ____\\              |\\   ____\\|\\   __  \\|\\   __  \\|\\  _____\\\\___   ___\\\n");
  printf("\\ \\  \\___|  ____________\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\__/\\|___ \\  \\_|\n");
  printf(" \\ \\  \\    |\\____________\\ \\  \\    \\ \\   _  _\\ \\   __  \\ \\   __\\    \\ \\  \\  \n");
  printf("  \\ \\  \\___\\|____________|\\ \\  \\____\\ \\  \\\\  \\\\ \\  \\ \\  \\ \\  \\_|     \\ \\  \\ \n");
  printf("   \\ \\_______\\             \\ \\_______\\ \\__\\\\ _\\\\ \\__\\ \\__\\ \\__\\       \\ \\__\\\n");
  printf("    \\|_______|              \\|_______|\\|__|\\|__|\\|__|\\|__|\\|__|        \\|__| %s2.4\t\t\t  Made by %sOrangeXarot%s\n\n", reset, color, reset);
}

void setup() {
  for(int i = 0; i < HEIGHT; i++) {
    for(int j = 0; j < WIDTH; j++) {
      map[i][j] = ' ';
    }
  }

  x = WIDTH/2;
  y = HEIGHT/2;
  map[y][x] = pChar;
  bChar = blocks[0];
}

void printScreen() {
  system("/bin/stty cooked");
  system("clear");
  splash();
  for(int i = 0; i < HEIGHT; i++) {
    for(int j = 0; j < WIDTH; j++) {
      if(i == 0 && j == 0) printf("╭");
      else if(i == 0 && j == WIDTH-1)
        printf("╮");
      else if(i == HEIGHT-1 && j == 0)
        printf("╰");
      else if(i == HEIGHT-1 && j == WIDTH-1)
        printf("╯");
      else if(i == 0 || i == HEIGHT-1)
        printf("─");
      else if(j == 0 || j == WIDTH-1)
        printf("│");
      else if(map[i][j] == 'O')
        printf("%sO%s", color, reset);
      else
        printf("%c", map[i][j]);
    }
    printf("\n");
  }


  printf(" Movement: %sw a s d%s  |  Build and Destroy: %sarrows%s  |  Change Block: %sc v%s  |  Custom Block: %s?%s  |  Quit: %sq%s\t\t  X: %s%d%s Y: %s%d%s\n", color, reset, color, reset, color, reset, color, reset, color, reset, color, x, reset, color, y, reset);
  printf(" Blocks: %s", color);

  for(int i = 0; i < totBlocks; i++) {
    printf(" ");
    if(idxBlocks == i && bChar != cChar) printf("\e[7m");
    printf("%c", blocks[i]);
    printf("\e[27m");
  } 
  printf("%s", reset);
  if(cChar != ' ') {
    if(bChar == cChar)
      printf(" | \e[7m%s%c%s\e[27m", color, cChar, reset);
    else 
      printf(" | %s%c%s", color, cChar, reset);
  }
  printf("\n");
  system("/bin/stty raw");

}


void movement() {
  input = getchar();
  map[y][x] = ' ';
  switch(input) {
    case 'a':
      x--;
      if(x == 0 || map[y][x] != ' ')
        x++;
      break;
    case 'd':
      x++;
      if(x == WIDTH-1 || map[y][x] != ' ')
        x--;
      break;
    case 'w':
      y--;
      if(y == 0 || map[y][x] != ' ')
        y++;
      break;
    case 's':
      y++;
      if(y == HEIGHT-1 || map[y][x] != ' ')
        y--;
      break;
    case 'v':
      idxBlocks++;
      if(idxBlocks > totBlocks - 1 || cChar == bChar) 
        idxBlocks = 0;
      cChar = ' ';
      bChar = blocks[idxBlocks];
      break;
    case 'c':
      idxBlocks--;
      if(idxBlocks < 0 || cChar == bChar) 
        idxBlocks = totBlocks - 1;
      cChar = ' ';
      bChar = blocks[idxBlocks];
      break;
    case '?':
      printf("\b Click a key to make it the custom character");
      cChar = getchar();
      bChar = cChar;
      break;
    case UP_ARROW:
      if(map[y-1][x] != ' ') map[y-1][x] = ' ';
      else map[y-1][x] = bChar;
      break;
    case RIGHT_ARROW:
      if(map[y][x+1] != ' ') map[y][x+1] = ' ';
      else map[y][x+1] = bChar;
      break;
    case DOWN_ARROW:
      if(map[y+1][x] != ' ') map[y+1][x] = ' ';
      else map[y+1][x] = bChar;
      break;
    case LEFT_ARROW:
      if(map[y][x-1] != ' ') map[y][x-1] = ' ';
      else map[y][x-1] = bChar;
      break;
  }
  map[y][x] = pChar;
}

int main() {
  init_color();
  splash();
  setup();
  do {
    printScreen();
    movement();
  } while (input != 'q');

  system("/bin/stty cooked");
  printf("\b\b Quitted...\n\e[?25h");
}


