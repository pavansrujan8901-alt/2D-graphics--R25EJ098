#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 30
#define COLS 60
#define MAX_OBJECTS 100

char canvas[ROWS][COLS];

typedef struct
{
    int type; // 1-Rectangle 2-Line 3-Triangle 4-Circle
    int p1, p2, p3, p4;
} Shape;

Shape shapes[MAX_OBJECTS];
int shapeCount = 0;

void clearCanvas()
{
    for(int i=0;i<ROWS;i++)
        for(int j=0;j<COLS;j++)
            canvas[i][j]='_';
}

void displayCanvas()
{
    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
            printf("%c",canvas[i][j]);
        printf("\n");
    }
}

void drawRectangle(int x,int y,int w,int h)
{
    for(int i=y;i<y+h && i<ROWS;i++)
    {
        for(int j=x;j<x+w && j<COLS;j++)
        {
            if(i==y || i==y+h-1 || j==x || j==x+w-1)
                canvas[i][j]='*';
        }
    }
}

void drawLine(int x1,int y1,int x2,int y2)
{
    int dx=abs(x2-x1);
    int dy=abs(y2-y1);

    int sx=(x1<x2)?1:-1;
    int sy=(y1<y2)?1:-1;

    int err=dx-dy;

    while(1)
    {
        if(x1>=0 && x1<COLS && y1>=0 && y1<ROWS)
            canvas[y1][x1]='*';

        if(x1==x2 && y1==y2)
            break;

        int e2=2*err;

        if(e2>-dy)
        {
            err-=dy;
            x1+=sx;
        }

        if(e2<dx)
        {
            err+=dx;
            y1+=sy;
        }
    }
}

void drawTriangle(int x,int y,int h)
{
    for(int i=0;i<h;i++)
    {
        if(y+i<ROWS)
        {
            if(x-i>=0)
                canvas[y+i][x-i]='*';

            if(x+i<COLS)
                canvas[y+i][x+i]='*';
        }
    }

    drawLine(x-h+1,y+h-1,x+h-1,y+h-1);
}

void drawCircle(int xc,int yc,int r)
{
    for(int y=0;y<ROWS;y++)
    {
        for(int x=0;x<COLS;x++)
        {
            int dx=x-xc;
            int dy=y-yc;

            double d=sqrt(dx*dx+dy*dy);

            if(d>=r-0.5 && d<=r+0.5)
                canvas[y][x]='*';
        }
    }
}

void redraw()
{
    clearCanvas();

    for(int i=0;i<shapeCount;i++)
    {
        switch(shapes[i].type)
        {
            case 1:
                drawRectangle(shapes[i].p1,shapes[i].p2,
                              shapes[i].p3,shapes[i].p4);
                break;

            case 2:
                drawLine(shapes[i].p1,shapes[i].p2,
                         shapes[i].p3,shapes[i].p4);
                break;

            case 3:
                drawTriangle(shapes[i].p1,shapes[i].p2,
                             shapes[i].p3);
                break;

            case 4:
                drawCircle(shapes[i].p1,shapes[i].p2,
                           shapes[i].p3);
                break;
        }
    }
}

void listObjects()
{
    printf("\nObjects:\n");

    for(int i=0;i<shapeCount;i++)
    {
        printf("%d. ",i+1);

        switch(shapes[i].type)
        {
            case 1: printf("Rectangle\n"); break;
            case 2: printf("Line\n"); break;
            case 3: printf("Triangle\n"); break;
            case 4: printf("Circle\n"); break;
        }
    }

    if(shapeCount==0)
        printf("No objects present.\n");
}

void deleteObject(int index)
{
    if(index<0 || index>=shapeCount)
    {
        printf("Invalid object number!\n");
        return;
    }

    for(int i=index;i<shapeCount-1;i++)
        shapes[i]=shapes[i+1];

    shapeCount--;
    redraw();
}

void modifyObject(int index)
{
    if(index<0 || index>=shapeCount)
    {
        printf("Invalid object number!\n");
        return;
    }

    Shape *s=&shapes[index];

    switch(s->type)
    {
        case 1:
            printf("Enter new x y width height: ");
            scanf("%d%d%d%d",&s->p1,&s->p2,&s->p3,&s->p4);
            break;

        case 2:
            printf("Enter new x1 y1 x2 y2: ");
            scanf("%d%d%d%d",&s->p1,&s->p2,&s->p3,&s->p4);
            break;

        case 3:
            printf("Enter new x y height: ");
            scanf("%d%d%d",&s->p1,&s->p2,&s->p3);
            break;

        case 4:
            printf("Enter new center_x center_y radius: ");
            scanf("%d%d%d",&s->p1,&s->p2,&s->p3);
            break;
    }

    redraw();
}

int main()
{
    int choice;

    clearCanvas();

    while(1)
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Add Rectangle\n");
        printf("2. Add Line\n");
        printf("3. Add Triangle\n");
        printf("4. Add Circle\n");
        printf("5. Delete Object\n");
        printf("6. Modify Object\n");
        printf("7. List Objects\n");
        printf("8. Display Canvas\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        if(choice==0)
            break;

        Shape s;
        int obj;

        switch(choice)
        {
            case 1:
                s.type=1;
                printf("Enter x y width height: ");
                scanf("%d%d%d%d",&s.p1,&s.p2,&s.p3,&s.p4);
                shapes[shapeCount++]=s;
                redraw();
                break;

            case 2:
                s.type=2;
                printf("Enter x1 y1 x2 y2: ");
                scanf("%d%d%d%d",&s.p1,&s.p2,&s.p3,&s.p4);
                shapes[shapeCount++]=s;
                redraw();
                break;

            case 3:
                s.type=3;
                printf("Enter x y height: ");
                scanf("%d%d%d",&s.p1,&s.p2,&s.p3);
                shapes[shapeCount++]=s;
                redraw();
                break;

            case 4:
                s.type=4;
                printf("Enter center_x center_y radius: ");
                scanf("%d%d%d",&s.p1,&s.p2,&s.p3);
                shapes[shapeCount++]=s;
                redraw();
                break;

            case 5:
                listObjects();
                printf("Enter object number to delete: ");
                scanf("%d",&obj);
                deleteObject(obj-1);
                break;

            case 6:
                listObjects();
                printf("Enter object number to modify: ");
                scanf("%d",&obj);
                modifyObject(obj-1);
                break;

            case 7:
                listObjects();
                break;

            case 8:
                displayCanvas();
                break;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}