#include "LPC17xx.h"

static int score1 = 0;
static int score2 = 0;
static uint8_t is_exam_over;


void exam_init(void);
uint8_t increase_score_exam(int); 
int is_colliding_exam(int* abc1, int abc2);
