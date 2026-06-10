#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 25
#define COLS 80
#define MAX_SHAPES 50

char canvas[ROWS][COLS];

typedef struct
{
    int id;
    int type; // 1-Line 2-Rectangle 3-Circle 4-Triangle

    int x1, y1;
    int x2, y2;
    int x3, y3;

    int radius;

} Shape;

Shape shapes[MAX_SHAPES];

int shapeCount = 0;
int nextID = 100;

/* ---------------- Canvas Functions ---------------- */

void clearCanvas()
{
    int i, j;

    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            canvas[i][j] = '_';
        }
    }
}

void putPixel(int x, int y)
{
    if (x >= 0 && x < COLS && y >= 0 && y < ROWS)
    {
        canvas[y][x] = '*';
    }
}

void displayCanvas()
{
    int i, j;

    printf("\n");

    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

/* ---------------- Drawing Functions ---------------- */

void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (1)
    {
        putPixel(x1, y1);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void drawRectangle(int x1, int y1, int x2, int y2)
{
    if (x1 > x2)
    {
        int temp = x1;
        x1 = x2;
        x2 = temp;
    }

    if (y1 > y2)
    {
        int temp = y1;
        y1 = y2;
        y2 = temp;
    }

    drawLine(x1, y1, x2, y1);
    drawLine(x1, y2, x2, y2);
    drawLine(x1, y1, x1, y2);
    drawLine(x2, y1, x2, y2);
}

void drawCircle(int cx, int cy, int r)
{
    int x = 0;
    int y = r;
    int d = 3 - (2 * r);

    while (x <= y)
    {
        putPixel(cx + x, cy + y);
        putPixel(cx - x, cy + y);
        putPixel(cx + x, cy - y);
        putPixel(cx - x, cy - y);

        putPixel(cx + y, cy + x);
        putPixel(cx - y, cy + x);
        putPixel(cx + y, cy - x);
        putPixel(cx - y, cy - x);

        if (d < 0)
        {
            d = d + (4 * x) + 6;
        }
        else
        {
            d = d + 4 * (x - y) + 10;
            y--;
        }

        x++;
    }
}

void drawTriangle(int x1, int y1,
                  int x2, int y2,
                  int x3, int y3)
{
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

/* ---------------- Utility Functions ---------------- */

void redrawCanvas()
{
    int i;

    clearCanvas();

    for (i = 0; i < shapeCount; i++)
    {
        switch (shapes[i].type)
        {
        case 1:
            drawLine(shapes[i].x1,
                     shapes[i].y1,
                     shapes[i].x2,
                     shapes[i].y2);
            break;

        case 2:
            drawRectangle(shapes[i].x1,
                          shapes[i].y1,
                          shapes[i].x2,
                          shapes[i].y2);
            break;

        case 3:
            drawCircle(shapes[i].x1,
                       shapes[i].y1,
                       shapes[i].radius);
            break;

        case 4:
            drawTriangle(shapes[i].x1,
                         shapes[i].y1,
                         shapes[i].x2,
                         shapes[i].y2,
                         shapes[i].x3,
                         shapes[i].y3);
            break;
        }
    }
}

int searchShape(int id)
{
    int i;

    for (i = 0; i < shapeCount; i++)
    {
        if (shapes[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

void listShapes()
{
    int i;

    if (shapeCount == 0)
    {
        printf("\nNo Shapes Present.\n");
        return;
    }

    printf("\n----- Shape List -----\n");

    for (i = 0; i < shapeCount; i++)
    {
        printf("ID %d : ", shapes[i].id);

        if (shapes[i].type == 1)
            printf("Line");

        else if (shapes[i].type == 2)
            printf("Rectangle");

        else if (shapes[i].type == 3)
            printf("Circle");

        else
            printf("Triangle");

        printf("\n");
    }
}

/* ---------------- Shape Operations ---------------- */

void addShape()
{
    if (shapeCount >= MAX_SHAPES)
    {
        printf("\nShape Storage Full!\n");
        return;
    }

    Shape s;

    printf("\nSelect Shape Type\n");
    printf("1. Line\n");
    printf("2. Rectangle\n");
    printf("3. Circle\n");
    printf("4. Triangle\n");

    printf("Enter Choice : ");
    scanf("%d", &s.type);

    s.id = nextID++;

    switch (s.type)
    {
    case 1:
        printf("Enter x1 y1 x2 y2 : ");
        scanf("%d %d %d %d",
              &s.x1, &s.y1,
              &s.x2, &s.y2);
        break;

    case 2:
        printf("Enter top-left and bottom-right coordinates:\n");
        scanf("%d %d %d %d",
              &s.x1, &s.y1,
              &s.x2, &s.y2);
        break;

    case 3:
        printf("Enter center x y and radius : ");
        scanf("%d %d %d",
              &s.x1,
              &s.y1,
              &s.radius);
        break;

    case 4:
        printf("Enter x1 y1 x2 y2 x3 y3 : ");
        scanf("%d %d %d %d %d %d",
              &s.x1, &s.y1,
              &s.x2, &s.y2,
              &s.x3, &s.y3);
        break;

    default:
        printf("Invalid Shape Type\n");
        return;
    }

    shapes[shapeCount++] = s;

    redrawCanvas();

    printf("\nShape Added Successfully");
    printf("\nAssigned ID : %d\n", s.id);

    displayCanvas();
}

void deleteShape()
{
    int id, index, i;

    printf("\nEnter Shape ID to Delete : ");
    scanf("%d", &id);

    index = searchShape(id);

    if (index == -1)
    {
        printf("Shape Not Found\n");
        return;
    }

    for (i = index; i < shapeCount - 1; i++)
    {
        shapes[i] = shapes[i + 1];
    }

    shapeCount--;

    redrawCanvas();

    printf("Shape Deleted Successfully\n");

    displayCanvas();
}

void modifyShape()
{
    int id;
    int index;

    printf("\nEnter Shape ID to Modify : ");
    scanf("%d", &id);

    index = searchShape(id);

    if (index == -1)
    {
        printf("Shape Not Found\n");
        return;
    }

    printf("\nEnter New Details\n");

    switch (shapes[index].type)
    {
    case 1:
        printf("Enter x1 y1 x2 y2 : ");
        scanf("%d %d %d %d",
              &shapes[index].x1,
              &shapes[index].y1,
              &shapes[index].x2,
              &shapes[index].y2);
        break;

    case 2:
        printf("Enter x1 y1 x2 y2 : ");
        scanf("%d %d %d %d",
              &shapes[index].x1,
              &shapes[index].y1,
              &shapes[index].x2,
              &shapes[index].y2);
        break;

    case 3:
        printf("Enter center x y radius : ");
        scanf("%d %d %d",
              &shapes[index].x1,
              &shapes[index].y1,
              &shapes[index].radius);
        break;

    case 4:
        printf("Enter x1 y1 x2 y2 x3 y3 : ");
        scanf("%d %d %d %d %d %d",
              &shapes[index].x1,
              &shapes[index].y1,
              &shapes[index].x2,
              &shapes[index].y2,
              &shapes[index].x3,
              &shapes[index].y3);
        break;
    }

    redrawCanvas();

    printf("Shape Modified Successfully\n");

    displayCanvas();
}

/* ---------------- Main Function ---------------- */

int main()
{
    int choice;

    clearCanvas();

    while (1)
    {
        printf("\n");
        printf("\n========== 2D GRAPHICS EDITOR ==========\n");
        printf("1. Add Shape\n");
        printf("2. Delete Shape\n");
        printf("3. Modify Shape\n");
        printf("4. Display Canvas\n");
        printf("5. List Shapes\n");
        printf("6. Exit\n");
        printf("Enter Choice : ");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addShape();
            break;

        case 2:
            deleteShape();
            break;

        case 3:
            modifyShape();
            break;

        case 4:
            displayCanvas();
            break;

        case 5:
            listShapes();
            break;

        case 6:
            printf("\nThank You For Using 2D Graphics Editor\n");
            return 0;

        default:
            printf("Invalid Choice\n");
        }
    }

    return 0;
}