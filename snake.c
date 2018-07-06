#include <ncurses.h>
#include <string.h>
#include <unistd.h>

typedef struct RowCol {
    int r;
    int c;
} RowCol;

char snake[1024] = "++++++++++";
RowCol rowcol[1024];
void init_row_col(int, int);

int main() {

    char object = 'A';
    int row, col;
    int ch;
    int snake_row;
    int snake_col;
    int object_row;
    int object_col;
    int row_center;
    int col_center;
    int input;
    int state;
    int row_max;
    int col_max;
    int i;
    int j;
    int pointer;
    int curr_row;
    int curr_col;
    int just_entered;
    int from;

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

    while (ch != ERR) {
        //just_entered = 1;
        switch (ch) {
            case(KEY_LEFT):
                while(snake_col > 0) {
                    /*
                    clear();
                    mvaddch(object_row, object_col, object | A_BOLD);
                    //snake_col--;
                    init_row_col(rowcol[0].r, --rowcol[0].c);
                    mvprintw(snake_row, snake_col, "%s", snake);
                    refresh();
                    usleep(100000);
                    input = getch();
                    if (input == KEY_UP || input == KEY_DOWN) {
                        just_entered = 1;
                        break;
                    }*/



                    if (just_entered == 1) {
                        pointer = 0;
                        for (i = 0; i < strlen(snake) - 1 && pointer < strlen(snake) - 1; i++) {
                            clear();
                            mvaddch(object_row, object_col, object | A_BOLD);
                            for (j = 0; j <= pointer; j++) {
                                mvaddch(rowcol[j].r, --rowcol[j].c, snake[j]);
                            }

                            usleep(100000);

                            for (j = pointer + 1; j < strlen(snake); j++) {
                                if (from == KEY_UP) {
                                    mvaddch(--rowcol[j].r, rowcol[j].c, snake[j]);
                                }
                                else { // from == KEY_DOWN
                                    mvaddch(++rowcol[j].r, rowcol[j].c, snake[j]);
                                }
                            }
                            pointer++;
                            refresh();
                            usleep(100000);
                        }
                        just_entered = 0;
                    }

                    clear();
                    mvaddch(object_row, object_col, object | A_BOLD);
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
                if (snake_col == 0) {
                    clear();
                    mvprintw(row_center, col_center, "GAME OVER");
                    refresh();
                    state = input;//ERR
                }
                else {
                    state = input;
                }
                break;
            case(KEY_RIGHT):
                while(snake_col < col_max) {
                    clear();
                    mvaddch(object_row, object_col, object | A_BOLD);
                    snake_col++;
                    mvprintw(snake_row, snake_col, "%s", snake);
                    refresh();
                    usleep(100000);
                    input = getch();
                    if (input == KEY_UP || input == KEY_DOWN) {
                        break;
                    }
                }
                if (snake_col == col_max) {
                    clear();
                    mvprintw(row_center, col_center, "GAME OVER");
                    refresh();
                    state = input;//ERR
                }
                else {
                    state = input;
                }
                break;
            case(KEY_UP):
                just_entered = 1;
                while(snake_row > 0) {
                    if (just_entered == 1) {
                        pointer = 0;
                        for (i = 0; i < strlen(snake) - 1 && pointer < strlen(snake) - 1; i++) {
                            clear();
                            mvaddch(object_row, object_col, object | A_BOLD);
                            for (j = 0; j <= pointer; j++) {
                                mvaddch(--rowcol[j].r, rowcol[j].c, snake[j]);
                            }

                            usleep(100000);

                            for (j = pointer + 1; j < strlen(snake); j++) {
                                mvaddch(rowcol[j].r, --rowcol[j].c, snake[j]);
                            }
                            pointer++;
                            refresh();
                            usleep(100000);
                        }
                        just_entered = 0;
                    }

                    clear();
                    mvaddch(object_row, object_col, object | A_BOLD);
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
                if (snake_row == 0) {
                    clear();
                    mvprintw(row_center, col_center, "GAME OVER");
                    refresh();
                    state = input;//ERR
                }
                else {
                    state = input;
                }
                break;
            case(KEY_DOWN):
                just_entered = 1;
                while(snake_row < row_max) {
                    if (just_entered == 1) {
                        pointer = 0;
                        for (i = 0; i < strlen(snake) - 1 && pointer < strlen(snake) - 1; i++) {
                            clear();
                            mvaddch(object_row, object_col, object | A_BOLD);
                            for (j = 0; j <= pointer; j++) {
                                mvaddch(++rowcol[j].r, rowcol[j].c, snake[j]);
                            }

                            usleep(100000);

                            for (j = pointer + 1; j < strlen(snake); j++) {
                                mvaddch(rowcol[j].r, --rowcol[j].c, snake[j]);
                            }
                            pointer++;
                            refresh();
                            usleep(100000);
                        }
                        just_entered = 0;
                    }

                    clear();
                    mvaddch(object_row, object_col, object | A_BOLD);
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
                if (snake_row == row_max) {
                    clear();
                    mvprintw(row_center, col_center, "GAME OVER");
                    refresh();
                    state = input;//ERR
                }
                else {
                    state = input;
                }
                break;
            default:
                break;
        }
        ch = state;
    }

    refresh();
    getch();
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
