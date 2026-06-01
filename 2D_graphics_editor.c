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

void initializeCanvas(void) {

}

void plot(int x, int y){

}

void drawLine(int x1, int y1, int x2, int y2){

}

void drawRectangle(int x1, int y1, int x2, int y2){

}

void drawCircle(int xc, int yc, int radius){

}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3){

}

void redrawCanvas(){

}

void displayCanvas(){

}

void addLine(){

}

void addRectangle(){

}

void addCircle(){

}

void addTriangle(){

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
    
}