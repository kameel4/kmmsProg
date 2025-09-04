#include <format>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

const int map_height = 25;
const int map_width = 80;

struct Object{
    char char_type;
    float height, width;
    float horizontal_speed;
    bool is_flying;
    float vertical_speed;
    float x, y; 
};

void clear_map(char map[map_height][map_width + 1]);
void create_level(int &level, Object& mario, int& bricks_length, Object *&bricks,
                  int& moving_length, Object *&moving, int &score, int &max_level);
void delete_moving_object(const int i, int &moving_length, Object *&moving);
Object *get_new_brick(int &bricks_length, Object *&bricks);
Object *get_new_moving(int &moving_length, Object *&moving);
void hide_cursor();
void horizontally_move_map(const float delta_x, Object& mario, Object *&bricks,
                           int &bricks_length, Object *&moving, int &moving_length);
void horizontally_move_object(Object *object, int &bricks_length, Object *&bricks, Object& mario,
                              Object *&moving, int &moving_length, int &level,
                              int &max_level, int &score);
void init_object(Object *object, const float x_pos, const float y_pos,
                 const float object_width, const float object_height, const char display_symbol);
bool is_collision(const Object object_1, const Object object_2);
bool is_object_on_map(const int x, const int y);
void mario_collision(int &moving_length, Object &mario, Object *&moving, int &score, int &level,
                     int &bricks_length, Object *&bricks, int &max_level);
void player_death(int &level);
void put_object_on_map(const Object object, char map[map_height][map_width + 1]);
void put_score_on_map(char map[map_height][map_width + 1], int &score);
void set_cursor_pos(const int x, const int y);
void set_object_pos(Object *object, const float x_pos, const float y_pos);
void show_map(char map[map_height][map_width + 1]);
void vertically_move_object(Object *object, Object& mario, Object *&bricks, int &bricks_length,
                            Object *&moving, int &moving_length, int &level, int &max_level,
                            int &score);

int main(){
    char map[map_height][map_width + 1];

    Object mario;
    Object *bricks = nullptr;
    Object *moving = nullptr;
    int bricks_length;
    int moving_length;

    int level = 1;
    int max_level = 3;
    int score;

    hide_cursor();
    create_level(level, mario, bricks_length, bricks, moving_length, moving,
                 score, max_level);

    do{   
        clear_map(map);


        if (mario.is_flying == false && GetKeyState(VK_SPACE) < 0){mario.vertical_speed = -1;}
        if (GetKeyState('A') < 0){horizontally_move_map(1,
             mario, bricks, bricks_length, moving, moving_length);}
        if (GetKeyState('D') < 0){horizontally_move_map(-1,
             mario, bricks, bricks_length, moving, moving_length);}
        if (mario.y > map_height){
            player_death(level);
            create_level(level, mario, bricks_length, bricks, moving_length, moving,
                 score, max_level);
        }
 
        vertically_move_object(&mario, mario,
             bricks, bricks_length, moving, moving_length, level, max_level, score);
        mario_collision(moving_length, mario, moving, score, level, bricks_length, bricks,
                        max_level);

        for (int i = 0; i < bricks_length; i++){
            put_object_on_map(bricks[i], map);
        }
        for (int i = 0; i < moving_length; i++){
            vertically_move_object(moving + i, mario,
                bricks, bricks_length, moving, moving_length, level, max_level, score);
            horizontally_move_object(moving + i,
                bricks_length, bricks, mario, moving, moving_length, level, max_level, score);

            if (moving[i].y > map_height){
                delete_moving_object(i, moving_length, moving);
                i--;
                continue;
            }
            put_object_on_map(moving[i], map);
        }

        put_object_on_map(mario, map);
        put_score_on_map(map, score);

        set_cursor_pos(0, 0);
        show_map(map);

        Sleep(10);
    } while (GetKeyState(VK_ESCAPE >= 0));
}

void clear_map(char map[map_height][map_width + 1]){
    for (int i = 0; i < map_width; i++){
        map[0][i] = ' ';
    }
    map[0][map_width] = '\0';

    for (int j = 1; j < map_height; j++){
        std::copy(map[0], map[0] + map_width + 1, map[j]);
    }   
}

