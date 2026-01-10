#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <conio.h>

#define H_SCALE 2
#define DIM 16
#define OFFSET_X 1
#define OFFSET_Y 4

typedef struct { int x; int y; } pos;

void display_header();
void display_score(int len);
int play_or_quit();
int game();
pos *update_snake(pos *snake, int len, int dir, int eat);
pos *update_head(pos *head, int dir);
void display_grid();
void display_len(int len);
void display_record();
void display_snake(pos *snake, int len);
void display_segment(pos segment);
void display_fruit(pos fruit);
void delete_tail(pos *snake, int len);
pos *place_fruit(pos *snake, int len);
int check_overlapping(pos *snake, int len);
int catch_input(int dir, int len);
int check_boundaries(pos head);
int check_fruit(pos head, pos fruit);
void gotoxy(int x, int y);


int main() {
    int play = 1;
    while(play) {
        system("cls");
        display_header();
        int score = game();
        system("cls");
        display_header();
        display_score(score);
        play = play_or_quit();
    }

    return 0;
}

/* function with game loop */
int game() {
    int len = 1;
    int dir = 80;

    pos *snake = malloc(len * sizeof(pos));
    snake->x = 5;
    snake->y = 5;

    pos *fruit = malloc(sizeof(pos));
    fruit = place_fruit(snake, len);

    display_grid();
    display_fruit(*fruit);
    display_record();

    while (check_boundaries(*snake) && check_overlapping(snake, len)) {
        display_len(len);
        display_snake(snake, len);
        int eat = check_fruit(*snake, *fruit);
        if (eat) {
            free(fruit);
            fruit = place_fruit(snake, len);
            display_fruit(*fruit);
        }
        len += eat;
        usleep(150000);
        dir = catch_input(dir, len);
        delete_tail(snake, len);
        snake = update_snake(snake, len, dir, eat);
    }

    return len;
}

/* function to update position of the snake */
pos *update_snake(pos *snake, int len, int dir, int eat) {
    // if snake has eaten the fruit I allocate other 2 byte of memory;
    pos *new_head = update_head(snake, dir);
    pos *new_snake = malloc(len * sizeof(pos));
    new_snake->x = new_head->x;
    new_snake->y = new_head->y;
    for (int i = 0; i < len - 1; i++) {
        (new_snake+i+1)->x = (snake+i)->x;
        (new_snake+i+1)->y = (snake+i)->y;
    }

    if (eat) {
        (new_snake+len-1)->x = (snake+len-2)->x;
        (new_snake+len-1)->y = (snake+len-2)->y;
    }

    free(snake);
    free(new_head);
    return new_snake;
}


/* function to update position of head segment */
pos *update_head(pos *head, int dir) {
    pos *new_pos = malloc(sizeof(pos));
    switch (dir) {
        case 72:
            new_pos->x = head->x;
            new_pos->y = head->y - 1;
            break;
        case 80:
            new_pos->x = head->x;
            new_pos->y = head->y + 1;
            break;
        case 75:
            new_pos->x = head->x - 1;
            new_pos->y = head->y;
            break;
        case 77:
            new_pos->x = head->x + 1;
            new_pos->y = head->y;
            break;
    }
    return new_pos;
}

/* function to display grid. width is scaled by 2 than height */
void display_grid() {
    int w = DIM * H_SCALE;
    int h = DIM;
    for (int i = 0; i <= h; i++) {
        for (int j = 0; j <= w; j++) {
            gotoxy(j+1, i+1);
            if (i == 0) printf("_");
            if (i == 0 && j == w) printf("_");
            if ((i != 0 && i != h) && j != 0) printf(" ");
            if ((i != 0 && i != h) && j == 0) printf("|");
            if ((i != 0 && i != h) && j == w-1) printf(" |");
            if (i == h && j == 0) printf("|_");
            if (i == h && j == w-1) printf("__|");
            if (i == h && j > 0 && j < w-1) printf("_");
        }
        printf("\n");
    }
}

/* function to display length of the snake */
void display_len(int len) {
    gotoxy(1, 0);
    printf("Length: %d\n", len);
}

/* function to display record of the game */
void display_record() {
    gotoxy(DIM * H_SCALE - 10, 0);
    printf("Record: %d\n", 255);
}

