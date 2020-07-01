#ifndef _CONTROLS_H_
#define _CONTROLS_H_

#include "maze.h"


int exit_check(void);
void check_move_keys(int map[][MAP_WIDTH], Player *player);
void move_player_forward(int map[][MAP_WIDTH], Player *p);
void move_player_back(int map[][MAP_WIDTH], Player *p);
void rotate_player(Player *p, float rotSpeed);

#endif
