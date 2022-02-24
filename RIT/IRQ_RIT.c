/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:		   IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:		V1.00
** Descriptions:		functions to manage T0 and T1 interrupts
** Correlated files:	RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../timer/timer.h"
#include "../led/led.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


void RIT_IRQHandler(void)
{
	// JOYSTICK
	// (LPC_GPIO1->FIOPIN & (1<<25)) == 0  	/* Joytick Select pressed */
	// (LPC_GPIO1->FIOPIN & (1<<26)) == 0	/* Joytick down pressed */
	// (LPC_GPIO1->FIOPIN & (1<<27)) == 0	 /* Joytick left pressed */
	// (LPC_GPIO1->FIOPIN & (1<<28)) == 0	 /* Joytick right pressed */
	// (LPC_GPIO1->FIOPIN & (1<<29)) == 0	 /* Joytick up pressed */
	// BUTTON
	// ((LPC_GPIO2->FIOPIN & (1 << 11)) == 0  /*KEY1 pressed */
	// ((LPC_GPIO2->FIOPIN & (1 << 12)) == 0  /* KEY2 pressed */
	// ((LPC_GPIO2->FIOPIN & (1 << 10)) == 0  /* INT0 pressed */
	// TIMER
	// VAR = LPC_RIT->RICOUNTER;  take the rit value

	/* Button De Bouncing Management */
	// KEY 1
	if (key1_down != 0)
	{
		key1_down++;
		if ((LPC_GPIO2->FIOPIN & (1 << 11)) == 0)
		{ /* KEY1 pressed */
			switch (key1_down)
			{
			case 2: // RIT is always on due to adc, so i wait 2*50ms to execute button action
				break;
			default:
				break;
			}
		}
		else
		{ /* button released */
			key1_down = 0;
			NVIC_EnableIRQ(EINT1_IRQn);		  /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4 |= (1 << 22); /* External interrupt 0 pin selection */
		}
	}

	// KEY 2
	if (key2_down != 0)
	{
		key2_down++;
		if ((LPC_GPIO2->FIOPIN & (1 << 12)) == 0)
		{ /* KEY2 pressed */
				switch (key2_down)
				{
				case 2: // RIT is always on due to adc, so i wait 2*50ms to execute button action
					break;
				default:
					break;
				}
		}
		else
		{ /* button released */
			key2_down = 0;
			NVIC_EnableIRQ(EINT2_IRQn);		  /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4 |= (1 << 24); /* External interrupt 0 pin selection */
		}
	}

	// KEY 0
	if (key0_down != 0)
	{
		key0_down++;
		if ((LPC_GPIO2->FIOPIN & (1 << 10)) == 0) 
		{ /* INT0 pressed */
			switch (key0_down)
			{
			case 2: // RIT is always on due to adc, so i wait 2*50ms to execute button action
				break;
			default:
				break;
			}
		}
		else
		{ /* button released */
			key0_down = 0;
			NVIC_EnableIRQ(EINT0_IRQn);		  /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4 |= (1 << 20); /* External interrupt 0 pin selection */
		}
	}

	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0)	 
	{/* Joytick right pressed */
		return;
	}

	
	LPC_RIT->RICTRL |= 0x1; /* clear interrupt flag */
}

/******************************************************************************
**							End Of File
******************************************************************************/
