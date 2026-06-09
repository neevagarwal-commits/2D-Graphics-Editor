#include <stdio.h>

#define ROWS 20
#define COLS 40

char pic[ROWS][COLS];

void initialize() {
    for(int i=0;i<ROWS;i++)
        for(int j=0;j<COLS;j++)
            pic[i][j]=' ';
}

void display() {
    for(int i=0;i<ROWS;i++) {
        for(int j=0;j<COLS;j++)
            printf("%c",pic[i][j]);
        printf("\n");
    }
}

int main() {

    initialize();

    int row = 2;
    int col = 20;
    int height = 8;

    for(int i=0;i<height;i++) {
        pic[row+i][col-i] = '*';
        pic[row+i][col+i] = '*';
    }

    for(int i=col-height+1;i<=col+height-1;i++)
        pic[row+height-1][i]='*';

    display();

    return 0;
}