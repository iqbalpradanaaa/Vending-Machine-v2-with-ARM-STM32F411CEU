/*
 * seos.c
 *
 *  Created on: Dec 7, 2020
 *      Author: ACER
 */
#include "main.h"
#include "hardwareinit.h"
#include "seos.h"
#include "task.h"

TIM_HandleTypeDef htim2;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM2)
	{
		Task_Run();
	}
}

