/****************************************Copyright (c)****************************************************
**
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h"
#include "button_EXINT/button.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "dac/dac.h"
#include "led/led.h"

#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

volatile uint8_t prevBall_x_position;
volatile uint8_t prevBall_y_position;
// struct struct_ball ball;
//  struct struct_paddle paddle;
/**
 * @brief main
 *
 * Margoni Diego
 * MAT : s295483
 *
 */
int main(void)
{
	// &= ~ reset bit
	// |= set bit
	// VETTORE
	// int vett[5];
	// int vett [5] = {1,2,3,4, 5};
	// int vett[]={12, 5, 3, 6};
	// MATRICE
	// tipo nome[num_righe][num_colonne];
	// int Mx[10][20] ={{0}}    (tutta a 0)
	// int Mx[][2]={{1,2},{3,4}};

	//	int Mx[100][4]={{1,2,3},{4,5}};
	// 1a riga: 1, 2, 3, 0
	// 2a riga: 4, 5, 0, 0
	// le altre 98 righe: 0, 0, 0, 0

	// 	int Mx[100][4]={1,2,3,4,5};
	// 1a riga: 1, 2, 3, 4
	// 2a riga: 5, 0, 0, 0
	// le altre 98 righe: 0, 0, 0, 0
	SystemInit(); /* System Initialization (i.e., PLL)  */

	BUTTON_init();
	LED_init();
	init_RIT(0x004C4B40);
	/* RIT Initialization 50ms : conoscendo la sua frequenza di 100MHz
								 la costante di tempo è 50ms*100MHz
								 0.05s * 100000000 = 5000000 = Hex 0x4C4B40
	*/
	enable_RIT();





	LPC_SC->PCON |= 0x1; /* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);

	while (1)
	{
		__ASM("wfi");
	}
}

/*********************************************************************************************************
	  END FILE
*********************************************************************************************************/
