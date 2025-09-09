/*
1) Забыл про хардкод, строки - в переменные 
(Я не знаю почему не вспомнил об этом,
во время рефакторинга арканоида я выносил строки и
помнил о этом )
  
2) Касательно объявлений, я точно знал, что без переносов
строк это выглядит страшно и нечитабельно, но не знал
как именно стоит оформить. До этого мы не встречались
с таким большим кол-вом аргументов и методов

2.1) При вызове методов с большим кол-вом аргументов,
соотвественно, вид тоже был страшный

3) Switch-case для level == 1/2/3

4) Передача матрицы - матрица и размерность

5) Освобождение памяти - delete[]

6) Ну и очевидно, выбор способов передачи аргументов с ошибками,
нужно больше опыта
*/

/**
	1. https://www.youtube.com/watch?v=7sTPrktLLBo&list=PLBOPkQsFLCR2DWRY74L03FmbRtz_Yy73_&index=30
	2. https://www.youtube.com/watch?v=8QDgZ3GNlt8&list=PLBOPkQsFLCR2DWRY74L03FmbRtz_Yy73_&index=34
*/

#include <cstring>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

const char BRICK = '#';
const char EMPTY_BOX = '-';
const char ENEMY = 'o';
const char FULL_BOX = '?';
const char MARIO = '@';
const char MONEY = '$';
const char WIN_BRICK = '+';

struct TObject {
	float x, y;
	float width, height;
	float vert_speed;
	float horiz_speed;
	bool is_fly;
	char ctype;
};

void check_mario_collisions(
	TObject& mario, 
	TObject *&bricks, int& bricks_count,
	TObject *&movings, int& movings_count,
	const int current_level,
	int& score
);
void clear_map(char **map, const int width, const int height);
void create_current_level(
	const int current_level, 
	TObject& mario, 
	TObject *&bricks, int& bricks_count, 
	TObject *&movings, int& movings_count,
	int& score
);
void delete_movings(const int i, TObject *movings, int& movings_count);
void hide_cursor();
void init_obj(
	TObject* obj, 
	const float xpos, const float ypos, 
	const float owidth, const float oheight, 
	const char inType
);
bool is_collision(TObject* obj1, TObject* obj2);
bool is_on_map(const int x, const int y, const int width, const int height);
void move_map_horizontally(
	const float dx, 
	TObject& mario, 
	TObject *bricks, const int bricks_count, 
	TObject *movings, int& movings_count
);
void move_obj_horizontally(
	TObject* obj, 
	TObject& mario, 
	TObject *&bricks, int& bricks_count, 
	TObject *&movings, int& movings_count,
	int& current_level,
	const int max_level,
	int& score
);
void move_obj_vertically(
	TObject* obj, 
	TObject& mario, 
	TObject *&bricks, int& bricks_count, 
	TObject *&movings, int& movings_count,
	int& current_level,
	const int max_level,
	int& score
);
void put_obj_on_map(TObject* obj, char **map, const int width, const int height);
void put_score_on_map(char **map, const int score);
void rerun_level(
	TObject& mario, 
	TObject *bricks, int& bricks_count, 
	TObject *movings, int& movings_count,
	const int current_level,
	int& score
);
void set_cursor_position(const int x, const int y);
void set_obj_position(TObject* obj, const float xpos, const float ypos);
void show_map(char **map, const int width, const int height);

