/*
 * rotating_cube.c
 *
 *  Created on: 21/06/2026
 *      Author: kenmi
 */
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "rotating_cube.h"
#include "ssd1306.h"
#include "ssd1306_conf.h"

#define CUBE_WIDTH 40
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define NUM_OF_VERTICES 8
#define PI 3.14159625

static float theta = 0;

Vec3D base_vertices[8] = {
	    {-0.5f, -0.5f, -0.5f},
	    {-0.5f,  0.5f, -0.5f},
	    { 0.5f, -0.5f, -0.5f},
	    { 0.5f,  0.5f, -0.5f},
	    {-0.5f, -0.5f,  0.5f},
	    {-0.5f,  0.5f,  0.5f},
	    { 0.5f, -0.5f,  0.5f},
	    { 0.5f,  0.5f,  0.5f},
};

static Vec3D cube_vertices[8] = {
	    {-0.5f, -0.5f, -0.5f},
	    {-0.5f,  0.5f, -0.5f},
	    { 0.5f, -0.5f, -0.5f},
	    { 0.5f,  0.5f, -0.5f},
	    {-0.5f, -0.5f,  0.5f},
	    {-0.5f,  0.5f,  0.5f},
	    { 0.5f, -0.5f,  0.5f},
	    { 0.5f,  0.5f,  0.5f},
};

static Vec2D projected_vertices[8] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

void rotate_cube (void) {
	if (theta <= 2* PI) {
		theta += 0.1;
	} else {
		theta = 0;
	}
	float c = cos(theta);
	float s = sin(theta);

	//Axis of rotation
	float u = 1, v = 2, w = 3;
	float mag = sqrt(u*u + v*v + w*w);
	u /= mag;
	v /= mag;
	w /= mag;

	for (size_t i = 0; i < NUM_OF_VERTICES; i++) {
		float x = base_vertices[i].x;
		float y = base_vertices[i].y;
		float z = base_vertices[i].z;

		float dot_product = u*x + v*y + w*z;

		//Rodrigues formula implementation
		cube_vertices[i].x =
		    u*dot_product*(1-c) +
		    x*c +
		    (-w*y + v*z)*s;

		cube_vertices[i].y =
		    v*dot_product*(1-c) +
		    y*c +
		    (w*x - u*z)*s;

		cube_vertices[i].z =
		    w*dot_product*(1-c) +
		    z*c +
		    (-v*x + u*y)*s;
	}
}

Vec2D convert_coords (float x, float y) {
	Vec2D new_point = {0, 0};
	new_point.x = ((x + 1)/2 * SCREEN_WIDTH) - 1;
	new_point.y = SCREEN_HEIGHT - 1 - (y + 1)/2 * SCREEN_HEIGHT;
	return new_point;

}

void draw_cube(void) {
	for (size_t i = 0; i < NUM_OF_VERTICES; i++){
		float pz = cube_vertices[i].z + 2;
		float px = cube_vertices[i].x / pz;
		float py = cube_vertices[i].y / pz;

		projected_vertices[i] = convert_coords(px, py);

		ssd1306_DrawPixel((uint8_t)projected_vertices[i].x, (uint8_t)projected_vertices[i].y, White);
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
