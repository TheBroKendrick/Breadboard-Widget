/*
 * rotating_cube.h
 *
 *  Created on: 21/06/2026
 *      Author: kenmi
 */

#ifndef INC_ROTATING_CUBE_H_
#define INC_ROTATING_CUBE_H_

typedef struct {
	float x;
	float y;
} Vec2D;

typedef struct {
	float x;
	float y;
	float z;
} Vec3D;

void convert_coords (Vec2D* point);
void draw_cube(void);
#endif /* INC_ROTATING_CUBE_H_ */
