/*
 * system.c
 *
 *  Created on: Dec 8, 2020
 *      Author: ACER
 */
#include "main.h"
#include "hardwareinit.h"
#include "system.h"
#include "i2c-lcd.h"

I2C_HandleTypeDef hi2c1;
TIM_HandleTypeDef htim2;

void system(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_I2C1_Init();
	MX_TIM2_Init(2);

	lcd_init();
	lcd_put_cur(0,0);
	lcd_send_string ("VENDING  MACHINE");
	HAL_Delay(1000);
	lcd_put_cur(1, 3);
	lcd_send_string("1110181004");
	HAL_Delay(3000);
	lcd_clear ();
	lcd_put_cur(0,0);
	lcd_send_string ("Masukkan  Uang");
	HAL_Delay(1000);
	lcd_put_cur(1,0);
	lcd_send_string ("Untuk Transaksi");
	HAL_Delay(2000);
	lcd_clear();

	HAL_TIM_Base_Start_IT(&htim2);
}

