#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <windows.h>

#define mapWidth 80
#define mapHeight 25

typedef struct SObject{
    float x,y;
    float width, height;
    float vertSpeed;
    bool IsFly;
    char cType; 
} TObject;

char map[mapHeight][mapWidth+1];
TObject mario;
TObject *brick = NULL;
int brickLength;

TObject *moving = NULL;
int movingLength;
int level = 1;


void ClearMap()
{
    for (int i = 0; i < mapWidth; i++)
        map[0][i] = ' ';
    map[0][mapWidth] = '\0';
    for (int j = 1; j < mapHeight; j++)
        sprintf(map[j], map[0]);
}

void ShowMap()
{
    map[mapHeight - 1][mapWidth - 1] = '\0';
    for (int j = 0; j < mapHeight; j++)
        std::cout << map[j];
}

void SetObjectPos(TObject *obj, float xPos, float yPos){
    (*obj).x = xPos;
    (*obj).y = yPos;
}

void InitObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeight, char inType){
    SetObjectPos(obj, xPos, yPos);
    (*obj).width = oWidth;
    (*obj).height = oHeight;
    (*obj).vertSpeed = 0;
    (*obj).cType = inType;
}

bool IsCollision(TObject o1, TObject o2);

void CreateLevel(int lvl);

void VertMoveObject(TObject *obj)
{
    (*obj).IsFly = true;
    (*obj).vertSpeed += 0.05;
    SetObjectPos(obj, (*obj).x, (*obj).y + (*obj).vertSpeed );
    for (int i = 0; i < brickLength; i++)
    {
        if (IsCollision( *obj, brick[i]))
        {
            (*obj).y -= (*obj).vertSpeed;
            (*obj).vertSpeed = 0;
            (*obj).IsFly = FALSE;
            if (brick[i].cType == '+')
            {   
                level++;
                if (level > 2) level = 1;
                CreateLevel(level);
                Sleep(1000);
            }
            break;
        }
    }
}

bool IsPosInMap(int x, int y){
    return ( (x >= 0) && (x <= mapWidth) && (y >= 0) && (y <= mapHeight) );
}

void PutObjectOnMap(TObject obj)
{
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth = (int)round(obj.width);
    int iHeight = (int)round(obj.height);
    for (int i = ix; i < (ix + iWidth); i++)
        for (int j = iy; j < (iy + iHeight); j++)
            if (IsPosInMap(i, j))
                map[j][i] = obj.cType;
}

void setCur(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void HorizonMoveMap(float dx)
{   
    mario.x -= dx;
    for (int i = 0; i < brickLength; i++)
        if (IsCollision(mario, brick[i]))
        {
            mario.x += dx;
            return;
        }
    mario.x += dx;
    for (int i = 0; i < brickLength; i++)
        brick[i].x += dx;

}

bool IsCollision(TObject o1, TObject o2)
{
    return ( ((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) &&
             ((o1.y + o1.height) > o2.y) && (o1.y) < (o2.y + o2.width) );
}

void CreateLevel(int lvl)
{
    InitObject(&mario, 39, 10, 3, 3, '@');

    if (lvl == 1)
    {
        brickLength = 6;
        brick = (TObject*)malloc(sizeof(*brick) * brickLength );
        InitObject(brick + 0, 20, 20, 40, 5, '#');
        InitObject(brick + 1, 60, 15, 10, 10, '#');
        InitObject(brick + 2, 80, 20, 20, 5, '#');
        InitObject(brick + 3, 120, 15, 10, 10, '#');
        InitObject(brick + 4, 150, 20, 40, 5, '#');
        InitObject(brick + 5, 210, 15, 10, 10, '+'); 
        movingLength = 1;
        moving = (TObject*)malloc(sizeof(*moving) * movingLength);
        InitObject(moving+0, 25, 10, 3, 2, 'o');   
    }
    if (lvl == 2)
    {
        brickLength = 4;
        brick = (TObject*)malloc(sizeof(*brick) * brickLength );
        InitObject(brick + 0, 20, 20, 40, 5, '#');
        InitObject(brick + 1, 80, 20, 15, 5, '#');
        InitObject(brick + 2, 120, 15, 15, 10, '#');
        InitObject(brick + 3, 160, 10, 15, 15, '+');
    }

    

}

void hide_cursor(){
    void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(handle, &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(handle, &structCursorInfo);

}

int main()
{   
    hide_cursor();
    CreateLevel(level);
    system("color 9F");

    do
    {   
        ClearMap();


        if (mario.IsFly == false && GetKeyState(VK_SPACE) < 0) mario.vertSpeed = -1;
        if (GetKeyState('A') < 0) HorizonMoveMap(1);
        if (GetKeyState('D') < 0) HorizonMoveMap(-1);

        if (mario.y > mapHeight) CreateLevel(level);
 
        VertMoveObject(&mario);
        for (int i = 0; i < brickLength; i++)
            PutObjectOnMap(brick[i]);
        for (int i = 0; i < movingLength; i++)
            PutObjectOnMap(moving[i]);
        PutObjectOnMap(mario);
        setCur(0, 0);
        ShowMap();

        Sleep(10);
    } while (GetKeyState(VK_ESCAPE >= 0));

    return 0;
}