/* function to display the whole snake's body. */
void display_snake(pos *snake, int len) {
    display_segment(snake[0]);
}

/* function to display a single segment of snake's body.
    width of the segment is affected by horizontal_scale
*/
void display_segment(pos segment) {
    for (int i = 0; i < H_SCALE; i++) {
        int scaled_x = (segment.x * H_SCALE) + i;
        gotoxy(scaled_x, segment.y + 1);
        putchar(177);
    }
}

/* function to display a fruit, width of the fruit is affected by horizontal_scale */
void display_fruit(pos fruit) {
    for (int i = 0; i < H_SCALE; i++) {
        int scaled_x = (fruit.x * H_SCALE) + i;
        gotoxy(scaled_x, fruit.y + 1);
        putchar(219);
    }
}

void delete_tail(pos *snake, int len) {
    for (int i = 0; i < H_SCALE; i++) {
        int scaled_x = ((snake+len-1)->x * H_SCALE) + i;
        gotoxy(scaled_x, (snake+len-1)->y + 1);
        // manage deletion of grid when snake pass along the bottom side.
        if ((snake+len-1)->y == DIM) {
            gotoxy(scaled_x, (snake+len-1)->y + 1);
            putchar('_');
        } else  putchar(32);
        
    }
}

/* function to check if snake is overlapping its own body with head */
int check_overlapping(pos *snake, int len) {
    for (int i = 0; i < len - 1; i++) {
        if ((snake+i+1)->x == snake->x && (snake+i+1)->y == snake->y) return 0;
    }
    return 1;
}

/* function to check if head is go out of the board */
int check_boundaries(pos head) {
    if (head.x < 1 || head.y < 1 || head.x > DIM || head.y > DIM) return 0;
    return 1;
}

/* function to check if snake eat fruit */
int check_fruit(pos head, pos fruit) {
    if (head.x == fruit.x && head.y == fruit.y) return 1;
    return 0;
}


/* function to check if snake eat fruit */
pos *place_fruit(pos *snake, int len) {
    srand(time(NULL));
    pos *fruit = malloc(sizeof(pos));
    int retry;
    do {
        retry = 0;
        fruit->x = 1 + (rand() % (DIM - 1));
        fruit->y = 1 + (rand() % (DIM - 1));
        for (int i = 0; i < len; i++) {
            if ((snake+i)->x == fruit->x && (snake+i)->y == fruit->y) retry = 1;
        }
    } while (retry); 

    return fruit;
}

/* function to catch digited key by user. If the key is the reverse of actual direction, this one won't change. */
int catch_input(int dir, int len) {
    int new_dir = dir;
    if (_kbhit()) {
        int ch = _getch();
        if (ch == 0 || ch == 224)
            new_dir = _getch();
    }
    int diff = new_dir - dir;
    if ((diff == 8 || diff == -8 || diff == 2 || diff == -2) && len > 1) return dir;
    return new_dir;
}

/* function to display header of game */
void display_header() {
    printf("SNAKE GAME\n\n");
}

/* function to display score */
void display_score(int len) {
    printf("Game over. Score -> %d\n\n", len);
}

/* flow to manage play or quit */
int play_or_quit() {
    int choice;
choose:
    printf("[Y] to replay or [N] to quit: ");
    choice = getchar();
    
    // Svuota il buffer (consuma tutto fino al newline incluso)
    while (getchar() != '\n');
    
    switch (choice) {
        case 'Y':
        case 'y':
            return 1;
        case 'N':
        case 'n':
            return 0;
        default:
            printf("\nYou can digit only [Y] or [N]!\n\n");
            goto choose;
    }
}

/* util to move cursor in terminal.
    first x inside the grid is 2, last one is eq to DIM * scale; 
    first y inside the grid is 2, last one is eq to DIM + 1;
    For example: if DIMension (DIM) of the grid is 10, and the H_SCALE is 2, so the snake
    can move itself from (2,2) to (20, 11);
    Each horizontal movement will be scaled by 2!!
*/
void gotoxy(int x, int y) {
    printf("\033[%d;%df", y + OFFSET_Y, x + OFFSET_X);
}