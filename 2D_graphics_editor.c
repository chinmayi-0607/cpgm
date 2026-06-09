#include<stdio.h>
#include<stdlib.h>

#define ROWS 30
#define COLS 60
#define MAX 100

typedef enum{
    LINE=1,
    RECTANGLE,
    CIRCLE,
    TRIANGLE
}ObjectType;

typedef struct{
    int x1,y1,x2,y2;
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
void redrawCanvas();
void displayCanvas();

void plot(int x,int y);

void drawLine(int,int,int,int);
void drawRectangle(int,int,int,int);
void drawCircle(int,int,int);
void drawTriangle(int,int,int,int,int,int);

void renderObject(Object);

void addLine();
void addRectangle();
void addCircle();
void addTriangle();

void deleteObject();
void modifyObject();

void clearObjects();
void listObjects();

void displayMenu();

int validPoint(int x,int y);
int getInt();

int main()
{
    int choice;
    initializeCanvas();
    while (1) {
        displayMenu();
        choice=getInt();

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
                clearObjects();
                break;
            case 10:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
}

int getInt()
{
    int x;
    while(scanf("%d",&x)!=1)
    {
        printf("Enter number only: ");
        while(getchar()!='\n');
    }
    return x;
}

int validPoint(int x,int y)
{
    return x>=0 && x<COLS && y>=0 && y<ROWS;
}

void initializeCanvas()
{
    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
        {
            canvas[i][j]='_';
        }
    }
}

void plot(int x, int y)
{
    if(validPoint(x,y))
    {
        canvas[y][x]='*';
    }
}

void drawLine(int x1, int y1, int x2, int y2)
{
    int dx= abs(x2-x1);
    int dy= abs(y2-y1);
    int sx= (x1<x2)?1:-1;
    int sy= (y1<y2)?1:-1;
    int err= dx-dy;
    while (1) {
        plot(x1, y1);
        if (x1 == x2 && y1 == y2)
            break;
        int e2 = 2*err;
        if (e2>-dy)
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
    if(x1>x2)
    {
        int t=x1;x1=x2;x2=t;
    }
    if(y1>y2)
    {
        int t=y1;y1=y2;y2=t;
    }
    drawLine(x1, y1, x2, y1);
    drawLine(x2, y1, x2, y2);
    drawLine(x2, y2, x1, y2);
    drawLine(x1, y2, x1, y1);
}

void drawCircle(int xc, int yc, int r)
{
    int x = 0;
    int y=r;
    int d=3-(2*r);
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
            d += 4 * (x - y) + 10;
        } else {
            d += 4 * x + 6;
        }
    }
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

void renderObject(Object obj)
{
    switch(obj.type)
    {
        case LINE:
            drawLine(
            obj.data.line.x1,
            obj.data.line.y1,
            obj.data.line.x2,
            obj.data.line.y2);
            break;

        case RECTANGLE:
            drawRectangle(
            obj.data.rect.x1,
            obj.data.rect.y1,
            obj.data.rect.x2,
            obj.data.rect.y2);
            break;
        
        case CIRCLE:
            drawCircle(
            obj.data.circle.xc,
            obj.data.circle.yc,
            obj.data.circle.radius);
            break;

        case TRIANGLE:
            drawTriangle(
            obj.data.tri.x1,
            obj.data.tri.y1,
            obj.data.tri.x2,
            obj.data.tri.y2,
            obj.data.tri.x3,
            obj.data.tri.y3);
    }
}

void redrawCanvas()
{
    initializeCanvas();
    for (int i = 0; i < objectCount; i++) {
        renderObject(objects[i]);
    }
}

void displayCanvas()
{
    redrawCanvas();
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

void addLine()
{
    if(objectCount>=MAX)
    {
        printf("Object limit reached\n");
        return;
    }
    Object obj;
    obj.type=LINE;
    printf("Enter x1 y1 x2 y2: ");
    scanf("%d%d%d%d",
    &obj.data.line.x1,
    &obj.data.line.y1,
    &obj.data.line.x2,
    &obj.data.line.y2);
    if(
        !validPoint(obj.data.line.x1,obj.data.line.y1)
        ||
        !validPoint(obj.data.line.x2,obj.data.line.y2)
    )
    {
        printf("Coordinates outside canvas\n");
        return;
    }
    objects[objectCount++]=obj;
    printf("Line Added\n");
}

void addRectangle()
{
    if(objectCount>=MAX)
    {
        printf("Object limit reached\n");
        return;
    }
    Object obj;
    obj.type=RECTANGLE;
    printf("Enter x1 y1 x2 y2: ");
    scanf("%d%d%d%d",
    &obj.data.rect.x1,
    &obj.data.rect.y1,
    &obj.data.rect.x2,
    &obj.data.rect.y2);
    if(
        !validPoint(obj.data.rect.x1,obj.data.rect.y1)
        ||
        !validPoint(obj.data.rect.x2,obj.data.rect.y2)
    )
    {
        printf("Coordinates outside canvas\n");
        return;
    }
    objects[objectCount++]=obj;
    printf("Rectangle Added\n");
}

void addCircle()
{
    if(objectCount>=MAX)
    {
        printf("Object limit reached\n");
        return;
    }
    Object obj;
    obj.type=CIRCLE;
    printf("Enter xc yc radius: ");
    scanf("%d%d%d",
    &obj.data.circle.xc,
    &obj.data.circle.yc,
    &obj.data.circle.radius);
    if(obj.data.circle.radius<=0)
    {
        printf("Invalid Radius\n");
        return;
    }
    if(
        !validPoint(
            obj.data.circle.xc,
            obj.data.circle.yc
        )
    )
    {
        printf("Center outside canvas\n");
        return;
    }
    if(
        obj.data.circle.xc-obj.data.circle.radius<0 ||
        obj.data.circle.xc+obj.data.circle.radius>=COLS ||
        obj.data.circle.yc-obj.data.circle.radius<0 ||
        obj.data.circle.yc+obj.data.circle.radius>=ROWS
    )
    {
        printf("Circle exceeds canvas\n");
        return;
    }
    objects[objectCount++]=obj;
    printf("Circle Added\n");
}

void addTriangle()
{
    if(objectCount>=MAX)
    {
        printf("Object limit reached\n");
        return;
    }
    Object obj;
    obj.type=TRIANGLE;
    printf("Enter 6 coordinates:\n");
    scanf("%d%d%d%d%d%d",
    &obj.data.tri.x1,
    &obj.data.tri.y1,
    &obj.data.tri.x2,
    &obj.data.tri.y2,
    &obj.data.tri.x3,
    &obj.data.tri.y3);
    if(
        !validPoint(obj.data.tri.x1,obj.data.tri.y1)
        ||
        !validPoint(obj.data.tri.x2,obj.data.tri.y2)
        ||
        !validPoint(obj.data.tri.x3,obj.data.tri.y3)
    )
    {
        printf("Coordinates outside canvas\n");
        return;
    }
    objects[objectCount++]=obj;
    printf("Triangle Added\n");
}

void deleteObject()
{
    int id;
    listObjects();
    printf("Delete object: ");
    id=getInt();
    if(id<1||id>objectCount)
    {
        printf("Invalid object\n");
        return;
    }
    for(int i=id-1;i<objectCount-1;i++)
        objects[i]=objects[i+1];
    objectCount--;
    printf("Deleted\n");
}

void modifyObject()
{
    int id,type;
    if(objectCount==0)
    {
        printf("No objects\n");
        return;
    }
    listObjects();
    printf("Enter object number to modify: ");
    id=getInt();
    if(id<1 || id>objectCount)
    {
        printf("Invalid object\n");
        return;
    }
    for(int i=id-1;i<objectCount-1;i++)
    {
        objects[i]=objects[i+1];
    }
    objectCount--;
    printf(
        "\nChoose replacement object:\n"
        "1 Line\n"
        "2 Rectangle\n"
        "3 Circle\n"
        "4 Triangle\n"
        "Choice: "
    );
    type=getInt();
    if(type<1 || type>4)
    {
        printf("Invalid choice\n");
        return;
    }
    switch(type)
    {
    {
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

        default:
            printf("Invalid choice\n");
    }
}
}

void clearObjects()
{
    objectCount=0;
    initializeCanvas();
    printf("Canvas Cleared\n");
}

void listObjects()
{
    if(objectCount==0)
    {
        printf("No objects\n");
        return;
    }
    for(int i=0;i<objectCount;i++)
    {
        printf("%d/%d : ",i+1,objectCount);
        switch(objects[i].type)
        {
            case LINE:
                printf("Line\n");
                break;

            case RECTANGLE:
                printf("Rectangle\n");
                break;

            case CIRCLE:
                printf("Circle\n");
                break;

            case TRIANGLE:
                printf("Triangle\n");
        }
    }
}

void displayMenu()
{
    printf(
        "\n---2D GRAPHICS EDITOR---\n"
        "1 Add Line\n"
        "2 Add Rectangle\n"
        "3 Add Circle\n"
        "4 Add Triangle\n"
        "5 Delete\n"
        "6 Modify\n"
        "7 Display\n"
        "8 List\n"
        "9 Clear\n"
        "10 Exit\n"
        "Choice: "
    );
}

