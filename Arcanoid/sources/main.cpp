#define AREA_WIDTH 65
#define AREA_HEIGHT 25

#include <algorithm>
#include <conio.h>
#include <iostream>
#include <string>


void init();
void init_racket();
void move_racket(int x);
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
    char pressed_key;
    init_racket();

    do {
        system("cls");
        init();
        put_racket();
        show();

        pressed_key = getch();
        if (pressed_key == 'a') move_racket(racket.x - 1);
        if (pressed_key == 'd') move_racket(racket.x + 1);

    } while (pressed_key != 'q');
    

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

void move_racket(int x){
    racket.x = x;
    // проверка попадания ракетки за границы поля
    if (racket.x < 1) racket.x = 1;
    if (racket.x + racket.width >= AREA_WIDTH) racket.x = AREA_WIDTH - 1 - racket.width;

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

