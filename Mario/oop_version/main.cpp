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

class Object;
class Map;

void delete_movings(const int i, Object *movings, int& movings_count);
void hide_cursor();

class Object{
	private:
		float x, y;
		const float width, height;
		float horiz_speed;
		float vert_speed;
		bool is_fly;
		char ctype;

	public:
		Object(
			const float _x = 0, const float _y = 0,
			const float _width = 1, const float _height = 1, 
			const char _ctype = '%')
			: width(_width), height(_height) {}
		Object(const Object &other) : width(other.width), height(other.height) {}

		
		void set_x(const int _x);
		void set_y(const int _y);
		// void set_obj_position(const int _x, const int _y) {x = _x; y = _y;}
		void set_horizspeed(const float _horiz_speed);
		void set_vert_speed(const float _vert_speed);
		void set_is_fly(const bool _is_fly);
		void increase_x(const int dx);
		
		float get_x() const;
		float get_y() const;
		float get_width() const;
		float get_height() const;
		float get_horizspeed() const;
		float get_vert_speed() const;
		char get_ctype() const;
		bool get_is_fly() const;

		bool is_collision(const Object &other);

		bool is_on_map(Map* const map);

		void move_obj_vertically( 
			Object& mario, 
			Object *&bricks, int& bricks_count,
			Object *&movings, int& movings_count,
			int& current_level,
			const int max_level,
			int& score, Map* const map
		);

		void move_obj_horizontally( 
			Object& mario, 
			Object *&bricks, int& bricks_count,
			Object *&movings, int& movings_count,
			int& current_level,
			const int max_level,
			int& score, Map* const map
		);
		void check_mario_collisions(
			Object& mario, 
			Object *&bricks, int& bricks_count, 
			Object *&movings, int& movings_count,
			const int current_level,
			int& score, Map* const map
		);
};

class Map{
	private:
		const int map_width;
		const int map_height;
		char **map = new char* [map_height];
	public:
		Map(const int _map_width, const int _map_height) : map_width(_map_width), map_height(_map_height){
			for (int i = 0; i < map_height; i++) {
				map[i] = new char[map_width + 1];
			}
		};

		void create_current_level(
			const int current_level, 
			Object &mario, 
			Object *&bricks, int& bricks_count,
			Object *&movings, int& movings_count,
			int& score
		);
		
		void clear_map();

		void put_obj_on_map(Object *obj);

		void move_map_horizontally(
			const float dx, 
			Object& mario, 
			Object *bricks, const int bricks_count,
			Object *movings, int& movings_count
		);

		void put_score_on_map(const int score);
		
		void show_map();

		void rerun_level(
			Object& mario, 
			Object *bricks, int& bricks_count, 
			Object *movings, int& movings_count,
			const int current_level,
			int& score
		);

		int get_map_width() const {return map_width;};
		int get_map_height() const {return map_height;};
};

void set_cursor_position(const int x, const int y);

int main() {
	hide_cursor();
	
	Map map(80, 25);
	
	Object mario(39, 10, 3, 3, '@');
	Object *bricks = nullptr;
	int bricks_count;
	
	Object *movings = nullptr;
	int movings_count;
	
	int current_level = 1;
	const int max_level = 3;
	int score;
	
	map.create_current_level(
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
		map.clear_map();
		
		if (mario.get_is_fly() == false && GetKeyState(jump_key) < 0) {
			mario.set_vert_speed(-1);
		}
		if (GetKeyState(left_direction_key) < 0) {
			map.move_map_horizontally(
				1, 
				mario, 
				bricks, bricks_count, 
				movings, movings_count);
		}
		if (GetKeyState(right_direction_key) < 0) {
			map.move_map_horizontally(
				-1, 
				mario, 
				bricks, bricks_count, 
				movings, movings_count);
		}
		if (mario.get_y() > map.get_map_height()) {
			map.rerun_level(
				mario, 
				bricks, bricks_count, 
				movings, movings_count, 
				current_level,  
				score);
		}
		
		mario.move_obj_vertically(
			mario, 
			bricks, bricks_count, 
			movings, movings_count, 
			current_level, max_level, 
			score, &map);
		mario.check_mario_collisions(
			mario, 
			bricks, bricks_count, 
			movings, movings_count, 
			current_level, score, &map);
		
		for (int i = 0; i < bricks_count; i++) {
			map.put_obj_on_map(&bricks[i]);
		}
		
		for (int i = 0; i < movings_count; i++) {
			movings[i].move_obj_vertically( 
				mario, 
				bricks, bricks_count, 
				movings, movings_count, 
				current_level, max_level, 
				score, &map);
			movings[i].move_obj_horizontally( 
				mario, 
				bricks, bricks_count, 
				movings, movings_count, 
				current_level, max_level, 
				score, &map);
			if (movings[i].get_y() > map.get_map_height()) {
				delete_movings(i, movings, movings_count);
				i--;
				continue;
			}
			map.put_obj_on_map(&movings[i]);
		}

		map.put_obj_on_map(&mario);
		map.put_score_on_map(score);
		
		set_cursor_position(0, 0);
		map.show_map();
		
		Sleep(10);
	} while (GetKeyState(exit_key) >= 0);
	
	map.~Map();
	
	delete [] bricks;
	delete [] movings;
	
	return 0;
}

