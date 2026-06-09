#include <stdio.h>
#include <stdlib.h>

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

void drawLine(int x1,int y1,int x2,int y2,char ch) {
    int dx=x2-x1;
    int dy=y2-y1;
    int steps=abs(dx)>abs(dy)?abs(dx):abs(dy);

    float xInc=dx/(float)steps;
    float yInc=dy/(float)steps;

    float x=x1,y=y1;

    for(int i=0;i<=steps;i++) {
        pic[(int)y][(int)x]=ch;
        x+=xInc;
        y+=yInc;
    }
}

int main() {
    initialize();
    drawLine(2,2,30,15,'*');
    display();
    return 0;
}