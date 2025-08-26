#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <windows.h>


void auto_move_ball();
void init(int level);
void init_ball();
void init_racket();
void move_ball(float x, float y);
void move_racket(int x);
void put_ball();
void put_racket();
void set_cursor(int x, int y);
void show();
void show_preview();

struct TRacket{
    int x, y;
    int width;
};

struct TBall{
    float x, y;
    int int_x, int_y;
    // Альфа - угол полета шарика
    float alpha;
    float speed;
};

const int AREA_HEIGHT = 25;
const int AREA_WIDTH = 65;
const char RACKET_SYMBOL = '@';
const char WALL_SYMBOL = '#';

int level = 1;
int max_score = 0;
int score = 0;


// + 1 - это выделение места для символа конца строки
char playing_area[AREA_HEIGHT][AREA_WIDTH + 1];
TRacket racket;
TBall ball;

int main(){
    char pressed_key;
    bool ball_moving_itself = false;
    init_ball();
    init_racket();

    show_preview();
    do {
        set_cursor(0, 0);

        if (ball_moving_itself) auto_move_ball();
        if (ball.int_y > AREA_HEIGHT){
            ball_moving_itself = false;
            max_score = std::max(max_score, score);
            score = 0;
        }
        if (score > 3){
            level++;
            ball_moving_itself = false;
            max_score = 0;
            score = 0;
            show_preview();
        }

        init(level);
        put_ball();
        put_racket();
        show();

        if (GetKeyState('A') < 0) move_racket(racket.x - 1);
        if (GetKeyState('D') < 0) move_racket(racket.x + 1);
        if (GetKeyState('W') < 0) ball_moving_itself = true;
        if (!ball_moving_itself){
            move_ball(racket.x + racket.width / 2, racket.y - 1);
        }

        Sleep(10);

    } while (GetKeyState(VK_ESCAPE) >= 0);
    

}

void auto_move_ball(){
    if (ball.alpha < 0) ball.alpha += M_PI * 2;
    if (ball.alpha > M_PI * 2) ball.alpha -= M_PI * 2;

    TBall old_ball_state = ball;
    move_ball(
        ball.x + cos(ball.alpha) * ball.speed,
        ball.y + sin(ball.alpha) * ball.speed
    );

    // Проверка на столкновение со стеной либо с ракеткой
    if (playing_area[ball.int_y][ball.int_x] == WALL_SYMBOL || 
        playing_area[ball.int_y][ball.int_x] == RACKET_SYMBOL){

        if (playing_area[ball.int_y][ball.int_x] == RACKET_SYMBOL) score++;

        // Случай когда изменились обе координаты    
        if (ball.int_x != old_ball_state.int_x && ball.int_y != old_ball_state.int_y){
            // Случай, когда шар оказался в углу
            if (playing_area[old_ball_state.int_y][ball.int_x] == playing_area[ball.int_y][old_ball_state.int_x]){
                old_ball_state.alpha += M_PI;
            // Случай, когда шар у стены. Отражаем либо по вертикали, либо по горизонтали
            }else{
                if (playing_area[old_ball_state.int_y][ball.int_x] == WALL_SYMBOL){
                    old_ball_state.alpha = (2 * M_PI - old_ball_state.alpha) + M_PI;
                }else{
                    old_ball_state.alpha = (2 * M_PI - old_ball_state.alpha);
                }
            }
        // Случай изменения только одной координаты - Х, следовательно шар движется по горизонтали, 
        // а отразить его - по вертикали
        }else if (ball.int_y == old_ball_state.int_y){
            old_ball_state.alpha = (2 * M_PI - old_ball_state.alpha) + M_PI;
        // Случай изменения только одной координаты - Y, следовательно шар движется по вертикали, 
        // а отразить его - по горизонтали
        }else{
            old_ball_state.alpha = (2 * M_PI - old_ball_state.alpha);
        }

        ball = old_ball_state;
        auto_move_ball();
    }
}

void init(int level){
    for (int i = 0; i < AREA_WIDTH; i++){
        playing_area[0][i] = WALL_SYMBOL;

        // искусственно добавляем символ конца строки для корректного вывода
        playing_area[0][AREA_WIDTH] = '\0';
    }

    std::copy(playing_area[0], playing_area[0] + AREA_WIDTH + 1, playing_area[1]);

    for (int i = 1; i < AREA_WIDTH - 1; i++){
        playing_area[1][i] = ' ';
    }

    for (int i = 2; i < AREA_HEIGHT; i++){
        std::copy(playing_area[1], playing_area[1] + AREA_WIDTH + 1, playing_area[i]);
    }

    if (level == 2){
        for (int i = 10; i < AREA_HEIGHT; i++){
            playing_area[10][i] = WALL_SYMBOL;
        }
    }

    if (level == 3){
        for (int j = 1; j < 10; j++){
            for (int i = 1; i < 65; i +=7){
                playing_area[j][i] = WALL_SYMBOL;
            }
        }
    }
}

void init_ball(){
    // размещаем шарик в левом верхнем углу
    move_ball(2, 2);
    
    ball.alpha = -1;
    ball.speed = 0.5;
}

void init_racket(){
    racket.width = 12;

    // размещаем ракетку в центре поля, в самом низу
    racket.x = (AREA_WIDTH - racket.width) / 2;
    racket.y = AREA_HEIGHT - 1;
}

void move_ball(float x, float y){
    ball.x = x;
    ball.y = y;
    ball.int_x = (int)round(x);
    ball.int_y = (int)round(y);
}

void move_racket(int x){
    racket.x = x;
    // проверка попадания ракетки за границы поля
    if (racket.x < 1) racket.x = 1;
    if (racket.x + racket.width >= AREA_WIDTH) racket.x = AREA_WIDTH - 1 - racket.width;

}

void put_ball(){    
    playing_area[ball.int_y][ball.int_x] = '*';
}

void put_racket(){
    for (int i = racket.x; i < racket.x + racket.width; i++){
        playing_area[racket.y][i] = RACKET_SYMBOL;
    }
}

void set_cursor(int x, int y){
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;

    // Здесь первый аргумент - это указатель на окно вывода,
    // который мы получаем через стандартный геттер
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void show(){
    for (int i = 0; i < AREA_HEIGHT; i++){
        std::cout << playing_area[i];

        if (i == 2) std::cout << "      level:          " << level;
        if (i == 3) std::cout << "      score:          " << score;
        if (i == 4) std::cout << "      max score:      " << max_score;

        if (i < AREA_HEIGHT - 1) std::cout << std::endl;
    }
}

void show_preview(){
    system("cls");
    for (int i = 0; i < 12; i++) std::cout << std::endl;
    std::cout << "\t\t\t\t      LEVEL   " << level;
    Sleep(1000);
    system("cls");
}