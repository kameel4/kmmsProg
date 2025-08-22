#define AREA_WIDTH 65
#define AREA_HEIGHT 25

#include <algorithm>
#include <iostream>
#include <string>

void init();
void init_racket();
void put_racket();
void show();
struct Tracket{
    int x, y;
    int width;
};

// + 1 - это выделение места для символа конца строки
char playing_area[AREA_HEIGHT][AREA_WIDTH + 1];
Tracket racket;

int main(){
    init();

    init_racket();
    put_racket();

    show();
}

void init(){
    for (int i = 0; i < AREA_WIDTH; i++){
        playing_area[0][i] = '#';

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
}

void init_racket(){
    racket.width = 7;

    // размещаем ракетку в центре поля, в самом низу
    racket.x = (AREA_WIDTH - racket.width) / 2;
    racket.y = AREA_HEIGHT - 1;
}

void put_racket(){
    for (int i = racket.x; i < racket.x + racket.width; i++){
        playing_area[racket.y][i] = '@';
    }
}

void show(){
    for (int i = 0; i < AREA_HEIGHT; i++){
        std::cout << playing_area[i] << std::endl;
    }
}