void create_level(int &level, Object& mario, int& bricks_length, Object *&bricks,
                  int& moving_length, Object *&moving, int &score, int &max_level){   
    system("color 9F");
    init_object(&mario, 39, 10, 3, 3, '@');
                    
    bricks_length = 0;
    bricks = (Object*)malloc(bricks_length);
    moving_length = 0;
    moving = (Object*)malloc(moving_length);

    score = 0;


    if (level == 1){   
        // Здесь табуляцией выделены блоки, подвешенные над соответсвующими островами
        init_object(get_new_brick(bricks_length, bricks), 20, 20, 40, 5, '#');
            init_object(get_new_brick(bricks_length, bricks), 30, 10, 5, 3, '?');
            init_object(get_new_brick(bricks_length, bricks), 50, 10, 5, 3, '?');
        init_object(get_new_brick(bricks_length, bricks), 60, 15, 40, 10, '#');
            init_object(get_new_brick(bricks_length, bricks), 60, 5, 10, 3, '-');
            init_object(get_new_brick(bricks_length, bricks), 70, 5, 5,  3, '?');
            init_object(get_new_brick(bricks_length, bricks), 75, 5, 5,  3, '-');
            init_object(get_new_brick(bricks_length, bricks), 80, 5, 5,  3, '?');
            init_object(get_new_brick(bricks_length, bricks), 85, 5, 10, 3, '-');
        init_object(get_new_brick(bricks_length, bricks), 100, 20, 20, 5,  '#');
        init_object(get_new_brick(bricks_length, bricks), 120, 15, 10, 10, '#');
        init_object(get_new_brick(bricks_length, bricks), 150, 20, 40, 5,  '#');
        init_object(get_new_brick(bricks_length, bricks), 210, 15, 10, 10, '+');

        init_object(get_new_moving(moving_length, moving), 25, 10, 3, 2, 'o');
        init_object(get_new_moving(moving_length, moving), 80, 10, 3, 2, 'o');
    }else if (level == 2){
        init_object(get_new_brick(bricks_length, bricks), 20,  20, 40, 5,  '#');
        init_object(get_new_brick(bricks_length, bricks), 60,  15, 10, 10, '#');
        init_object(get_new_brick(bricks_length, bricks), 80,  20, 20, 5,  '#');
        init_object(get_new_brick(bricks_length, bricks), 120, 15, 10, 10, '#');
        init_object(get_new_brick(bricks_length, bricks), 150, 20, 40, 5,  '#');
        init_object(get_new_brick(bricks_length, bricks), 210, 15, 10, 10, '+');

        init_object(get_new_moving(moving_length, moving), 25,  10, 3, 2, 'o');
        init_object(get_new_moving(moving_length, moving), 80,  10, 3, 2, 'o');
        init_object(get_new_moving(moving_length, moving), 65,  10, 3, 2, 'o');
        init_object(get_new_moving(moving_length, moving), 120, 10, 3, 2, 'o');
        init_object(get_new_moving(moving_length, moving), 160, 10, 3, 2, 'o');
        init_object(get_new_moving(moving_length, moving), 175, 10, 3, 2, 'o');   
    }else if (level == 3){
        init_object(get_new_brick(bricks_length, bricks), 20,  20, 40, 5,  '#');
        init_object(get_new_brick(bricks_length, bricks), 80,  20, 15, 5,  '#');
        init_object(get_new_brick(bricks_length, bricks), 120, 15, 15, 10, '#');
        init_object(get_new_brick(bricks_length, bricks), 160, 10, 15, 15, '+');

        init_object(get_new_moving(moving_length, moving), 25,  10, 3, 2, 'o');
        init_object(get_new_moving(moving_length, moving), 50,  10, 3, 2, 'o');
        init_object(get_new_moving(moving_length, moving), 80,  10, 3, 2, 'o');
        init_object(get_new_moving(moving_length, moving), 90,  10, 3, 2, 'o');
        init_object(get_new_moving(moving_length, moving), 120, 10, 3, 2, 'o');
        init_object(get_new_moving(moving_length, moving), 130, 10, 3, 2, 'o');
    }

    max_level = 3;
}

