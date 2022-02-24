;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                AREA constants, DATA, READONLY
Sector_prices   DCD 0x01, 25, 0x02, 40, 0x03, 55, 0x04, 65, 0x05, 80 
                DCD 0x06, 110
				;;;;
				; esempio caricamento
				;ldr R5, =Sector_prices
				;ldr r6, [R5]
				;;;;;					
Sector_quantity DCD 0x02, 250, 0x05, 250, 0x03, 550, 0x01, 150, 0x04 
                DCD 100, 0x06, 200
					
Num_sectors     DCD 6	

; purchase request
Tickets         DCD 0x05, 2, 0x03, 10, 0x01, 120
Ticket_requests DCD 3
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;			
				AREA my_data, DATA, READWRITE
					
total_tickets          space 4
Sector_quantity_res	   space 48
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
				
				AREA asm_functions, CODE, READONLY				
                EXPORT  duty_cycle
duty_cycle 
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}	
                                                  ;r0            ;r1              ;r2             ;r3  
				;duty_cycle_val = duty_cycle(valore_iniziale, max_time, tempi_variazioni, nr_acquisizioni);

				;controllo il valore_iniziale
				MOV R6, #1 ; contatore cicli
				CMP r0, #1
				BEQ IN_VAL_UNO  ; il valore iniziale era == 1
				BLO IN_VAL_ZERO ; il valore iniziale era == 0
				

IN_VAL_UNO
		CMP R3, #0 ; se non ho acquisto nulla e il val iniziale era 1, torno 100
		MOVEQ R0, #100
		BEQ FINE
		; se invece ci sono acquisizioni, proseguo
		ANDS R4, R3, #1 ;AND con 1 di nr_acquisizioni per vedere se � pari(R4=0) o dispari(R4<>0)
		BEQ IN_UNO__NR_EL_PARI
		B   IN_UNO__NR_EL_DISP

IN_VAL_ZERO
		CMP R3, #0 ; se non ho acquisto nulla e il val iniziale era 0, torno 0
		MOVEQ R0, #0
		BEQ FINE
		; se invece ci sono acquisizioni, proseguo
		ANDS R4, R3, #1 ;AND con 1 di nr_acquisizioni per vedere se � pari(R4=0) o dispari(R4<>0)
		BEQ IN_ZERO__NR_EL_PARI
		B   IN_ZERO__NR_EL_DISP


								  ;r0            ;r1              ;r2             ;r3  
;duty_cycle_val = duty_cycle(valore_iniziale, max_time, tempi_variazioni, nr_acquisizioni);

IN_UNO__NR_EL_PARI ;DUTY_CYCLE = MAX_TIME - (SUM(EL IN POS PARI)) + (SUM(EL IN POS DISPARI))
		MOV r0, r1 ; sposto max_time in R0
loop1 	LDR R4, [R2], #4 ; carico il contenuto dell'array (increment after)
		ANDS R5, r6, #1 ;AND con 1 controllo se sto ciclando un indice pari o dispari
		ADDNE R0, R0, R4 ;se l'indice era dispari
		SUBEQ R0, R0, R4 ;se l'indice era pari
		CMP R6, R3
		ADD  R6, R6, #1 ; incremento contatore ciclo
		BNE loop1
		B CONCLUDE		


IN_UNO__NR_EL_DISP ;DUTY_CYCLE = (SUM(EL IN POS DISPARI)) - (SUM(EL IN POS PARI))
		MOV r0, #0 ; inizializzo R0
loop2 	LDR R4, [R2], #4 ; carico il contenuto dell'array (increment after)
		ANDS R5, R6, #1 ;AND con 1 controllo se sto ciclando un indice pari o dispari
		ADDNE R0, R0, R4 ;se l'indice era dispari
		SUBEQ R0, R0, R4 ;se l'indice era pari
		CMP R6, R3
		ADD  R6, R6, #1 ; incremento contatore ciclo
		BNE loop2
		B CONCLUDE	

IN_ZERO__NR_EL_PARI ;DUTY_CYCLE = (SUM(EL IN POS PARI)) - (SUM(EL IN POS DISPARI))
		MOV r0, #0 ; inizializzo R0
loop3 	LDR R4, [R2], #4 ; carico il contenuto dell'array (increment after)
		ANDS R5, R6, #1 ;AND con 1 controllo se sto ciclando un indice pari o dispari
		SUBNE R0, R0, R4 ;se l'indice era dispari
		ADDEQ R0, R0, R4 ;se l'indice era pari
		CMP R6, R3
		ADD  R6, R6, #1 ; incremento contatore ciclo
		BNE loop3
		B CONCLUDE	

IN_ZERO__NR_EL_DISP ;DUTY_CYCLE = MAX_TIME - (SUM(EL IN POS DISPARI)) + (SUM(EL IN POS PARI))
		MOV r0, r1 ; sposto max_time in R0
loop4 	LDR R4, [R2], #4 ; carico il contenuto dell'array (increment after)
		ANDS R5, R6, #1 ;AND con 1 controllo se sto ciclando un indice pari o dispari
		SUBNE R0, R0, R4 ;se l'indice era dispari
		ADDEQ R0, R0, R4 ;se l'indice era pari
		CMP R6, R3
		ADD  R6, R6, #1 ; incremento contatore ciclo
		BNE loop4
		B CONCLUDE	
 
 
CONCLUDE ; calcolo la percentuale del tempo ON (salvato in R0) / max_time (R1)
		MOV R7, #100
		MUL R0, R0, R7
		UDIV R0, R0, R1
		

FINE

;  				MOV r5, #0
;  				SUB r1, #1
;  first_negative				
;  				LDR	r3, [r0,r1, LSL #2]				
;  				CMP r3, #0
;  				BLT loop				
;  				SUBS r1, #1				
;  				BLT fine
;  				B	first_negative
				
;  loop			SUBS r1, #1
;  				MOVMI R5, R3
;  				BMI	fine
;  				LDR r2, [r0,r1, LSL #2]
;  				CMP r2, #0
;  				SUBLTS r4, r3, r2
;  				MOVLT r3, r2
;  				B	loop
								
;  				; setup a value for R0 to return
;  fine				
				; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
                END
				
				