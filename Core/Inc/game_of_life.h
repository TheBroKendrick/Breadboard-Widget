/*
 * game_of_life.h
 *
 *  Created on: 18/06/2026
 *      Author: kenmi
 */

#ifndef INC_GAME_OF_LIFE_H_
#define INC_GAME_OF_LIFE_H_

void game_of_life_init(void);
static uint8_t count_neighbours(int x, int y);
void pixel_driver(void);
void game_of_life(void);

#endif /* INC_GAME_OF_LIFE_H_ */
