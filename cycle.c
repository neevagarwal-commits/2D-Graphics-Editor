#include <stdio.h>
#include <math.h>

#define ROWS 25
#define COLS 50

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

void drawCircle(int xc,int yc,int r,char ch) {

    for(int y=0;y<ROWS;y++) {
        for(int x=0;x<COLS;x++) {

            int d=(x-xc)*(x-xc)+(y-yc)*(y-yc);

            if(abs(d-r*r)<=r)
                pic[y][x]=ch;
        }
    }
}

int main() {

    initialize();

    drawCircle(25,12,8,'O');

    display();

    return 0;
}