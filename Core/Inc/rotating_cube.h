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

Vec3D* init_vertices(void);
void convert_coords (Vec2D* point);
void init_cube(Vec3D** cube_vertices);
#endif /* INC_ROTATING_CUBE_H_ */
