/*
 * HMI.c
 *
 *  Created on: Dec 18, 2018
 *      Author: karl
 */

#include <stdlib.h>
#include "LCD/LCD.h"
#include "SegLCD1.h"
#include "TSS1.h"
#include "LED1.h"
#include "LED2.h"
#include "SW1.h"
#include "SW2.h"

static LDD_TDeviceData *MySegLCDPtr;

int counter = 0;
int points = 0;
bool sw1, sw2;
char lcd_txt[4];

void addCounter()
{
	counter++;
	counter = (counter < 9999)?counter:0;
	itoa (counter,lcd_txt,10);
	vfnLCD_Write_Msg((uint8 *)lcd_txt);
}

void setPoints(int value)
{
	points = ((points+value < 0) || (points+value > 5))? points : points+value;
	if (points > 1)	_LCD_DP1_ON(); else _LCD_DP1_OFF();
	if (points > 2)	_LCD_DP2_ON(); else _LCD_DP2_OFF();
	if (points > 3)	_LCD_DP3_ON(); else _LCD_DP3_OFF();
	if (points > 4)	_LCD_COL_ON(); else _LCD_COL_OFF();
}

void HMI_init()
{
	Configure();
	MySegLCDPtr = SegLCD1_Init(NULL);  //initialize sLCD according to PEx
	setPoints(0);
	sw1 = FALSE;
	sw2 = sw1;
}

void HMI_refresh()
{
	TSS_Task();
	if (SW1_GetVal()!=sw1)
	{
		sw1 = SW1_GetVal();
		if (sw1 == TRUE) setPoints(-1);
	}
	if (SW2_GetVal() != sw2)
	{
		sw2 = SW2_GetVal();
		if (sw2 == TRUE) setPoints(1);
	}
}
