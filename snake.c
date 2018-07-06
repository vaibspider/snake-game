/*********************************************************************
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.

**************************************************************************/

/************************************
 * Copyright 06-07-2018
 * Author: Vaibhav Kurhe
 * Email-ID: vaibhav.kurhe@gmail.com
 *
 * **********************************/

#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct RowCol {
    int r;
    int c;
} RowCol;

char snake[1024] = "##########";
RowCol rowcol[1024];
void init_row_col(int, int);
char object = 'A';
int object_row = 0;
int object_col = 0;
void generate_object();
int row_max;
int col_max;

int main() {

    int row = 0, col = 0;
    int ch;
    int snake_row = 0;
    int snake_col = 0;
    int row_center = 0;
    int col_center = 0;
    int input;
    int state;
    int i = 0;
    int j = 0;
    int pointer = 0;
    int curr_row;
    int curr_col;
    int just_entered = 0;
    int from;
    int firsttime;

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    getmaxyx(stdscr, row, col);

    row_max = row;
    col_max = col;

    row_center = row/2;
    col_center = (col - strlen(snake))/2;

    snake_row = row_center;
    snake_col = col_center;

    object_row = row/4;
    object_col = col/8;


    init_row_col(snake_row, snake_col);
    mvprintw(snake_row, snake_col, "%s", snake);
    mvaddch(object_row, object_col, object | A_BOLD);
    refresh();

    ch = getch();

    halfdelay(1);

    firsttime = 1;
    while (ch != ERR) {
        //just_entered = 1;
        switch (ch) {
            case(KEY_LEFT):
                while(rowcol[0].c > 0) {
                    if (just_entered == 1 && from != -123) {
                        pointer = 0;
                        for (i = 0; i < strlen(snake) - 1 && pointer < strlen(snake) - 1; i++) {
                            clear();
                            //mvaddch(object_row, object_col, object | A_BOLD);
                            generate_object();
                            for (j = 0; j <= pointer; j++) {
                                mvaddch(rowcol[j].r, --rowcol[j].c, snake[j]);
                            }

                            usleep(100000);

                            for (j = pointer + 1; j < strlen(snake); j++) {
                                if (from == KEY_UP) {
                                    mvaddch(--rowcol[j].r, rowcol[j].c, snake[j]);
                                }
                                else if (from == KEY_DOWN){
                                    mvaddch(++rowcol[j].r, rowcol[j].c, snake[j]);
                                }
                                else {
                                }
                            }
                            pointer++;
                            refresh();
                            usleep(100000);
                        }
                        just_entered = 0;
                    }

                    clear();
                    //mvaddch(object_row, object_col, object | A_BOLD);
                    generate_object();
                    for (i = 0; i < strlen(snake); i++) {
                        mvaddch(rowcol[i].r, --rowcol[i].c, snake[i]);
                    }
                    //mvprintw(snake_row, snake_col, "%s", snake);
                    refresh();
                    usleep(100000);
                    input = getch();
                    if (input == KEY_UP || input == KEY_DOWN) {
                        just_entered = 1;
                        from = KEY_LEFT;
                        break;
                    }
                }
                if (rowcol[0].c == 0) {
                    clear();
                    mvprintw(row_center, col_center, "GAME OVER");
                    refresh();
                    state = input;//ERR
                }
                else {
                    state = input;
                }
                firsttime = 0;
                break;
            case(KEY_RIGHT):
                while(rowcol[0].c < col_max) {
                    if (just_entered == 1) {
                        pointer = 0;
                        for (i = 0; i < strlen(snake) - 1 && pointer < strlen(snake) - 1; i++) {
                            clear();
                            //mvaddch(object_row, object_col, object | A_BOLD);
                            generate_object();
                            for (j = 0; j <= pointer; j++) {
                                mvaddch(rowcol[j].r, ++rowcol[j].c, snake[j]);
                            }

                            usleep(100000);

                            for (j = pointer + 1; j < strlen(snake); j++) {
                                if (from == KEY_UP) {
                                    mvaddch(--rowcol[j].r, rowcol[j].c, snake[j]);
                                }
                                else if (from == KEY_DOWN) { // from == KEY_DOWN
                                    mvaddch(++rowcol[j].r, rowcol[j].c, snake[j]);
                                }
                            }
                            pointer++;
                            refresh();
                            usleep(100000);
                        }
                        just_entered = 0;
                    }

                    if (firsttime == 1) {
                        usleep(100000);
                        input = getch();
                        if (input == KEY_UP || input == KEY_DOWN || input == KEY_LEFT) {
                            just_entered = 1;
                            from = -123;
                            break;
                        }
                    }
                    else {
                        clear();
                        //mvaddch(object_row, object_col, object | A_BOLD);
                        generate_object();
                        for (i = 0; i < strlen(snake); i++) {
                            mvaddch(rowcol[i].r, ++rowcol[i].c, snake[i]);
                        }
                        //mvprintw(snake_row, snake_col, "%s", snake);
                        refresh();
                        usleep(100000);
                        input = getch();
                        if (input == KEY_UP || input == KEY_DOWN) {
                            just_entered = 1;
                            from = KEY_RIGHT;
                            break;
                        }
                    }
                }
                if (rowcol[0].c == col_max) {
                    clear();
                    mvprintw(row_center, col_center, "GAME OVER");
                    refresh();
                    state = input;//ERR
                }
                else {
                    state = input;
                }
                firsttime = 0;
                break;
            case(KEY_UP):
                just_entered = 1;
                while(rowcol[0].r > 0) {
                    if (just_entered == 1) {
                        pointer = 0;
                        for (i = 0; i < strlen(snake) - 1 && pointer < strlen(snake) - 1; i++) {
                            clear();
                            //mvaddch(object_row, object_col, object | A_BOLD);
                            generate_object();
                            for (j = 0; j <= pointer; j++) {
                                mvaddch(--rowcol[j].r, rowcol[j].c, snake[j]);
                            }

                            usleep(100000);

                            for (j = pointer + 1; j < strlen(snake); j++) {
                                if (from == KEY_LEFT) {
                                    mvaddch(rowcol[j].r, --rowcol[j].c, snake[j]);
                                }
                                else if (from == KEY_RIGHT) {
                                    mvaddch(rowcol[j].r, ++rowcol[j].c, snake[j]);
                                }
                                else {//same as KEY_LEFT
                                    mvaddch(rowcol[j].r, --rowcol[j].c, snake[j]);
                                }
                            }
                            pointer++;
                            refresh();
                            usleep(100000);
                        }
                        just_entered = 0;
                    }

                    clear();
                    //mvaddch(object_row, object_col, object | A_BOLD);
                    generate_object();
                    for (i = 0; i < strlen(snake); i++) {
                        mvaddch(--rowcol[i].r, rowcol[i].c, snake[i]);
                    }
                    //mvprintw(snake_row, snake_col, "%s", snake);
                    refresh();
                    usleep(100000);
                    input = getch();
                    if (input == KEY_LEFT || input == KEY_RIGHT) {
                        just_entered = 1;
                        from = KEY_UP;
                        break;
                    }
                }
                if (rowcol[0].r == 0) {
                    clear();
                    mvprintw(row_center, col_center, "GAME OVER");
                    refresh();
                    state = input;//ERR
                }
                else {
                    state = input;
                }
                firsttime = 0;
                break;
            case(KEY_DOWN):
                just_entered = 1;
                while(rowcol[0].r < row_max) {
                    if (just_entered == 1) {
                        pointer = 0;
                        for (i = 0; i < strlen(snake) - 1 && pointer < strlen(snake) - 1; i++) {
                            clear();
                            //mvaddch(object_row, object_col, object | A_BOLD);
                            generate_object();
                            for (j = 0; j <= pointer; j++) {
                                mvaddch(++rowcol[j].r, rowcol[j].c, snake[j]);
                            }

                            usleep(100000);

                            for (j = pointer + 1; j < strlen(snake); j++) {
                                if (from == KEY_LEFT) {
                                    mvaddch(rowcol[j].r, --rowcol[j].c, snake[j]);
                                }
                                else if (from == KEY_RIGHT) {
                                    mvaddch(rowcol[j].r, ++rowcol[j].c, snake[j]);
                                }
                                else {//same as KEY_LEFT
                                    mvaddch(rowcol[j].r, --rowcol[j].c, snake[j]);
                                }
                            }
                            pointer++;
                            refresh();
                            usleep(100000);
                        }
                        just_entered = 0;
                    }

                    clear();
                    //mvaddch(object_row, object_col, object | A_BOLD);
                    generate_object();
                    for (i = 0; i < strlen(snake); i++) {
                        mvaddch(++rowcol[i].r, rowcol[i].c, snake[i]);
                    }
                    //mvprintw(snake_row, snake_col, "%s", snake);
                    refresh();
                    usleep(100000);
                    input = getch();
                    if (input == KEY_LEFT || input == KEY_RIGHT) {
                        just_entered = 1;
                        from = KEY_DOWN;
                        break;
                    }
                }
                if (rowcol[0].r == row_max) {
                    clear();
                    mvprintw(row_center, col_center, "GAME OVER");
                    refresh();
                    state = input;//ERR
                }
                else {
                    state = input;
                }
                firsttime = 0;
                break;
            default:
                break;
        }
        ch = state;
    }

    refresh();
    while(getch() != KEY_F(1));
    endwin();
    return 0;
}

void init_row_col(int startrow, int startcol) {
    int i;
    for (i = 0; i < strlen(snake); i++) {
        rowcol[i].r = startrow;
        rowcol[i].c = startcol + i;
    }
    rowcol[i].r = EOF;
    rowcol[i].c = EOF;
}

void generate_object() {
    if (rowcol[0].r == object_row && rowcol[0].c == object_col) {
        object_row = random() % row_max;
        object_col = random() % col_max;
    }
    mvaddch(object_row, object_col, object | A_BOLD);
}
