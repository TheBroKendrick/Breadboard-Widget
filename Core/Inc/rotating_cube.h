/*
 * rotating_cube.h
 *
 *  Created on: 21/06/2026
 *      Author: kenmi
 */

#ifndef INC_ROTATING_CUBE_H_
#define INC_ROTATING_CUBE_H_

typedef struct {
	uint8_t x;
	uint8_t y;
} Vec2D;

typedef struct {
	uint8_t x;
	uint8_t y;
	uint8_t z;
} Vec3D;

Vec2D convert_coords (Vec2D* point);
#endif /* INC_ROTATING_CUBE_H_ */