void delete_moving_object(const int i, int &moving_length, Object *&moving){
    moving_length--;
    moving[i] = moving[moving_length];
    moving = (Object*)realloc(moving, sizeof(*moving) * moving_length);
}

Object *get_new_brick(int &bricks_length, Object *&bricks){
    bricks_length++;
    bricks = (Object*)realloc(bricks, sizeof(*bricks) * bricks_length);
    return bricks + bricks_length - 1;
}

Object *get_new_moving(int &moving_length, Object *&moving){
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

void horizontally_move_map(const float delta_x, Object& mario, Object *&bricks,
                           int &bricks_length, Object *&moving, int &moving_length){   
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

void horizontally_move_object(Object *object, int &bricks_length, Object *&bricks, Object& mario,
                              Object *&moving, int &moving_length, int &level,
                              int &max_level, int &score){
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
        vertically_move_object(&temp, mario,
            bricks, bricks_length, moving, moving_length, level, max_level, score);
        if (temp.is_flying == true){
            object[0].x -= object[0].horizontal_speed;
            object[0].horizontal_speed = -object[0].horizontal_speed;
        }
    }
}

void init_object(Object *object, const float x_pos, const float y_pos,
                 const float object_width, const float object_height, const char display_symbol){

    set_object_pos(object, x_pos, y_pos);
    (*object).char_type = display_symbol;
    (*object).height = object_height;
    (*object).horizontal_speed = 0.2;
    (*object).vertical_speed = 0;
    (*object).width = object_width;
}

bool is_collision(const Object object_1, const Object object_2){
    return  (object_1.x + object_1.width > object_2.x  && object_1.x < object_2.x + object_2.width) 
            &&
            (object_1.y + object_1.height > object_2.y && object_1.y < object_2.y + object_2.height);
}

bool is_object_on_map(const int x, const int y){
    return (x >= 0 && x < map_width && y >= 0 && y < map_height);
}

void mario_collision(int &moving_length, Object &mario, Object *&moving, int &score, int &level,
                     int &bricks_length, Object *&bricks, int &max_level){
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
                    delete_moving_object(i, moving_length, moving);
                    i--;
                    continue;
                }else{
                    player_death(level);
                    create_level(level, mario, bricks_length, bricks, moving_length, moving,
                                 score, max_level);
                }
            }

            if (moving[i].char_type == '$'){
                score += 100;
                delete_moving_object(i, moving_length, moving);
                i--;
                continue;
            }
        }
    }
}

void player_death(int &level){
    system("color 4F");
    Sleep(500);
}

void put_object_on_map(const Object object, char map[map_height][map_width + 1]){
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

void put_score_on_map(char map[map_height][map_width + 1], int &score){
    // Для поддержки std::format необходим 20ый стандарт c++
    std::string score_string = std::format("Score: {}", score);
    int score_string_len = score_string.size();
    for (int i = 0; i < score_string_len; i++){
        map[1][i+5] = score_string[i];
    }
}

void set_cursor_pos(const int x, const int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void set_object_pos(Object *object, const float x_pos, const float y_pos){
    (*object).x = x_pos;
    (*object).y = y_pos;
}

void show_map(char map[map_height][map_width + 1]){
    map[map_height - 1][map_width - 1] = '\0';
    for (int j = 0; j < map_height; j++)
        std::cout << map[j];
}

void vertically_move_object(Object *object, Object& mario, Object *&bricks, int &bricks_length,
                            Object *&moving, int &moving_length, int &level, int &max_level,
                            int &score){
    (*object).is_flying = true;
    (*object).vertical_speed += 0.05;
    set_object_pos(object, (*object).x, (*object).y + (*object).vertical_speed);
    
    for (int i = 0; i < bricks_length; i++){
        if (is_collision(*object, bricks[i])){
            if (object[0].vertical_speed > 0){object[0].is_flying = false;}
            
            if ((bricks[i].char_type == '?') && (object[0].vertical_speed < 0) && (object == &mario)){
                bricks[i].char_type = '-';
                init_object(get_new_moving(moving_length, moving), bricks[i].x, bricks[i].y - 3, 3, 2, '$');
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
                create_level(level, mario, bricks_length, bricks, moving_length, moving,
                     score, max_level);
            }
            break;
        }
    }
}