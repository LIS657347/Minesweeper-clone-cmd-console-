#pragma once
#include<windows.h>
#include<iostream>

#ifndef map_minesweper
#define map_minesweper


#define Fail    -1
#define Game_over -2
#define Succes   0
#define Game_win 1


int unlock_map(int _x, int _y);
void switch_mark(int _x, int _y);

struct Tile {
	UINT8 mines_count : 4;
	UINT8 is_open : 1;
	UINT8 is_mine : 1;
	UINT8 is_marked : 1;
};

class Map
{
public:
	Map(int height, int width, int mines);
	~Map();
	int open(const int x, const int y);
	int mark_tile(const int x, const int y);
	int peek(const int x, const int y);
	int init(const int x, const int y);
	bool is_open(const int x, const int y);
	bool is_marked(const int x, const int y);
private:
	int _height;
	int _width;
	Tile* data;
	int fake_mines;
	int mines_found;
	int _mines;
	int tile_open;
};

#endif // !map_minesweper

