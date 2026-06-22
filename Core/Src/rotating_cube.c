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

Vec3D* init_vertices(void) {
	static Vec3D cube_vertices[8] = {
			{-0.5, -0.5, 1.5},
			{-0.5, 0.5, 1.5},
			{0.5, -0.5, 1.5},
			{0.5, 0.5, 1.5},

			{-0.5, -0.5, 2},
			{-0.5, 0.5, 2},
			{0.5, -0.5, 2},
			{0.5, 0.5, 2},
	};

	return cube_vertices;
}

void convert_coords (Vec2D* point) {
	point -> x = (uint8_t)(((float)point -> x + 1)/2 * SCREEN_WIDTH) - 1;
	point -> y = (uint8_t)(SCREEN_HEIGHT - 1 - ((float)point -> y + 1)/2 * SCREEN_HEIGHT);
}

void init_cube(Vec3D** cube_vertices) {
	for (size_t i = 0; i < 8; i++){
		cube_vertices[i] -> x = (((float)cube_vertices[i] -> x + 1)/2 * SCREEN_WIDTH - 1) / cube_vertices[i] -> z;
		cube_vertices[i] -> y = (SCREEN_HEIGHT - 1 - ((float)cube_vertices[i] -> y + 1)/2 * SCREEN_HEIGHT) / cube_vertices[i] -> z;
		ssd1306_DrawPixel((uint8_t)cube_vertices[i] -> x, (uint8_t)cube_vertices[i] -> y, White);
	}

	ssd1306_UpdateScreen();
}
