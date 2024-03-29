/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h"
#include "../TouchPanel/TouchPanel.h"
#include "../GLCD/GLCD.h"
#include "../dac/dac.h"
#include <stdlib.h>
#include "../led/led.h"
#include "../RIT/RIT.h"
#include "../exam/exam.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

uint16_t SinTable[45] = /*                      */
	{
		410, 467, 523, 576, 627, 673, 714, 749, 778,
		799, 813, 819, 817, 807, 789, 764, 732, 694,
		650, 602, 550, 495, 438, 381, 324, 270, 217,
		169, 125, 87, 55, 30, 12, 2, 0, 6,
		20, 41, 70, 105, 146, 193, 243, 297, 353};
	

void TIMER0_IRQHandler(void)
{
	// if (LPC_TIM0->IR & 01)
	// {
	// 	// XXX se IR � 0001 allora ha interrotto il MR0,
	// 	//     se IR � 0010    ''          ''       MR1 ecc..
	// }
	
	if(is_showing_lung_array) {
		show_lung_array();
	} else {
		show_duty_cycle();	
	}
	
	/*---*/
	LPC_TIM0->IR = 1; /* clear interrupt flag */

	
	return;
}

/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler(void)
{
	LPC_TIM1->IR = 1; /* clear interrupt flag of MR0 */
	return;
}

/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer/Counter 2 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER2_IRQHandler(void)
{	
	LPC_TIM2->IR = 1; /* clear interrupt flag of MR0 */
	return;
}

/******************************************************************************
** Function name:		Timer3_IRQHandler
**
** Descriptions:		Timer/Counter 3 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER3_IRQHandler(void)
{
	
	switch_to_monitor(LPC_TIM3->TC);
	LPC_TIM3->IR = 1; /* clear interrupt flag of MR0 */
	return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
