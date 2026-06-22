/*
 * screen_task.c
 *
 *  Created on: 21/06/2026
 *      Author: kenmi
 */
#include "screen_task.h"
#include "ssd1306.h"
#include "ssd1306_conf.h"
#include "game_of_life.h"
#include "rotating_cube.h"


void screen_task_init(void) {
	ssd1306_Init();
	ssd1306_Fill(Black);
	game_of_life_init();
	ssd1306_UpdateScreen();
}

void screen_task_execute(void) {
//	ssd1306_Fill(Black);
//	game_of_life();
//	ssd1306_UpdateScreen();
	Vec3D* cube_vertices = init_vertices();
	init_cube(&cube_vertices);
	ssd1306_UpdateScreen();
}
