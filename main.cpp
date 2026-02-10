#include <iostream>
#include <random>
#include <ncurses.h>

using namespace std;

const int width = 50;
const int height = 20;
bool gameOver = false;
int snake_pos_x, snake_pos_y;
int fruit_x, fruit_y;
int segments_X[100];
int segments_Y[100];
int snake_size;
 
enum Direction { UP, DOWN, RIGHT, LEFT};
Direction dir;

void draw_fruit() {
    fruit_x = rand() % width;
    fruit_y = rand() % height;
}

void Setup() {
    snake_pos_x = width / 2;
    snake_pos_y = height / 2;
    draw_fruit();
}

void Draw(int width, int height) {
    clear();
    for (int i = 0; i < width+1; i++) {
        printw("#");
    }
    printw("\n");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            
            if (j == 0) {
                printw("#");
            } 

            if (j == snake_pos_x && i == snake_pos_y) {
                printw("0");

            } else if (j == fruit_x && i == fruit_y) {
                printw("F");

            } else {
                bool print = false;
                for (int k = 0; k < snake_size; k++) {
                    if (segments_X[k] == j && segments_Y[k] == i) {
                        printw("o");
                        print = true;
                    }
                }

                if (!print) {
                    printw(" ");
                }
            }
        

            if (j == width - 1) {
                printw("#");
            } 

        }
        printw("\n");
    }

    for (int i = 0; i < width+1; i++) {
        printw("#");
    }
    
    refresh();

}

void Logic() {
    int prevX = segments_X[0];
    int prevY = segments_Y[0];
    int prev2X, prev2Y;
    segments_X[0] = snake_pos_x;
    segments_Y[0] = snake_pos_y;

    for (int s = 1; s < snake_size; s++) {
        prev2X = segments_X[s];
        prev2Y = segments_Y[s];
        segments_X[s] = prevX;
        segments_Y[s] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case UP:
        snake_pos_y--;
        break;
    case DOWN:
        snake_pos_y++;   
        break; 
    case RIGHT:
        snake_pos_x++;
        break;
    case LEFT:
        snake_pos_x--;
        break;
    }


    if (snake_pos_x == width) {
        snake_pos_x = 1;

    } else if (snake_pos_x == 0) {
        snake_pos_x = width - 1;
    }

    if (snake_pos_y == height) {
        snake_pos_y = 0;

    } else if (snake_pos_y == 0) {
        snake_pos_y = height - 1;
    }

    if (snake_pos_x == fruit_x && snake_pos_y == fruit_y) {
        snake_size++;
        draw_fruit();
    }

    for (int p = 1; p < snake_size; p++) {
        if (snake_pos_x == segments_X[p] && snake_pos_y == segments_Y[p]) {
            clear();
            mvprintw(height / 2, width / 2, "You Lost...");
            refresh();
            napms(5000);
            gameOver = true;
        }
    }

}

void Input() {
    int ch;
    ch = getch();

    switch (ch) {
        case KEY_UP:
            dir = UP;
            break;
        case KEY_DOWN:
            dir = DOWN;
            break;
        case KEY_RIGHT:
            dir = RIGHT;
            break;
        case KEY_LEFT:
            dir = LEFT;
            break;
    }
}

int main() {
    initscr();
    cbreak(); 
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    Setup();

    while (!gameOver) {
        Draw(width, height);  
        Input();
        Logic();
        napms(100);   
    }
 
    endwin();
    return 0;
}