int main() {
	hide_cursor();
	
	const int map_width = 80;
	const int map_height = 25;
	char **map = new char* [map_height];
	for (int i = 0; i < map_height; i++) {
		map[i] = new char[map_width + 1];
	}
	
	TObject mario;
	
	TObject *bricks = nullptr;
	int bricks_count;
	
	TObject *movings = nullptr;
	int movings_count;
	
	int current_level = 1;
	const int max_level = 3;
	int score;
	
	create_current_level(
		current_level,
		mario, 
		bricks, bricks_count, 
		movings, movings_count,
		score);
	
	const int jump_key = VK_SPACE;
	const int exit_key = VK_ESCAPE;
	const char left_direction_key = 'A';
	const char right_direction_key = 'D';
	do {
		clear_map(map, map_width, map_height);
		
		if (mario.is_fly == false && GetKeyState(jump_key) < 0) {
			mario.vert_speed = -1;
		}
		if (GetKeyState(left_direction_key) < 0) {
			move_map_horizontally(
				1, 
				mario, 
				bricks, bricks_count, 
				movings, movings_count);
		}
		if (GetKeyState(right_direction_key) < 0) {
			move_map_horizontally(
				-1, 
				mario, 
				bricks, bricks_count, 
				movings, movings_count);
		}
		if (mario.y > map_height) {
			rerun_level(
				mario, 
				bricks, bricks_count, 
				movings, movings_count, 
				current_level,  
				score);
		}
		
		move_obj_vertically(
			&mario, mario, 
			bricks, bricks_count, 
			movings, movings_count, 
			current_level, max_level, 
			score);
		check_mario_collisions(
			mario, 
			bricks, bricks_count, 
			movings, movings_count, 
			current_level, score);
		
		for (int i = 0; i < bricks_count; i++) {
			put_obj_on_map(&bricks[i], map, map_width, map_height);
		}
		
		for (int i = 0; i < movings_count; i++) {
			move_obj_vertically(
				&movings[i], 
				mario, 
				bricks, bricks_count, 
				movings, movings_count, 
				current_level, max_level, 
				score);
			move_obj_horizontally(
				&movings[i], 
				mario, 
				bricks, bricks_count, 
				movings, movings_count, 
				current_level, max_level, 
				score);
			if (movings[i].y > map_height) {
				delete_movings(i, movings, movings_count);
				i--;
				continue;
			}
			put_obj_on_map(&movings[i], map, map_width, map_height);
		}

		put_obj_on_map(&mario, map, map_width, map_height);
		put_score_on_map(map, score);
		
		set_cursor_position(0, 0);
		show_map(map, map_width, map_height);
		
		Sleep(10);
	} while (GetKeyState(exit_key) >= 0);
	
	for (int i = 0; i < map_height; i++) {
		delete [] map[i];
	}
	delete [] map;
	
	delete [] bricks;
	delete [] movings;
	
	return 0;
}

void check_mario_collisions(
	TObject& mario, 
	TObject *&bricks, int& bricks_count, 
	TObject *&movings, int& movings_count,
	const int current_level,
	int& score
) {
	for (int i = 0; i < movings_count; i++) {
		if (is_collision(&mario, &movings[i])) {
			if (movings[i].ctype == ENEMY) {
				if (
					mario.is_fly == true && 
					mario.vert_speed > 0 &&
					mario.y + mario.height < movings[i].y + movings[i].height * 0.5
				) {
					score += 50;
					delete_movings(i, movings, movings_count);
					i--;
					continue;
				}
				else rerun_level(
					mario, 
					bricks, bricks_count, 
					movings, movings_count, 
					current_level,  
					score);
			}
			
			if (movings[i].ctype == MONEY) {
				score += 100;
				delete_movings(i, movings, movings_count);
				i--;
				continue;
			}
		}
	}
}

void clear_map(char **map, const int width, const int height) {
	for (int i = 0; i < width; i++) {
		map[0][i] = ' ';
	}
	map[0][width] = '\0';
	for (int j = 1; j < height; j++) {
		sprintf(map[j], map[0]);
	}
}

