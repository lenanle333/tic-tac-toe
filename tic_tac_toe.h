#ifndef TIC_TAC_TOE_H

#include <iostream>
#include <vector>

using namespace std;

void print_grid(char **grid, int size);

void next_move(char **grid, int size, int pid, bool &is_game_over);

bool check_gameover(char **grid, int size);
bool check_draw(char **grid, int size);

#endif