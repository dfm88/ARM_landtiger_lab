#include "LPC17xx.h"
#define N 5

extern int is_in_monitor;

extern char valore_iniziale;
extern uint8_t last_sample;
extern uint8_t is_showing_lung_array;
extern unsigned int tempi_variazioni[N];


///
uint8_t increase_score_exam(int); 
int is_colliding_exam(int* abc1, int abc2);
///

void exam_init(void);
void switch_to_monitor(int tempo_tot);
void switch_to_acquisiz(void);
void sample_timer(void);

void show_lung_array(void);
void show_duty_cycle(void);