void create_current_level(
	const int current_level, 
	TObject& mario, 
	TObject *&bricks, int& bricks_count,
	TObject *&movings, int& movings_count,
	int& score
) {
	system("color 9F");
	
	delete [] bricks;
	bricks = nullptr;
	delete [] movings;
	movings = nullptr;

	init_obj(&mario, 39, 10, 3, 3, '@');
	score = 0;
	
	switch (current_level) {
		case 1:
			bricks_count = 13;
			bricks = new TObject[bricks_count];
			
			init_obj(&bricks[0], 20, 20, 40, 5, BRICK);
			
			init_obj(&bricks[1], 30, 10, 5, 3, FULL_BOX);
			init_obj(&bricks[2], 50, 10, 5, 3, FULL_BOX);
			
			init_obj(&bricks[3], 60, 15, 40, 10, BRICK);
			
			init_obj(&bricks[4], 60, 5, 10, 3, EMPTY_BOX);
			init_obj(&bricks[5], 70, 5, 5, 3, FULL_BOX);
			init_obj(&bricks[6], 75, 5, 5, 3, EMPTY_BOX);
			init_obj(&bricks[7], 80, 5, 5, 3, FULL_BOX);
			init_obj(&bricks[8], 85, 5, 10, 3, EMPTY_BOX);
			
			init_obj(&bricks[9], 100, 20, 20, 5, BRICK);
			init_obj(&bricks[10], 120, 15, 10, 10, BRICK);
			init_obj(&bricks[11], 150, 20, 40, 5, BRICK);
			init_obj(&bricks[12], 210, 15, 10, 10, WIN_BRICK);
			
			movings_count = 2;
			movings = new TObject[movings_count];
			
			init_obj(&movings[0], 25, 10, 3, 2, ENEMY);
			init_obj(&movings[1], 80, 10, 3, 2, ENEMY);
			break;
		case 2:
			bricks_count = 6;
			bricks = new TObject[bricks_count];
			
			init_obj(&bricks[0], 20, 20, 40, 5, BRICK);
			init_obj(&bricks[1], 60, 15, 10, 10, BRICK);
			init_obj(&bricks[2], 80, 20, 20, 5, BRICK);
			init_obj(&bricks[3], 120, 15, 10, 10, BRICK);
			init_obj(&bricks[4], 150, 20, 40, 5, BRICK);
			init_obj(&bricks[5], 210, 15, 10, 10, WIN_BRICK);

			movings_count = 6;
			movings = new TObject[movings_count];
			
			init_obj(&movings[0], 25, 10, 3, 2, ENEMY);
			init_obj(&movings[1], 80, 10, 3, 2, ENEMY);
			init_obj(&movings[2], 65, 10, 3, 2, ENEMY);
			init_obj(&movings[3], 120, 10, 3, 2, ENEMY);
			init_obj(&movings[4], 160, 10, 3, 2, ENEMY);
			init_obj(&movings[5], 175, 10, 3, 2, ENEMY);
			break;
		case 3:
			bricks_count = 4;
			bricks = new TObject[bricks_count];
			
			init_obj(&bricks[0], 20, 20, 40, 5, BRICK);
			init_obj(&bricks[1], 80, 20, 15, 5, BRICK);
			init_obj(&bricks[2], 120, 15, 15, 10, BRICK);
			init_obj(&bricks[3], 160, 10, 15, 15, WIN_BRICK);
			
			movings_count = 6;
			movings = new TObject[movings_count];

			init_obj(&movings[0], 25, 10, 3, 2, ENEMY);
			init_obj(&movings[1], 50, 10, 3, 2, ENEMY);
			init_obj(&movings[2], 80, 10, 3, 2, ENEMY);
			init_obj(&movings[3], 90, 10, 3, 2, ENEMY);
			init_obj(&movings[4], 120, 10, 3, 2, ENEMY);
			init_obj(&movings[5], 135, 10, 3, 2, ENEMY);
			break;
		default: 
			break;
	}
}

void delete_movings(const int i, TObject *movings, int& movings_count) {
	movings_count--;
	movings[i] = movings[movings_count];
}

void hide_cursor() {
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO struct_cursor_info;
	GetConsoleCursorInfo(handle, &struct_cursor_info);
	struct_cursor_info.bVisible = false;
	SetConsoleCursorInfo(handle, &struct_cursor_info);
}

void init_obj(
	TObject* obj, 
	const float xpos, const float ypos, 
	const float owidth, const float oheight, 
	const char inType
) {
	set_obj_position(obj, xpos, ypos);
	obj->width = owidth;
	obj->height = oheight;
	obj->vert_speed = 0;
	obj->ctype = inType;
	obj->horiz_speed = 0.2;
}

bool is_collision(TObject* obj1, TObject* obj2) {
	return (
		obj1->x + obj1->width > obj2->x && 
		obj1->x < obj2->x + obj2->width &&
		obj1->y + obj1->height > obj2->y && 
		obj1->y < obj2->y + obj2->height
	);
}

bool is_on_map(const int x, const int y, const int width, const int height) {
	return x >= 0 && x < width && y >= 0 && y < height;
}

