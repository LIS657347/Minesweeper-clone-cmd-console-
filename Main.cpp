#include<stdio.h>
#include<conio.h>
#include<time.h>
#include"Map.h"

auto out = GetStdHandle(STD_OUTPUT_HANDLE);
int fake_mines;
int mines;
int mines_found;
int x = 0;
int y = 0;
int x_start;
int y_start;
Map* map;



void goto_xy(int x, int y) {
	COORD xy;
	xy.X = x;
	xy.Y = y;
	SetConsoleCursorPosition(out,xy);
}

int unlock_map(int _x, int _y) {
	int mines_count = map->peek(_x, _y);
	if (mines_count == Game_over) {
		return Game_over;
	}
	if(mines_count==Fail) {
		return Succes;
	}
	goto_xy(x_start + _x, y_start + _y);
	if (mines_count == 0) {
		_putch(32);
		map->open(_x, _y);
		unlock_map(_x, _y + 1);
		unlock_map(_x, _y - 1);
		unlock_map(_x + 1, _y);
		unlock_map(_x - 1, _y);
	}
	else _putch('0'+mines_count);
	map->open(_x, _y);
	goto_xy(x + x_start, y + y_start);
	return Succes;
}

void switch_mark(int _x, int _y) {
	goto_xy(_x + x_start, _y + y_start);
	if (map->is_marked(_x, _y)) {
		_putch(32);
	}
	else {
		_putch('?');
	}
}

void init(int height, int width) {
	system("cls");
	srand(time(0));
	printf("\t\tminesweper\t\t\n");
	y_start = 2;
	x_start = 1;
	for (int _y = 0; _y <= height+1; ++_y) {
		for (int _x = 0; _x <= width+1; ++_x) {
			if (_x == 0 || _y == 0 || _x == width+1 || _y == height+1) {
				_putch('"');
			}
			else {
				_putch(140);
			}
		}
		_putch('\n');
	}
	map = new Map(height, width, 5);
	goto_xy(x + x_start, y + y_start);
	while (1) {
		char key = _getch();
		switch (key) {
		case 'w':
			--y;
			break;
		case 's':
			++y;
			break;
		case 'a':
			--x;
			break;
		case'd':
			++x;
			break;
		case 13:
			map->init(x, y);
			unlock_map(x, y);
			return;
		}
		goto_xy(x + x_start, y + y_start);
	}

}



void control(int &result) {
	char key = 0;
	key = _getch();
	if (_kbhit()) {
		key = _getch();
	}
	switch (key) {
	case 'w': 
		--y;
		break;
	case 's':
		++y;
		break;
	case 'a':
		--x;
		break;
	case'd':
		++x;
		break;
	case 32:
		result = map->mark_tile(x, y);
		break;
	case 13:
		result = unlock_map(x, y);
		break;
	}
	goto_xy(x + x_start, y + y_start);
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int result=0;
	init(12, 20);
	while (1) {
		control(result);
		if (result == Game_over) {
			break;
			printf("Loose");
		}
		if (result == Game_win) {
			goto_xy(0, 20);
			printf("Win!");
		}

	}
	system("pause");
}