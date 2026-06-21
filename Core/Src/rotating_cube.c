/*
 * rotating_cube.c
 *
 *  Created on: 21/06/2026
 *      Author: kenmi
 */
#include <stdint.h>
#include "rotating_cube.h"
#include "ssd1306.h"
#include "ssd1306_conf.h"

#define CUBE_WIDTH 40
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define ORIGIN_X 63
#define ORIGIN_Y 31

static uint8_t buffer[SCREEN_WIDTH][SCREEN_HEIGHT] = {0};

void cube_init(void){

}