void delete_movings(const int i, Object *movings, int& movings_count) {
	movings_count--;
	new (&movings[i]) Object(movings[movings_count]);
}

void hide_cursor() {
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO struct_cursor_info;
	GetConsoleCursorInfo(handle, &struct_cursor_info);
	struct_cursor_info.bVisible = false;
	SetConsoleCursorInfo(handle, &struct_cursor_info);
}

void set_cursor_position(const int x, const int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
		
void Object::set_x(const int _x) {x = _x;}
void Object::set_y(const int _y) {y = _y;}
// void set_obj_position(const int _x, const int _y) {x = _x; y = _y;}
void Object::set_horizspeed(const float _horiz_speed) { horiz_speed = _horiz_speed; }
void Object::set_vert_speed(const float _vert_speed) { vert_speed = _vert_speed; }
void Object::set_is_fly(const bool _is_fly) { is_fly = _is_fly; }
void Object::increase_x(const int dx) { x += dx;}

float Object::get_x() const { return x; }
float Object::get_y() const { return y; }
float Object::get_width() const { return width; }
float Object::get_height() const { return height; }
float Object::get_horizspeed() const { return horiz_speed; }
float Object::get_vert_speed() const { return vert_speed; }
char Object::get_ctype() const { return ctype; }
bool Object::get_is_fly() const { return is_fly; }

bool Object::is_collision(const Object &other) {
	return (
		x + width > other.x && 
		x < other.x + other.width &&
		y + height > other.y && 
		y < other.y + other.height
	);
}

bool Object::is_on_map(Map* const map) {
	return x >= 0 && x < map->get_map_width() && y >= 0 && y < map->get_map_height();
}

void Object::move_obj_vertically( 
	Object& mario, 
	Object *&bricks, int& bricks_count,
	Object *&movings, int& movings_count,
	int& current_level,
	const int max_level,
	int& score, Map* const map
) {
	is_fly = true;
	vert_speed += 0.05;
	y += vert_speed;
	// set_obj_position(obj, obj->x, obj->y + obj->vert_speed);
	
	for (int i = 0; i < bricks_count; i++) {
		if (is_collision(bricks[i])) {
			if (vert_speed > 0) {
				is_fly = false;
			}
			
			if (
				bricks[i].ctype == FULL_BOX && 
				vert_speed < 0 && 
				this == &mario
			) {
				bricks[i].ctype = EMPTY_BOX;
				
				movings_count++;
				Object* temp = new Object[movings_count];
				for (int i = 0; i < movings_count - 1; i++) {
					//Пока не знаю как иначе передать значение из одного массива в другой
					new (&temp[i]) Object(movings[i]);
				}
				delete [] movings;
				movings = temp;

				new (&movings[movings_count - 1]) Object(bricks[i].x, bricks[i].y - 3, 3, 2, '$'); 
				
				// init_obj(
				// 	&movings[movings_count - 1], 
				// 	bricks[i].x, bricks[i].y - 3, 
				// 	3, 2, 
				// 	'$');
				movings[movings_count - 1].vert_speed = -0.7;
			}

			y -= vert_speed;
			vert_speed = 0;

			if (bricks[i].ctype == WIN_BRICK) {
				current_level++;
				if (current_level > max_level) {
					current_level = 1;
				}
				
				system("color 2F");
				Sleep(500);
				map->create_current_level(
					current_level, mario, 
					bricks, bricks_count, 
					movings, movings_count, 
					score);
			}
			break;
		}
	}
}

void Object::move_obj_horizontally( 
	Object& mario, 
	Object *&bricks, int& bricks_count,
	Object *&movings, int& movings_count,
	int& current_level,
	const int max_level,
	int& score, Map* const map
) {
	x += horiz_speed;
	
	for (int i = 0; i < bricks_count; i++) {
		if (is_collision(bricks[i])) {
			x -= horiz_speed;
			horiz_speed = -horiz_speed;
			return;
		}
	}
	
	if (ctype == ENEMY) {
		Object tmp = *this;
		tmp.move_obj_vertically( 
			mario, 
			bricks, bricks_count, 
			movings, movings_count, 
			current_level, max_level, 
			score, map);
		if (tmp.is_fly == true) {
			x -= horiz_speed;
			horiz_speed = -horiz_speed;
		}
	}
}

void Object::check_mario_collisions(
	Object& mario, 
	Object *&bricks, int& bricks_count, 
	Object *&movings, int& movings_count,
	const int current_level,
	int& score, Map* const map
) {
	for (int i = 0; i < movings_count; i++) {
		if (mario.is_collision(movings[i])) {
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
				else map->rerun_level(
					mario, 
					bricks, bricks_count, 
					movings, movings_count, 
					current_level,  
					score);
			}
			
			if (movings[i].ctype = MONEY) {
				score += 100;
				delete_movings(i, movings, movings_count);
				i--;
				continue;
			}
		}
	}
}

