#include <format>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

const int map_height = 25;
const int map_width = 80;

struct Object;

void clear_map();
void create_level(int level);
void delete_moving_object(int i);
Object *get_new_brick();
Object *get_new_moving();
void hide_cursor();
void horizontally_move_map(float delta_x);
void horizontally_move_object(Object *object);
void init_object(Object *object, float x_pos, float y_pos,
                 float object_width, float object_height, char display_symbol);
bool is_collision(Object object_1, Object object_2);
bool is_object_on_map(int x, int y);
void mario_collision();
void player_death();
void put_object_on_map(Object object);
void put_score_on_map();
void set_cursor_pos(int x, int y);
void set_object_pos(Object *object, float x_pos, float y_pos);
void show_map();
void vertically_move_object(Object *object);

char map[map_height][map_width + 1];

Object mario;
Object *bricks = NULL;
Object *moving = NULL;
int bricks_length;
int moving_length;

int level = 1;
int max_level;
int score;

int main(){   
    hide_cursor();
    create_level(level);

    do{   
        clear_map();


        if (mario.is_flying == false && GetKeyState(VK_SPACE) < 0){mario.vertical_speed = -1;}
        if (GetKeyState('A') < 0){horizontally_move_map( 1);}
        if (GetKeyState('D') < 0){horizontally_move_map(-1);}
        if (mario.y > map_height){player_death();}
 
        vertically_move_object(&mario);
        mario_collision();

        for (int i = 0; i < bricks_length; i++){
            put_object_on_map(bricks[i]);
        }
        for (int i = 0; i < moving_length; i++){
            vertically_move_object(moving + i);
            horizontally_move_object(moving + i);

            if (moving[i].y > map_height){
                delete_moving_object(i);
                i--;
                continue;
            }
            put_object_on_map(moving[i]);
        }

        put_object_on_map(mario);
        put_score_on_map();

        set_cursor_pos(0, 0);
        show_map();

        Sleep(10);
    } while (GetKeyState(VK_ESCAPE >= 0));
}

struct Object{
    char char_type;
    float height, width;
    float horizontal_speed;
    bool is_flying;
    float vertical_speed;
    float x, y; 
};

void clear_map(){
    for (int i = 0; i < map_width; i++){
        map[0][i] = ' ';
    }
    map[0][map_width] = '\0';

    for (int j = 1; j < map_height; j++){
        std::copy(map[0], map[0] + map_width, map[j]);
    }   
}

void create_level(int level){   
    system("color 9F");
    init_object(&mario, 39, 10, 3, 3, '@');

    bricks_length = 0;
    bricks = (Object*)malloc(0);
    moving_length = 0;
    moving = (Object*)malloc(0);

    score = 0;


    if (level == 1){   
        // Здесь табуляцией выделены блоки, подвешенные над соответсвующими островами
        init_object(get_new_brick(), 20, 20, 40, 5, '#');
            init_object(get_new_brick(), 30, 10, 5, 3, '?');
            init_object(get_new_brick(), 50, 10, 5, 3, '?');
        init_object(get_new_brick(), 60, 15, 40, 10, '#');
            init_object(get_new_brick(), 60, 5, 10, 3, '-');
            init_object(get_new_brick(), 70, 5, 5,  3, '?');
            init_object(get_new_brick(), 75, 5, 5,  3, '-');
            init_object(get_new_brick(), 80, 5, 5,  3, '?');
            init_object(get_new_brick(), 85, 5, 10, 3, '-');
        init_object(get_new_brick(), 100, 20, 20, 5,  '#');
        init_object(get_new_brick(), 120, 15, 10, 10, '#');
        init_object(get_new_brick(), 150, 20, 40, 5,  '#');
        init_object(get_new_brick(), 210, 15, 10, 10, '+');

        init_object(get_new_moving(), 25, 10, 3, 2, 'o');
        init_object(get_new_moving(), 80, 10, 3, 2, 'o');
    }else if (level == 2){
        init_object(get_new_brick(), 20,  20, 40, 5,  '#');
        init_object(get_new_brick(), 60,  15, 10, 10, '#');
        init_object(get_new_brick(), 80,  20, 20, 5,  '#');
        init_object(get_new_brick(), 120, 15, 10, 10, '#');
        init_object(get_new_brick(), 150, 20, 40, 5,  '#');
        init_object(get_new_brick(), 210, 15, 10, 10, '+');

        init_object(get_new_moving(), 25,  10, 3, 2, 'o');
        init_object(get_new_moving(), 80,  10, 3, 2, 'o');
        init_object(get_new_moving(), 65,  10, 3, 2, 'o');
        init_object(get_new_moving(), 120, 10, 3, 2, 'o');
        init_object(get_new_moving(), 160, 10, 3, 2, 'o');
        init_object(get_new_moving(), 175, 10, 3, 2, 'o');   
    }else if (level == 3){
        init_object(get_new_brick(), 20,  20, 40, 5,  '#');
        init_object(get_new_brick(), 80,  20, 15, 5,  '#');
        init_object(get_new_brick(), 120, 15, 15, 10, '#');
        init_object(get_new_brick(), 160, 10, 15, 15, '+');

        init_object(get_new_moving(), 25,  10, 3, 2, 'o');
        init_object(get_new_moving(), 50,  10, 3, 2, 'o');
        init_object(get_new_moving(), 80,  10, 3, 2, 'o');
        init_object(get_new_moving(), 90,  10, 3, 2, 'o');
        init_object(get_new_moving(), 120, 10, 3, 2, 'o');
        init_object(get_new_moving(), 130, 10, 3, 2, 'o');
    }

    max_level = 3;
}

