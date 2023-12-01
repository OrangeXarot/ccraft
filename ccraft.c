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
char blocks[] = {'#', '$', '/', '\\', '[', ']', '-'};
int totBlocks = sizeof(blocks)/sizeof(blocks[0]);
int idxBlocks = 0;
char bChar;
char input;
int x, y;
char color[9];

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
  char reset[] = "\e[0m";

  printf("\b \n%s ________                ________  ________  ________  ________ __________\n", color);
  printf("|\\   ____\\              |\\   ____\\|\\   __  \\|\\   __  \\|\\  _____\\\\___   ___\\\n");
  printf("\\ \\  \\___|  ____________\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\__/\\|___ \\  \\_|\n");
  printf(" \\ \\  \\    |\\____________\\ \\  \\    \\ \\   _  _\\ \\   __  \\ \\   __\\    \\ \\  \\  \n");
  printf("  \\ \\  \\___\\|____________|\\ \\  \\____\\ \\  \\\\  \\\\ \\  \\ \\  \\ \\  \\_|     \\ \\  \\ \n");
  printf("   \\ \\_______\\             \\ \\_______\\ \\__\\\\ _\\\\ \\__\\ \\__\\ \\__\\       \\ \\__\\\n");
  printf("    \\|_______|              \\|_______|\\|__|\\|__|\\|__|\\|__|\\|__|        \\|__| %s2.2\t\t\t   Made by %sOrangeXarot%s\n\n", reset, color, reset);
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
      else
        printf("%c", map[i][j]);
    }
    printf("\n");
  }


  printf(" Movement: w a s d   Change block: c ('%c')  \t\t\t\t\t\tQuit: q\t\t  X: %d Y: %d\n", bChar, x, y);
  printf(" Build and Destroy: arrows\n");
  system("/bin/stty raw");

}


void movement() {
  input = getchar();
  putchar(input);
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
    case 'c':
      idxBlocks++;
      if(idxBlocks == totBlocks) 
        idxBlocks = 0;
      bChar = blocks[idxBlocks];
      break;
    case UP_ARROW:
      if(map[y-1][x] == bChar) map[y-1][x] = ' ';
      else map[y-1][x] = bChar;
      break;
    case RIGHT_ARROW:
      if(map[y][x+1] == bChar) map[y][x+1] = ' ';
      else map[y][x+1] = bChar;
      break;
    case DOWN_ARROW:
      if(map[y+1][x] == bChar) map[y+1][x] = ' ';
      else map[y+1][x] = bChar;
      break;
    case LEFT_ARROW:
      if(map[y][x-1] == bChar) map[y][x-1] = ' ';
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
  printf("\b\b Quitted...\n");
}


