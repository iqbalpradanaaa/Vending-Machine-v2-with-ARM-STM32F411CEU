/*
 * task.c
 *
 *  Created on: Nov 28, 2020
 *      Author: ACER
 */
#include "task.h"
#include "stm32f4xx_hal.h"
#include "hardwareinit.h"
#include "main.h"
#include "i2c-lcd.h"

#define delay       100   // 200ms
#define delay2		300   // 600ms
#define BTN500      HAL_GPIO_ReadPin(BTNA_GPIO_Port, BTNA_Pin)==GPIO_PIN_RESET
#define BTN1000     HAL_GPIO_ReadPin(BTNB_GPIO_Port, BTNB_Pin)==GPIO_PIN_RESET
#define BP      	HAL_GPIO_ReadPin(BTNC_GPIO_Port, BTNC_Pin)==GPIO_PIN_RESET
#define BB       	HAL_GPIO_ReadPin(BTND_GPIO_Port, BTND_Pin)==GPIO_PIN_RESET

#define LD500_ON    HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET)
#define LD500_OFF   HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET)

#define LD1000_ON   HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET)
#define LD1000_OFF  HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET)

#define LDSCS_ON    HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET)
#define LDSCS_OFF   HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_RESET)

#define CNC_ON      HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET)
#define CNC_OFF     HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET)

enum state {s0, s1, s2, s3, s4, s5, s6, s7} stateku;

unsigned int timedelay = 0;
unsigned int timedelay2 = 0;


unsigned char B500 (void)
{
	static unsigned char bouncing=0xFF;
	unsigned char detectedFLag=0;

	if (BTN500)
	{
		bouncing=(bouncing<<1);
	} else
	{
		bouncing= (bouncing<<1)|1;
	}
	if (bouncing==0x03)
	{
		detectedFLag=1;
	}
	return detectedFLag;

}

unsigned char B1000 (void)
{
	static unsigned char bouncing=0xFF;
	unsigned char detectedFLag=0;

	if (BTN1000)
	{
		bouncing=(bouncing<<1);
	} else
	{
		bouncing= (bouncing<<1)|1;
	}
	if (bouncing==0x03)
	{
		detectedFLag=1;
	}
	return detectedFLag;
}

unsigned char Proses (void)
{
	static unsigned char bouncing=0xFF;
	unsigned char detectedFLag=0;

	if (BP)
	{
		bouncing=(bouncing<<1);
	} else
	{
		bouncing= (bouncing<<1)|1;
	}
	if (bouncing==0x03)
	{
		detectedFLag=1;
	}
	return detectedFLag;
}

unsigned char Batal (void)
{
	static unsigned char bouncing=0xFF;
	unsigned char detectedFLag=0;

	if (BB)
	{
		bouncing=(bouncing<<1);
	} else
	{
		bouncing= (bouncing<<1)|1;
	}
	if (bouncing==0x03)
	{
		detectedFLag=1;
	}
	return detectedFLag;
}

void Task_Init (void)
{
	stateku=s0;
}

void Task_Run (void)
{
	switch (stateku)
	{
		case s0 :
		{
			LD500_OFF;
			LD1000_OFF;
			LDSCS_OFF;
			CNC_OFF;
			lcd_put_cur(0,0);
			lcd_send_string ("H.Minum : Rp1000");
			lcd_put_cur(1,0);
			lcd_send_string ("Uang    : Rp");

			if(B500())
			{
				LD500_ON;
				stateku=s1;
				lcd_clear();
			}

			if(B1000())
			{
				LD1000_ON;
				stateku=s2;
				lcd_clear();
			}

			break;
		}

		case s1 :
		{
			LD500_OFF;
			LD1000_OFF;
			LDSCS_OFF;
			CNC_OFF;
			lcd_put_cur(0,2);
			lcd_send_string ("Saldo Kurang");
			lcd_put_cur(1,0);
			lcd_send_string ("Uang    : Rp 500");

			if(B500())
			{
				LD500_ON;
				stateku=s2;
				lcd_clear();
			}

			if(B1000())
			{
				LD1000_ON;
				stateku=s5;
				lcd_clear();
			}

			if (Batal())
			{
				LD500_ON;
				stateku=s4;
				lcd_clear();
			}
			break;
		}

		case s2 :
		{
			LD500_OFF;
			LD1000_OFF;
			LDSCS_OFF;
			CNC_OFF;
			lcd_put_cur(0,2);
			lcd_send_string ("Saldo Cukup");
			lcd_put_cur(1,0);
			lcd_send_string ("Uang    : Rp1000");

			if(B500())
			{
				LD500_ON;
				stateku=s5;
				lcd_clear();
			}

			if(B1000())
			{
				LD1000_ON;
				stateku=s6;
				lcd_clear();
			}

			if (Batal())
			{
				LD1000_ON;
				stateku=s7;
				lcd_clear();
			}

			if (Proses())
			{
				stateku=s3;
				lcd_clear();
			}

			break;
		}

		case s3 :
		{
			LD500_OFF;
			LD1000_OFF;
			LDSCS_ON;
			CNC_OFF;
			lcd_put_cur(0,3);
			lcd_send_string ("Transaksi");
			lcd_put_cur(1,3);
			lcd_send_string ("Berhasil");

			if(++timedelay2==delay2)
			{
				stateku=s0;
				lcd_clear();
				timedelay2=0;
			}

			break;
		}

		case s4 :
		{
			LD500_ON;
			LD1000_OFF;
			LDSCS_OFF;
			CNC_OFF;
			lcd_put_cur(0,3);
			lcd_send_string ("Uang Rp500");
			lcd_put_cur(1,2);
			lcd_send_string ("Dikembalikan");

			if(++timedelay2==delay2)
			{
				CNC_ON;
				stateku=s0;
				lcd_clear();
				timedelay2=0;
			}

			break;
		}

		case s5 :
		{
			LD500_ON;
			LD1000_OFF;
			LDSCS_OFF;
			CNC_OFF;
			lcd_put_cur(0,3);
			lcd_send_string ("Uang Rp500");
			lcd_put_cur(1,2);
			lcd_send_string ("Dikembalikan");

			if(++timedelay2==delay2)
			{
				stateku=s2;
				lcd_clear();
				timedelay2=0;
			}

			break;
		}

		case s6 :
		{
			LD500_OFF;
			LD1000_ON;
			LDSCS_OFF;
			CNC_OFF;
			lcd_put_cur(0,2);
			lcd_send_string ("Uang Rp1000");
			lcd_put_cur(1,2);
			lcd_send_string ("Dikembalikan");

			if(++timedelay2==delay2)
			{
				stateku=s2;
				lcd_clear();
				timedelay2=0;
			}

			break;
		}
		case s7 :
		{
			LD500_OFF;
			LD1000_ON;
			LDSCS_OFF;
			CNC_OFF;
			lcd_put_cur(0,2);
			lcd_send_string ("Uang Rp1000");
			lcd_put_cur(1,2);
			lcd_send_string ("Dikembalikan");

			if(++timedelay2==delay2)
			{
				CNC_ON;
				stateku=s0;
				lcd_clear();
				timedelay2=0;
			}

			break;
		}

	}
}
