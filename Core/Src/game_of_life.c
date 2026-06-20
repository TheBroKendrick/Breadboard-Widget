/*
 * game_of_life.c
 *
 *  Created on: 18/06/2026
 *      Author: kenmi
 */
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "game_of_life.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ssd1306_conf.h"

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64

static uint8_t matrix[SCREEN_WIDTH][SCREEN_HEIGHT] = {0};
static uint8_t next[SCREEN_WIDTH][SCREEN_HEIGHT] = {0};

void game_of_life_init(void) {
    srand(12345);
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            matrix[x][y] = (rand() % 10 < 3) ? 1 : 0;
        }
    }
}

static uint8_t count_neighbours(int x, int y) {
    uint8_t count = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            int nx = (x + dx + SCREEN_WIDTH)  % SCREEN_WIDTH;
            int ny = (y + dy + SCREEN_HEIGHT) % SCREEN_HEIGHT;
            count += matrix[nx][ny];
        }
    }
    return count;
}

void game_of_life(void) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            uint8_t neighbours = count_neighbours(x, y);
            if (matrix[x][y]) {
                next[x][y] = (neighbours == 2 || neighbours == 3) ? 1 : 0;
            } else {
                next[x][y] = (neighbours == 3) ? 1 : 0;
            }
        }
    }

    for (int x = 0; x < SCREEN_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            matrix[x][y] = next[x][y];
            ssd1306_DrawPixel(x, y, matrix[x][y] ? White : Black);
        }
    }
}
