#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#define mapHeight 25
#define mapWidth 80

struct Object{
    char cType;
    float height, width;
    float horizSpeed;
    BOOL IsFly;
    float vertSpeed;
    float x, y; 
};

char map[mapHeight][mapWidth + 1];

Object mario;
Object *brick = NULL;
int brickLength;
Object *moving = NULL;

int level = 1;
int maxLvl;
int movingLength;
int score;

void ClearMap(){
    for (int i = 0; i < mapWidth; i++){
        map[0][i] = ' ';
    }
    map[0][mapWidth] = '\0';

    for (int j = 1; j < mapHeight; j++){
        sprintf(map[j], map[0]);
    }   
}

void ShowMap(){
    map[mapHeight - 1][mapWidth - 1] = '\0';
    for (int j = 0; j < mapHeight; j++)
        std::cout << map[j];
}

void SeObjectPos(Object *obj, float xPos, float yPos){
    (*obj).x = xPos;
    (*obj).y = yPos;
}

void IniObject(Object *obj, float xPos, float yPos, float oWidth, float oHeight, char inType){
    SeObjectPos(obj, xPos, yPos);
    (*obj).cType = inType;
    (*obj).height = oHeight;
    (*obj).horizSpeed = 0.2;
    (*obj).vertSpeed = 0;
    (*obj).width = oWidth;
}

void CreateLevel(int lvl);

void PlayerDead(){
    system("color 4F");
    Sleep(500);
    CreateLevel(level);
}

BOOL IsCollision(Object o1, Object o2);
Object *GetNewMoving();

void VertMoveObject(Object *obj){
    (*obj).IsFly = TRUE;
    (*obj).vertSpeed += 0.05;
    SeObjectPos(obj, (*obj).x, (*obj).y + (*obj).vertSpeed );
    
    for (int i = 0; i < brickLength; i++){
        if (IsCollision( *obj, brick[i])){
            if (obj[0].vertSpeed > 0){obj[0].IsFly = FALSE;}
            
            if ((brick[i].cType == '?') && (obj[0].vertSpeed < 0) && (obj == &mario)){
                brick[i].cType = '-';
                IniObject(GetNewMoving(), brick[i].x, brick[i].y - 3, 3, 2, '$');
                moving[movingLength - 1].vertSpeed = -0.7;
            }

            (*obj).y -= (*obj).vertSpeed;
            (*obj).vertSpeed = 0;
            (*obj).IsFly = FALSE;
            
            if (brick[i].cType == '+'){   
                level++;
                if (level > maxLvl) level = 1;

                system("color 2F");
                Sleep(500);
                CreateLevel(level);
            }
            break;
        }
    }
}

void DeleteMoving(int i){
    movingLength--;
    moving[i] = moving[movingLength];
    moving = (Object*)realloc(moving, sizeof(*moving) * movingLength);
}

void MarioCollision(){
    for (int i = 0; i < movingLength; i++){
        if (IsCollision(mario, moving[i]))
        {
            if (moving[i].cType == 'o')
            {
                if (   (mario.IsFly == TRUE)
                    && (mario.vertSpeed > 0)
                    && (mario.y + mario.height < moving[i].y + moving[i].height * 0.5)
                    ){   
                    score += 50;
                    DeleteMoving(i);
                    i--;
                    continue;
                }else{
                    PlayerDead();
                }
            }

            if (moving[i].cType == '$'){
                score += 100;
                DeleteMoving(i);
                i--;
                continue;
            }
        }
    }
}

void HorizonMoveObject(Object *obj){
    obj[0].x += obj[0].horizSpeed;

    for (int i = 0; i < brickLength; i++){
        if (IsCollision(obj[0], brick[i])){
            obj[0].x -= obj[0].horizSpeed;
            obj[0].horizSpeed = -obj[0].horizSpeed;
            return;
        }
    }

    if (obj[0].cType == 'o'){
        Object tmp = *obj;
        VertMoveObject(&tmp);
        if (tmp.IsFly == TRUE){
            obj[0].x -= obj[0].horizSpeed;
            obj[0].horizSpeed = -obj[0].horizSpeed;
        }
    }
}

BOOL IsPosInMap(int x, int y){
    return (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight);
}

void PuObjectOnMap(Object obj){
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth = (int)round(obj.width);
    int iHeight = (int)round(obj.height);

    for (int i = ix; i < (ix + iWidth); i++){
        for (int j = iy; j < (iy + iHeight); j++){
            if (IsPosInMap(i, j)){
                map[j][i] = obj.cType;
            }
        }
    }
}

