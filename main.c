#include <stdio.h>
#include <string.h>

#define ROWS 20
#define COLS 40

char canvas[ROWS][COLS];

// Clear canvas
void clearCanvas() {
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLS; j++)
            canvas[i][j] = '_';
}

// Display canvas
void displayCanvas() {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++)
            printf("%c", canvas[i][j]);
        printf("\n");
    }
}

// Draw Rectangle
void drawRectangle(int x, int y, int width, int height) {
    for(int i = y; i < y + height && i < ROWS; i++)
        for(int j = x; j < x + width && j < COLS; j++)
            canvas[i][j] = '*';
}

// Draw Horizontal Line
void drawLine(int x1, int x2, int y) {
    if (y < 0 || y >= ROWS || x1 > x2)
        return;

    int start = x1 < 0 ? 0 : x1;
    int end = x2 >= COLS ? COLS - 1 : x2;

    for(int i = start; i <= end; i++)
        canvas[y][i] = '*';
}

// Draw Triangle
void drawTriangle(int x, int y, int h) {
    if (x < 0 || y < 0 || h <= 0)
        return;

    for(int i = 0; i < h; i++) {
        int row = y + i;
        if (row < 0 || row >= ROWS)
            break;

        for(int j = 0; j <= i; j++) {
            int col = x + j;
            if (col < 0 || col >= COLS)
                continue;
            canvas[row][col] = '*';
        }
    }
}

// Draw Simple Circle
void drawCircle(int cx, int cy, int r) {
    if (r < 0)
        return;

    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            int dx = j - cx;
            int dy = i - cy;

            if(dx*dx + dy*dy <= r*r)
                canvas[i][j] = '*';
        }
    }
}

// Delete Object (replace area with '_')
void deleteArea(int x, int y, int width, int height) {
    for(int i = y; i < y + height && i < ROWS; i++)
        for(int j = x; j < x + width && j < COLS; j++)
            canvas[i][j] = '_';
}

int main() {
    int choice;
    int x, y, width, height, x2, h, cx, cy, r;

    clearCanvas();

    while (1) {
        printf("\nCanvas editor menu:\n");
        printf("1) Draw rectangle\n");
        printf("2) Draw line\n");
        printf("3) Draw triangle\n");
        printf("4) Draw circle\n");
        printf("5) Delete area\n");
        printf("6) Clear canvas\n");
        printf("7) Display canvas\n");
        printf("0) Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter x y width height: ");
                if (scanf("%d %d %d %d", &x, &y, &width, &height) == 4)
                    drawRectangle(x, y, width, height);
                else
                    printf("Invalid input.\n");
                break;
            case 2:
                printf("Enter x1 x2 y: ");
                if (scanf("%d %d %d", &x, &x2, &y) == 3)
                    drawLine(x, x2, y);
                else
                    printf("Invalid input.\n");
                break;
            case 3:
                printf("Enter x y height: ");
                if (scanf("%d %d %d", &x, &y, &h) == 3)
                    drawTriangle(x, y, h);
                else
                    printf("Invalid input.\n");
                break;
            case 4:
                printf("Enter center x y and radius: ");
                if (scanf("%d %d %d", &cx, &cy, &r) == 3)
                    drawCircle(cx, cy, r);
                else
                    printf("Invalid input.\n");
                break;
            case 5:
                printf("Enter x y width height: ");
                if (scanf("%d %d %d %d", &x, &y, &width, &height) == 4)
                    deleteArea(x, y, width, height);
                else
                    printf("Invalid input.\n");
                break;
            case 6:
                clearCanvas();
                printf("Canvas cleared.\n");
                break;
            case 7:
                displayCanvas();
                break;
            case 0:
                printf("Exiting.\n");
                return 0;
            default:
                printf("Unknown choice. Please select 0-7.\n");
                break;
        }

        while (getchar() != '\n');
    }

    return 0;
}