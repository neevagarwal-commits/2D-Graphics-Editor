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

void drawRectangle(int x,int y,int width,int height,char ch) {

    for(int i=x;i<x+width;i++) {
        pic[y][i]=ch;
        pic[y+height-1][i]=ch;
    }

    for(int i=y;i<y+height;i++) {
        pic[i][x]=ch;
        pic[i][x+width-1]=ch;
    }
}

int main() {
    initialize();
    drawRectangle(5,4,20,8,'#');
    display();
    return 0;
}