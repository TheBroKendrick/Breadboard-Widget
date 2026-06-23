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
#define NUM_OF_VERTICES 8

static uint8_t buffer[SCREEN_WIDTH][SCREEN_HEIGHT] = {0};

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

void convert_coords (Vec2D* point) {
	point -> x = (uint8_t)(((float)point -> x + 1)/2 * SCREEN_WIDTH) - 1;
	point -> y = (uint8_t)(SCREEN_HEIGHT - 1 - ((float)point -> y + 1)/2 * SCREEN_HEIGHT);
}

void draw_cube(void) {
	Vec2D projected_vertices[8] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
	for (size_t i = 0; i < NUM_OF_VERTICES; i++){
		float px = cube_vertices[i].x / cube_vertices[i].z;
		float py = cube_vertices[i].y / cube_vertices[i].z;

		px = (((float)px + 1)/2 * SCREEN_WIDTH - 1);
		py = (SCREEN_HEIGHT - 1 - ((float)py + 1)/2 * SCREEN_HEIGHT);

		projected_vertices[i].x = px;
		projected_vertices[i].y = py;
		ssd1306_DrawPixel(px, py, White);
	}

	//One face
	ssd1306_Line((uint8_t)projected_vertices[0].x, (uint8_t)projected_vertices[0].y, (uint8_t)projected_vertices[1].x, (uint8_t)projected_vertices[1].y, White);
	ssd1306_Line((uint8_t)projected_vertices[0].x, (uint8_t)projected_vertices[0].y, (uint8_t)projected_vertices[2].x, (uint8_t)projected_vertices[2].y, White);
	ssd1306_Line((uint8_t)projected_vertices[1].x, (uint8_t)projected_vertices[1].y, (uint8_t)projected_vertices[3].x, (uint8_t)projected_vertices[3].y, White);
	ssd1306_Line((uint8_t)projected_vertices[2].x, (uint8_t)projected_vertices[2].y, (uint8_t)projected_vertices[3].x, (uint8_t)projected_vertices[3].y, White);

	//Other face
	ssd1306_Line((uint8_t)projected_vertices[4].x, (uint8_t)projected_vertices[4].y, (uint8_t)projected_vertices[5].x, (uint8_t)projected_vertices[5].y, White);
	ssd1306_Line((uint8_t)projected_vertices[6].x, (uint8_t)projected_vertices[6].y, (uint8_t)projected_vertices[7].x, (uint8_t)projected_vertices[7].y, White);
	ssd1306_Line((uint8_t)projected_vertices[4].x, (uint8_t)projected_vertices[4].y, (uint8_t)projected_vertices[6].x, (uint8_t)projected_vertices[6].y, White);
	ssd1306_Line((uint8_t)projected_vertices[5].x, (uint8_t)projected_vertices[5].y, (uint8_t)projected_vertices[7].x, (uint8_t)projected_vertices[7].y, White);

	//Connecting the two
	ssd1306_Line((uint8_t)projected_vertices[0].x, (uint8_t)projected_vertices[0].y, (uint8_t)projected_vertices[4].x, (uint8_t)projected_vertices[4].y, White);
	ssd1306_Line((uint8_t)projected_vertices[1].x, (uint8_t)projected_vertices[1].y, (uint8_t)projected_vertices[5].x, (uint8_t)projected_vertices[5].y, White);
	ssd1306_Line((uint8_t)projected_vertices[2].x, (uint8_t)projected_vertices[2].y, (uint8_t)projected_vertices[6].x, (uint8_t)projected_vertices[6].y, White);
	ssd1306_Line((uint8_t)projected_vertices[3].x, (uint8_t)projected_vertices[3].y, (uint8_t)projected_vertices[7].x, (uint8_t)projected_vertices[7].y, White);
	ssd1306_UpdateScreen();
}
