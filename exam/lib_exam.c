
#include "exam.h"
#include <stdio.h>
#include <stdlib.h>
#include "lpc17xx.h"
#include "../timer/timer.h"
#include "../RIT/RIT.h"
#include "../adc/adc.h"
#include "../led/led.h"

/**
 * @brief  Function that initializes exam
 */
int ciao =0;
int i;
uint8_t nr_acquisizioni;
uint8_t duty_cycle_val;
unsigned char duty_cycle(
	unsigned char VALORE_INIZIALE, 
	unsigned int TEMPO_TOTALE, 
	unsigned int* TEMPI_VARIAZIONI, //array
	unsigned char NR_ACQUISIZIONI
);
char valore_iniziale;
uint8_t last_sample;
uint8_t is_showing_lung_array;
unsigned int tempi_variazioni[N];
int is_in_monitor;

///////////////////////////////////////////////////////

void exam_init(void)
{
	is_in_monitor=1;
	i=0;
	nr_acquisizioni=0;
	is_showing_lung_array=1;
	duty_cycle_val=0;

}

void switch_to_monitor(int temp_tot)
{
	is_in_monitor=1;
	is_showing_lung_array=1;	
	disable_timer(3);
	reset_timer(3);
	
	// take the duty cycle value
	//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx hard cooooded
	valore_iniziale= 1;
	temp_tot = 150;
	tempi_variazioni[0] = 65;
	tempi_variazioni[1] = 110;
	tempi_variazioni[2] = 125;
	nr_acquisizioni= 3;
	duty_cycle_val = duty_cycle(valore_iniziale, temp_tot, tempi_variazioni, nr_acquisizioni);
	show_lung_array();
	enable_timer(0); //to show lungh_array/dutycycle alternatly with T=1/2Hz
		

}

void show_lung_array(){
	uint8_t show=0; //dovendo mostrare sia led 7 che lunghezza array, faccio una or con il 7 bit
	is_showing_lung_array = 0;
	
	show = nr_acquisizioni | 128; //128= 1000 0000
	
	LED_Out(show);

}

void show_duty_cycle(){
	is_showing_lung_array = 1;
	LED_Out(duty_cycle_val);

}

void switch_to_acquisiz(void)
{
	is_in_monitor=0;
	i=0;
	nr_acquisizioni=0;
	duty_cycle_val=0;
	disable_timer(0);
	reset_timer(0);
	// timer 3, 1 secondo aciclico (stop + interrupt)
	init_timer(3, 0, 0, 5, 0x17D7840);
	enable_timer(3);
	LED_Out(0xff);
	
	// prendo il valore iniziale del joystick
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0)	 
	{/* Joytick up pressed */
		valore_iniziale=1;
		last_sample= 1;
	} else {
		valore_iniziale=0;
		last_sample= 0;
	};

}

void sample_timer(){
	//stoppo il timer 3, e aggiungo il timestamp all'array tempi_variazionilungo 5
	int timer3_timestamp;
	disable_timer(3);
	timer3_timestamp = LPC_TIM3 -> TC; //leggo il valore di TC TIMER 3
	enable_timer(3);


	if(i==N-1){//5 acquisizioni effettuate
		disable_timer(3); //interrompo il timer 3
		reset_timer(3);   //
		tempi_variazioni[i] = timer3_timestamp;
		nr_acquisizioni++;
		switch_to_monitor(timer3_timestamp); // passo in modalit� monitor
	}
	else if(i<N) {
		tempi_variazioni[i] = timer3_timestamp;
		i++;
		nr_acquisizioni++;
	}

	
}




uint8_t increase_score_exam(int player)
{
    return 0;
}

int is_colliding_exam(int* abc1, int abc2)
{
    return 0;
}




