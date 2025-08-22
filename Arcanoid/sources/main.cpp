#define WIDTH 65
#define HEIGHT 25

#include <algorithm>
#include <iostream>
#include <string>

// + 1 - это выделение места для символа конца строки
char playing_area[HEIGHT][WIDTH + 1];

void init(){
    for (int i = 0; i < WIDTH; i++){
        playing_area[0][i] = '#';

        // искусственно добавляем символ конца строки для корректного вывода
        playing_area[0][WIDTH] = '\0';
    }

    for (int i = 1; i < HEIGHT; i++){
        std::copy(playing_area[0], playing_area[0] + WIDTH + 1, playing_area[i]);
    }
}

void show(){
    for (int i = 0; i < HEIGHT; i++){
        std::cout << playing_area[i] << std::endl;
    }
}

int main(){
    init();
    show();
}