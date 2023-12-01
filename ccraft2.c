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
char ds[6];
char input;
int x, y, direction;
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
  direction = 0;
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

  switch(direction) {
    case UP:
      strcpy(ds, "up");
      break;
    case RIGHT:
      strcpy(ds, "right");
      break;
    case DOWN:
      strcpy(ds, "down");
      break;
    case LEFT:
      strcpy(ds, "left");
      break;
  }

  printf(" Movement: w a s d  Direction: arrows  Change block: c ('%c')  \t\t\t\tQuit: q\t\t  X: %d Y: %d D: %s\n", bChar, x, y, ds);
  printf(" Build: b  Destroy: n\n");
  system("/bin/stty raw");

}


void movement() {
  input = getchar();
  putchar(input);
  map[y][x] = ' ';
  switch(input) {
    case 'a':
      x--;
      direction = LEFT;
      if(x == 0 || map[y][x] != ' ')
        x++;
      break;
    case 'd':
      x++;
      direction = RIGHT;
      if(x == WIDTH-1 || map[y][x] != ' ')
        x--;
      break;
    case 'w':
      y--;
      direction = UP;
      if(y == 0 || map[y][x] != ' ')
        y++;
      break;
    case 's':
      y++;
      direction = DOWN;
      if(y == HEIGHT-1 || map[y][x] != ' ')
        y--;
      break;
    case 'b':
      if(direction == UP)
        map[y-1][x] = bChar;
      if(direction == RIGHT)
        map[y][x+1] = bChar;
      if(direction == DOWN)
        map[y+1][x] = bChar;
      if(direction == LEFT)
        map[y][x-1] = bChar;
      break;
    case 'n':
      if(direction == UP)
        map[y-1][x] = ' ';
      if(direction == RIGHT)
        map[y][x+1] = ' ';
      if(direction == DOWN)
        map[y+1][x] = ' ';
      if(direction == LEFT)
        map[y][x-1] = ' ';
      break;
    case 'c':
      idxBlocks++;
      if(idxBlocks == totBlocks) 
        idxBlocks = 0;
      bChar = blocks[idxBlocks];
      break;
    case UP_ARROW:
      direction = UP;
      break;
    case RIGHT_ARROW:
      direction = RIGHT;
      break;
    case DOWN_ARROW:
      direction = DOWN;
      break;
    case LEFT_ARROW:
      direction = LEFT;
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


