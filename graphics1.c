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
