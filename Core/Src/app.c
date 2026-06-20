/*
 * app.c
 *
 *  Created on: 6/06/2026
 *      Author: kenmi
 */
#include "app.h"
#include "gpio.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ssd1306_conf.h"
#include "screen_task.h"


#define TICK_FREQUENCY 1000
#define BLINK_FREQUENCY 2
#define SCREEN_FREQUENCY 10

#define BLINKY_PERIOD_TICKS TICK_FREQUENCY / BLINK_FREQUENCY
#define SCREEN_PERIOD_TICKS TICK_FREQUENCY / SCREEN_FREQUENCY

static uint32_t Blinky_Next_Run = 0;
static uint32_t Screen_Next_Run = 0;

void app_main(void) {
	screen_task_init();

	Blinky_Next_Run = HAL_GetTick() + BLINKY_PERIOD_TICKS;
	Screen_Next_Run = HAL_GetTick() + SCREEN_PERIOD_TICKS;

	while (1) {
		uint32_t ticks = HAL_GetTick();

		if (ticks >= Blinky_Next_Run) {
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
			Blinky_Next_Run += BLINKY_PERIOD_TICKS;
		}

		if (ticks >= Screen_Next_Run) {
			screen_task_execute();
			Screen_Next_Run += SCREEN_PERIOD_TICKS;
		}
	}

}

