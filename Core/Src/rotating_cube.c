/*
 * rotating_cube.c
 *
 *  Created on: 21/06/2026
 *      Author: kenmi
 */
#include <stdint.h>
#include <stdlib.h>

#include "rotating_cube.h"
#include "ssd1306.h"
#include "ssd1306_conf.h"

#define CUBE_WIDTH 40
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define ORIGIN_X 63
#define ORIGIN_Y 31

static uint8_t buffer[SCREEN_WIDTH][SCREEN_HEIGHT] = {0};

Vec2D convert_coords (Vec2D* point) {
	Vec2D normalised_point = {0, 0};
	normalised_point.x = (uint8_t)(((float)point -> x + 1)/2 * SCREEN_WIDTH) - 1;
	normalised_point.y = (uint8_t)(((float)point -> y + 1)/2 * SCREEN_HEIGHT) - 1;
	return normalised_point;
}


