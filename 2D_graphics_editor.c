#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define ROWS 20
#define COLS 50
#define MAX 100

typedef enum{
    LINE=1,
    TRIANGLE=2,
    RECTANGLE=3,
    CIRCLE=4
}ObjectType;

typedef struct{
    int x1,x2,y1,y2;
}Line;

typedef struct{
    int x1,y1,x2,y2;
}Rectangle;

typedef struct {
    int xc, yc, radius;
} Circle;

typedef struct {
    int x1, y1, x2, y2, x3, y3;
} Triangle;

typedef struct {
    ObjectType type;
    union {
        Line line;
        Rectangle rect;
        Circle circle;
        Triangle tri;
    } data;
} Object;

char canvas[ROWS][COLS];
Object objects[MAX];
int objectCount = 0;

void initializeCanvas();
void plot(int x, int y);
void drawLine(int x1, int y1, int x2, int y2);
void drawRectangle(int x1, int y1, int x2, int y2);
void drawCircle(int xc, int yc, int radius);
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
void redrawCanvas();
void displayCanvas();
void addLine();
void addRectangle();
void addCircle();
void addTriangle();
void deleteObject();
void modifyObject();
void listObjects();
void displayMenu();
void renderObject(Object obj);

int main()
{
    int choice;
    initializeCanvas();
    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addLine();
                break;
            case 2:
                addRectangle();
                break;
            case 3:
                addCircle();
                break;
            case 4:
                addTriangle();
                break;
            case 5:
                deleteObject();
                break;
            case 6:
                modifyObject();
                break;
            case 7:
                displayCanvas();
                break;
            case 8:
                listObjects();
                break;
            case 9:
                return 0;
            default:
                printf("Invalid Choice\n");
        }
    }

    return 0;
}

void initializeCanvas() {
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLS;j++){
            canvas[i][j]='_';
        }
    }
}

void plot(int x, int y){
    if(x>=0 && x<COLS && y>=0 && y<ROWS){
        canvas[y][x]='*';
    }
}

void drawLine(int x1, int y1, int x2, int y2){
    int dx= abs(x2-x1);
    int dy= abs(y2-y1);
    int sx= (x1<x2)?1:-1;
    int sy= (y1<y2)?1:-1;
    int err= dx-dy;
    while (1) {
        plot(x1, y1);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void drawRectangle(int x1, int y1, int x2, int y2){
    drawLine(x1, y1, x2, y1);
    drawLine(x2, y1, x2, y2);
    drawLine(x2, y2, x1, y2);
    drawLine(x1, y2, x1, y1);
}

void drawCircle(int xc, int yc, int radius){
    int x = 0, y = radius;
    int d = 3 - 2 * radius;
    while (y >= x) {
        plot(xc + x, yc + y);
        plot(xc - x, yc + y);
        plot(xc + x, yc - y);
        plot(xc - x, yc - y);
        plot(xc + y, yc + x);
        plot(xc - y, yc + x);
        plot(xc + y, yc - x);
        plot(xc - y, yc - x);
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
    }
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3){
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

void redrawCanvas(){
    initializeCanvas();
    for (int i = 0; i < objectCount; i++) {
        renderObject(objects[i]);
    }
}

void displayCanvas(){
    redrawCanvas();
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

void addLine(){
    if (objectCount >= MAX) {
        printf("Object limit reached\n");
        return;
    }
    Object obj;
    obj.type = LINE;

    printf("Enter x1 y1 x2 y2: ");
    scanf("%d %d %d %d",
          &obj.data.line.x1, &obj.data.line.y1,
          &obj.data.line.x2, &obj.data.line.y2);
          objects[objectCount++] = obj;
    printf("Line added successfully\n");
}

void addRectangle(){
    if (objectCount >= MAX) {
        printf("Object limit reached\n");
        return;
    }

    Object obj;
    obj.type = RECTANGLE;

    printf("Enter x1 y1 x2 y2: ");
    scanf("%d %d %d %d",
          &obj.data.rect.x1, &obj.data.rect.y1,
          &obj.data.rect.x2, &obj.data.rect.y2);

    objects[objectCount++] = obj;
    printf("Rectangle added successfully\n");
}

void addCircle(int xc, int yc, int radius){
int x = 0, y = radius;
int d = 3 - 2 * radius;

    while (y >= x) {
        plot(xc + x, yc + y);
        plot(xc - x, yc + y);
        plot(xc + x, yc - y);
        plot(xc - x, yc - y);
        plot(xc + y, yc + x);
        plot(xc - y, yc + x);
        plot(xc + y, yc - x);
        plot(xc - y, yc - x);

        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else {
            d = d + 4 * x + 6;
        }
    }
}

void addTriangle(){
    if (objectCount >= MAX_OBJECTS) {
        printf("Object limit reached\n");
        return;
}

void deleteObject(){

}

void modifyObject(){

}

void listObjects(){

}

void displayMenu(){

}

void renderObject(Object obj){
    switch (obj.type) {
        case LINE:
            drawLine(obj.data.line.x1, obj.data.line.y1,
                     obj.data.line.x2, obj.data.line.y2);
            break;
        case RECTANGLE:
            drawRectangle(obj.data.rect.x1, obj.data.rect.y1,
                          obj.data.rect.x2, obj.data.rect.y2);
            break;
        case CIRCLE:
            drawCircle(obj.data.circle.xc, obj.data.circle.yc,
                       obj.data.circle.radius);
            break;
        case TRIANGLE:
            drawTriangle(obj.data.tri.x1, obj.data.tri.y1,
                         obj.data.tri.x2, obj.data.tri.y2,
                         obj.data.tri.x3, obj.data.tri.y3);
            break;
    }
}