void delete_moving_object(int i){
    moving_length--;
    moving[i] = moving[moving_length];
    moving = (Object*)realloc(moving, sizeof(*moving) * moving_length);
}

Object *get_new_brick(){
    bricks_length++;
    bricks = (Object*)realloc(bricks, sizeof(*bricks) * bricks_length);
    return bricks + bricks_length - 1;
}

Object *get_new_moving(){
    moving_length++;
    moving = (Object*)realloc(moving, sizeof(*moving) * moving_length);
    return moving + moving_length - 1;
}

void hide_cursor(){
    void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(handle, &structCursorInfo);
    structCursorInfo.bVisible = false;
    SetConsoleCursorInfo(handle, &structCursorInfo);
}

void horizontally_move_map(float delta_x){   
    mario.x -= delta_x;
    for (int i = 0; i < bricks_length; i++){
        if (is_collision(mario, bricks[i])){
            mario.x += delta_x;
            return;
        }
    }
    mario.x += delta_x;

    for (int i = 0; i < bricks_length; i++){
        bricks[i].x += delta_x;
    }
    for (int i = 0; i < moving_length; i++){
        moving[i].x += delta_x;
    }
}

void horizontally_move_object(Object *object){
    object[0].x += object[0].horizontal_speed;

    for (int i = 0; i < bricks_length; i++){
        if (is_collision(object[0], bricks[i])){
            object[0].x -= object[0].horizontal_speed;
            object[0].horizontal_speed = -object[0].horizontal_speed;
            return;
        }
    }

    if (object[0].char_type == 'o'){
        Object temp = *object;
        vertically_move_object(&temp);
        if (temp.is_flying == true){
            object[0].x -= object[0].horizontal_speed;
            object[0].horizontal_speed = -object[0].horizontal_speed;
        }
    }
}

void init_object(Object *object, float x_pos, float y_pos,
                 float object_width, float object_height, char display_symbol){

    set_object_pos(object, x_pos, y_pos);
    (*object).char_type = display_symbol;
    (*object).height = object_height;
    (*object).horizontal_speed = 0.2;
    (*object).vertical_speed = 0;
    (*object).width = object_width;
}

bool is_collision(Object object_1, Object object_2){
    return  (object_1.x + object_1.width > object_2.x  && object_1.x < object_2.x + object_2.width ) &&
            (object_1.y + object_1.height > object_2.y && object_1.y < object_2.y + object_2.height);
}

bool is_object_on_map(int x, int y){
    return (x >= 0 && x < map_width && y >= 0 && y < map_height);
}

void mario_collision(){
    for (int i = 0; i < moving_length; i++){
        if (is_collision(mario, moving[i]))
        {
            if (moving[i].char_type == 'o')
            {
                if (   (mario.is_flying == true)
                    && (mario.vertical_speed > 0)
                    && (mario.y + mario.height < moving[i].y + moving[i].height * 0.5)
                    ){   
                    score += 50;
                    delete_moving_object(i);
                    i--;
                    continue;
                }else{
                    player_death();
                }
            }

            if (moving[i].char_type == '$'){
                score += 100;
                delete_moving_object(i);
                i--;
                continue;
            }
        }
    }
}

void player_death(){
    system("color 4F");
    Sleep(500);
    create_level(level);
}

void put_object_on_map(Object object){
    int int_x = (int)round(object.x);
    int int_y = (int)round(object.y);
    int int_width = (int)round(object.width);
    int int_height = (int)round(object.height);

    for (int i = int_x; i < (int_x + int_width); i++){
        for (int j = int_y; j < (int_y + int_height); j++){
            if (is_object_on_map(i, j)){
                map[j][i] = object.char_type;
            }
        }
    }
}

void put_score_on_map(){
    // Для поддержки std::format необходим 20ый стандарт c++
    std::string score_string = std::format("Score: {}", score);
    int score_string_len = score_string.size();
    for (int i = 0; i < score_string_len; i++){
        map[1][i+5] = score_string[i];
    }
}

void set_cursor_pos(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void set_object_pos(Object *object, float x_pos, float y_pos){
    (*object).x = x_pos;
    (*object).y = y_pos;
}

void show_map(){
    map[map_height - 1][map_width - 1] = '\0';
    for (int j = 0; j < map_height; j++)
        std::cout << map[j];
}

void vertically_move_object(Object *object){
    (*object).is_flying = true;
    (*object).vertical_speed += 0.05;
    set_object_pos(object, (*object).x, (*object).y + (*object).vertical_speed);
    
    for (int i = 0; i < bricks_length; i++){
        if (is_collision(*object, bricks[i])){
            if (object[0].vertical_speed > 0){object[0].is_flying = false;}
            
            if ((bricks[i].char_type == '?') && (object[0].vertical_speed < 0) && (object == &mario)){
                bricks[i].char_type = '-';
                init_object(get_new_moving(), bricks[i].x, bricks[i].y - 3, 3, 2, '$');
                moving[moving_length - 1].vertical_speed = -0.7;
            }

            (*object).y -= (*object).vertical_speed;
            (*object).vertical_speed = 0;
            (*object).is_flying = false;
            
            if (bricks[i].char_type == '+'){   
                level++;
                if (level > max_level) level = 1;

                system("color 2F");
                Sleep(500);
                create_level(level);
            }
            break;
        }
    }
}