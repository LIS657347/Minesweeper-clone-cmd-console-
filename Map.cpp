#include "Map.h"
#include<math.h>


Map::Map(int  height, int width, int mines)
{
	this->_height = height;
	this->_width = width;
	this->tile_open = 0;
	this->mines_found = 0;
	this->fake_mines = 0;
	this->_mines = mines;
	this->data = new Tile[_height*_width];
	for (int y = 0; y < _height; ++y) {
		for(int x = 0; x < _width; ++x) {
			data[x + y * _width].is_mine = false;
			data[x + y * _width].is_marked = false;
			data[x + y * _width].mines_count = 0;
		}
	}
}

Map::~Map()
{
	delete[] this->data;
}

int Map::open(const int _x, const int _y)
{
	Tile& check = data[_x + _y * _width];
	if (check.is_mine) {
		return Game_over;
	}
	check.is_open = true;
	++tile_open;
	return Succes;
}

int  Map::mark_tile(const int _x, const int _y)
{
	Tile& check = data[_x + _y * _width];
	switch_mark(_x,_y);
	if (check.is_marked) {
		if (check.is_mine) {
			--mines_found;
			return Succes;
		}
		else {
			--fake_mines;
			return Succes;
		}
	}
	if (check.is_mine) {
		++mines_found;
		if (mines_found == _mines && !fake_mines) {
			return Game_win;
		}
		return Succes;
	}
	else {
		++fake_mines;
		return Succes;
	}
}

int Map::peek(const int _x,const int _y)
{
	if (_x >= _width || _y >= _height || _x<0||_y<0) {
		return Fail;
	}
	if (_height * _width == tile_open + _mines) {
		return Game_win;
	}
	Tile& check =  data[_x + _width * _y];
	if (check.is_open) {
		return Fail;
	}
	if (check.is_mine) {
		return Game_over;
	}
	return check.mines_count;
}

int Map::init(const int _x, const int _y)
{
	for (int i = 0; i < _mines; ++i) {
		COORD mine;
		mine.X = rand() % _width;
		mine.Y = rand() % _height;
		if (abs(mine.X - _x)<2 || abs(mine.Y - _y)<2) {
			--i;
			continue;
		}
		if (data[mine.X + mine.Y * _width].is_mine) {
			--i;
			continue;
		}
		data[mine.X + mine.Y * _width].is_mine = true;
		if(mine.X!=_width-1)							data[mine.X + 1 + mine.Y * _width].mines_count += 1;
		if (mine.X != 0)								data[mine.X - 1 + mine.Y * _width].mines_count += 1;
		if (mine.Y != _height-1)						data[mine.X + (mine.Y + 1) * _width].mines_count += 1;
		if (mine.Y != 0)								data[mine.X + (mine.Y - 1) * _width].mines_count += 1;
		if (mine.X != _width-1 && mine.Y != _height-1)	data[mine.X + 1 + (mine.Y + 1)* _width].mines_count += 1;
		if (mine.X != 0 && mine.Y != _height-1)			data[mine.X - 1 + (mine.Y + 1) * _width].mines_count += 1;
		if (mine.X != _width-1 && mine.Y != 0)			data[mine.X + 1 + (mine.Y - 1) * _width].mines_count += 1;
		if (mine.X != 0 && mine.Y != 0)					data[mine.X - 1 + (mine.Y - 1) * _width].mines_count += 1;
	}
	return unlock_map(_x,_y);
}

bool Map::is_open(const int _x, const int _y)
{
	return data[_x + _y * _width].is_open;
}

bool Map::is_marked(const int x, const int y)
{
	return data[x + y * _width].is_marked;
}