void move_map_horizontally(
	const float dx, 
	TObject& mario, 
	TObject *bricks, const int bricks_count,
	TObject *movings, int& movings_count
) {
	mario.x -= dx;
	for (int i = 0; i < bricks_count; i++) {
		if (is_collision(&mario, &bricks[i])) {
			mario.x += dx;
			return;
		}
	}
	mario.x += dx;
	
	for (int i = 0; i < bricks_count; i++) {
		bricks[i].x += dx;
	}
	
	for (int i = 0; i < movings_count; i++) {
		movings[i].x += dx;
	}
}

void move_obj_horizontally(
	TObject* obj, 
	TObject& mario, 
	TObject *&bricks, int& bricks_count,
	TObject *&movings, int& movings_count,
	int& current_level,
	const int max_level,
	int& score
) {
	obj->x += obj->horiz_speed;
	
	for (int i = 0; i < bricks_count; i++) {
		if (is_collision(obj, &bricks[i])) {
			obj->x -= obj->horiz_speed;
			obj->horiz_speed = -obj->horiz_speed;
			return;
		}
	}
	
	if (obj->ctype == ENEMY) {
		TObject tmp = *obj;
		move_obj_vertically(
			&tmp, 
			mario, 
			bricks, bricks_count, 
			movings, movings_count, 
			current_level, max_level, 
			score);
		if (tmp.is_fly == true) {
			obj->x -= obj->horiz_speed;
			obj->horiz_speed = -obj->horiz_speed;
		}
	}
}

void move_obj_vertically(
	TObject* obj, 
	TObject& mario, 
	TObject *&bricks, int& bricks_count,
	TObject *&movings, int& movings_count,
	int& current_level,
	const int max_level,
	int& score
) {
	obj->is_fly = true;
	obj->vert_speed += 0.05;
	set_obj_position(obj, obj->x, obj->y + obj->vert_speed);
	
	for (int i = 0; i < bricks_count; i++) {
		if (is_collision(obj, &bricks[i])) {
			if (obj->vert_speed > 0) {
				obj->is_fly = false;
			}
			
			if (
				bricks[i].ctype == FULL_BOX && 
				obj->vert_speed < 0 && 
				obj == &mario
			) {
				bricks[i].ctype = EMPTY_BOX;
				
				movings_count++;
				TObject* temp = new TObject[movings_count];
				for (int i = 0; i < movings_count - 1; i++) {
					temp[i] = movings[i];
				}
				delete [] movings;
				movings = temp;
				
				init_obj(
					&movings[movings_count - 1], 
					bricks[i].x, bricks[i].y - 3, 
					3, 2, 
					'$');
				movings[movings_count - 1].vert_speed = -0.7;
			}

			obj->y -= obj->vert_speed;
			obj->vert_speed = 0;

			if (bricks[i].ctype == WIN_BRICK) {
				current_level++;
				if (current_level > max_level) {
					current_level = 1;
				}
				
				system("color 2F");
				Sleep(500);
				create_current_level(
					current_level, 
					mario, 
					bricks, bricks_count, 
					movings, movings_count,
					score);
			}
			break;
		}
	}
}

void put_obj_on_map(TObject* obj, char **map, const int width, const int height) {
	int ix = (int) round(obj->x);
	int iy = (int) round(obj->y);
	int iwidth = (int) round(obj->width);
	int iheight = (int) round(obj->height);
	
	for (int i = ix; i < ix + iwidth; i++) {
		for (int j = iy; j < iy + iheight; j++) {
			if (is_on_map(i, j, width, height)) {
				map[j][i] = obj->ctype;
			}
		}
	}
}

void put_score_on_map(char **map, const int score) {
	char c[30];
	sprintf(c, "Score: %d", score);
	int len = std::strlen(c);
	for (int i = 0; i < len; i++) {
		map[1][i + 5] = c[i];
	}
}

void rerun_level(
	TObject& mario, 
	TObject *bricks, int& bricks_count, 
	TObject *movings, int& movings_count,
	const int current_level,
	int& score
) {
	system("color 4F");
	Sleep(500);
	create_current_level(
		current_level, 
		mario, 
		bricks, bricks_count, 
		movings, movings_count,
		score);
}

void set_cursor_position(const int x, const int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void set_obj_position(TObject* obj, const float xpos, const float ypos) {
	obj->x = xpos;
	obj->y = ypos;
}

void show_map(char **map, const int width, const int height) {
	map[height - 1][width - 1] = '\0';
	for (int j = 0; j < height; j++) {
		std::cout << map[j];
	}
}