void setCur(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void HorizonMoveMap(float dx){   
    mario.x -= dx;
    for (int i = 0; i < brickLength; i++){
        if (IsCollision(mario, brick[i])){
            mario.x += dx;
            return;
        }
    }
    mario.x += dx;

    for (int i = 0; i < brickLength; i++){
        brick[i].x += dx;
    }
    for (int i = 0; i < movingLength; i++){
        moving[i].x += dx;
    }
}

BOOL IsCollision(Object o1, Object o2){
    return  (o1.x + o1.width > o2.x  && o1.x < o2.x + o2.width ) &&
            (o1.y + o1.height > o2.y && o1.y < o2.y + o2.height);
}

Object *GetNewBrick(){
    brickLength++;
    brick = (Object*)realloc(brick, sizeof(*brick) * brickLength);
    return brick + brickLength - 1;
}

Object *GetNewMoving(){
    movingLength++;
    moving = (Object*)realloc(moving, sizeof(*moving) * movingLength);
    return moving + movingLength - 1;
}

void PutScoreOnMap(){
    char c[30];
    sprintf(c, "Score: %d", score);
    int len = strlen(c);

    for (int i = 0; i < len; i++){
        map[1][i+5] = c[i];
    }
}

void CreateLevel(int lvl){   
    system("color 9F");
    IniObject(&mario, 39, 10, 3, 3, '@');

    brickLength = 0;
    brick = (Object*)malloc(0);
    movingLength = 0;
    moving = (Object*)malloc(0);

    score = 0;


    if (lvl == 1){   
        // Здесь табуляцией выделены блоки, подвешенные над соответсвующими островами
        IniObject(GetNewBrick(), 20, 20, 40, 5, '#');
            IniObject(GetNewBrick(), 30, 10, 5, 3, '?');
            IniObject(GetNewBrick(), 50, 10, 5, 3, '?');
        IniObject(GetNewBrick(), 60, 15, 40, 10, '#');
            IniObject(GetNewBrick(), 60, 5, 10, 3, '-');
            IniObject(GetNewBrick(), 70, 5, 5,  3, '?');
            IniObject(GetNewBrick(), 75, 5, 5,  3, '-');
            IniObject(GetNewBrick(), 80, 5, 5,  3, '?');
            IniObject(GetNewBrick(), 85, 5, 10, 3, '-');
        IniObject(GetNewBrick(), 100, 20, 20, 5,  '#');
        IniObject(GetNewBrick(), 120, 15, 10, 10, '#');
        IniObject(GetNewBrick(), 150, 20, 40, 5,  '#');
        IniObject(GetNewBrick(), 210, 15, 10, 10, '+');

        IniObject(GetNewMoving(), 25, 10, 3, 2, 'o');
        IniObject(GetNewMoving(), 80, 10, 3, 2, 'o');
    }else if (lvl == 2){
        IniObject(GetNewBrick(), 20,  20, 40, 5,  '#');
        IniObject(GetNewBrick(), 60,  15, 10, 10, '#');
        IniObject(GetNewBrick(), 80,  20, 20, 5,  '#');
        IniObject(GetNewBrick(), 120, 15, 10, 10, '#');
        IniObject(GetNewBrick(), 150, 20, 40, 5,  '#');
        IniObject(GetNewBrick(), 210, 15, 10, 10, '+');

        IniObject(GetNewMoving(), 25,  10, 3, 2, 'o');
        IniObject(GetNewMoving(), 80,  10, 3, 2, 'o');
        IniObject(GetNewMoving(), 65,  10, 3, 2, 'o');
        IniObject(GetNewMoving(), 120, 10, 3, 2, 'o');
        IniObject(GetNewMoving(), 160, 10, 3, 2, 'o');
        IniObject(GetNewMoving(), 175, 10, 3, 2, 'o');   
    }else if (lvl == 3){
        IniObject(GetNewBrick(), 20,  20, 40, 5,  '#');
        IniObject(GetNewBrick(), 80,  20, 15, 5,  '#');
        IniObject(GetNewBrick(), 120, 15, 15, 10, '#');
        IniObject(GetNewBrick(), 160, 10, 15, 15, '+');

        IniObject(GetNewMoving(), 25,  10, 3, 2, 'o');
        IniObject(GetNewMoving(), 50,  10, 3, 2, 'o');
        IniObject(GetNewMoving(), 80,  10, 3, 2, 'o');
        IniObject(GetNewMoving(), 90,  10, 3, 2, 'o');
        IniObject(GetNewMoving(), 120, 10, 3, 2, 'o');
        IniObject(GetNewMoving(), 130, 10, 3, 2, 'o');
    }

    maxLvl = 3;
}

void hide_cursor(){
    void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(handle, &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(handle, &structCursorInfo);

}

int main(){   
    hide_cursor();
    CreateLevel(level);

    do{   
        ClearMap();


        if (mario.IsFly == FALSE && GetKeyState(VK_SPACE) < 0){mario.vertSpeed = -1;}
        if (GetKeyState('A') < 0){HorizonMoveMap(1);}
        if (GetKeyState('D') < 0){HorizonMoveMap(-1);}
        if (mario.y > mapHeight){PlayerDead();}
 
        VertMoveObject(&mario);
        MarioCollision();

        for (int i = 0; i < brickLength; i++){
            PuObjectOnMap(brick[i]);
        }
        for (int i = 0; i < movingLength; i++){
            VertMoveObject(moving + i);
            HorizonMoveObject(moving + i);

            if (moving[i].y > mapHeight){
                DeleteMoving(i);
                i--;
                continue;
            }
            PuObjectOnMap(moving[i]);
        }

        PuObjectOnMap(mario);
        PutScoreOnMap();

        setCur(0, 0);
        ShowMap();

        Sleep(10);
    } while (GetKeyState(VK_ESCAPE >= 0));
}