void Map::create_current_level(
	const int current_level, 
	Object &mario, 
	Object *&bricks, int& bricks_count,
	Object *&movings, int& movings_count,
	int& score
) {
	system("color 9F");
	
	delete [] bricks;
	bricks = nullptr;
	delete [] movings;
	movings = nullptr;

	// init_obj(&mario, 39, 10, 3, 3, '@');
	score = 0;
	
	switch (current_level) {
		case 1:
			bricks_count = 13;
			bricks = new Object[bricks_count];
			
			// new (&bricks[0]) Object(20, 20, 40, 5, BRICK);
			new (&bricks[0]) Object(20, 20, 40, 5, BRICK);
			
			new (&bricks[1]) Object(30, 10, 5, 3, FULL_BOX);
			new (&bricks[2]) Object(50, 10, 5, 3, FULL_BOX);
			
			new (&bricks[3]) Object(60, 15, 40, 10, BRICK);
			
			new (&bricks[4]) Object(60, 5, 10, 3, EMPTY_BOX);
			new (&bricks[5]) Object(70, 5, 5, 3, FULL_BOX);
			new (&bricks[6]) Object(75, 5, 5, 3, EMPTY_BOX);
			new (&bricks[7]) Object(80, 5, 5, 3, FULL_BOX);
			new (&bricks[8]) Object(85, 5, 10, 3, EMPTY_BOX);
			
			new (&bricks[9]) Object(100, 20, 20, 5, BRICK);
			new (&bricks[10]) Object( 120, 15, 10, 10, BRICK);
			new (&bricks[11]) Object( 150, 20, 40, 5, BRICK);
			new (&bricks[12]) Object( 210, 15, 10, 10, WIN_BRICK);
			
			movings_count = 2;
			movings = new Object[movings_count];
			
			new (&movings[0]) Object(25, 10, 3, 2, ENEMY);
			new (&movings[1]) Object(80, 10, 3, 2, ENEMY);
			break;
		default: 
			break;
	}
}

void Map::clear_map() {
	for (int i = 0; i < map_width; i++) {
		map[0][i] = ' ';
	}
	map[0][map_width] = '\0';
	for (int j = 1; j < map_height; j++) {
		sprintf(map[j], map[0]);
	}
}

void Map::put_obj_on_map(Object *obj) {
	int ix = (int) round(obj->get_x());
	int iy = (int) round(obj->get_y());
	int iwidth = (int) round(obj->get_width());
	int iheight = (int) round(obj->get_height());
	
	for (int i = ix; i < ix + iwidth; i++) {
		for (int j = iy; j < iy + iheight; j++) {
			if (obj->is_on_map(this)) {
				map[j][i] = obj->get_ctype();
			}
		}
	}
}

void Map::move_map_horizontally(
	const float dx, 
	Object& mario, 
	Object *bricks, const int bricks_count,
	Object *movings, int& movings_count
) {
	mario.increase_x(-dx);
	for (int i = 0; i < bricks_count; i++) {
		if (mario.is_collision(bricks[i])) {
			mario.increase_x(dx);
			return;
		}
	}
	mario.increase_x(dx);
	
	for (int i = 0; i < bricks_count; i++) {
		bricks[i].increase_x(dx);
	}
	
	for (int i = 0; i < movings_count; i++) {
		movings[i].increase_x(dx);
	}
}

void Map::put_score_on_map(const int score) {
	char c[30];
	sprintf(c, "Score: %d", score);
	int len = std::strlen(c);
	for (int i = 0; i < len; i++) {
		map[1][i + 5] = c[i];
	}
}

void Map::show_map() {
	map[map_height - 1][map_width - 1] = '\0';
	for (int j = 0; j < map_height; j++) {
		std::cout << map[j];
	}
}

void Map::rerun_level(
	Object& mario, 
	Object *bricks, int& bricks_count, 
	Object *movings, int& movings_count,
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
