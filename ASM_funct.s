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
				;duty_cycle_val = duty_cycle(valore_iniziale, temp_tot, tempi_variazioni, nr_acquisizioni);
				; R0   = sodd, R1   = neutro, R2= insodd, R3 = &ps
				; SP#4 = &pn,  SP#8 = &pi
				ldr R5, =Sector_prices
				ldr r6, [R5]
				

				;controllo il valore_iniziale
				CMP r0, #1
				BEQ IN_VAL_UNO  ; il valore iniziale era == 1
				BLO IN_VAL_ZERO ; il valore iniziale era == 0
				

IN_VAL_UNO
		ANDS R4, R3, #1 ;AND con 1 di nr_acquisizioni per vedere se � pari(R4=0) o dispari(R4<>0)
		BEQ IN_UNO__NR_EL_PARI
		B   IN_UNO__NR_EL_DISP

IN_VAL_ZERO
		ANDS R4, R3, #1 ;AND con 1 di nr_acquisizioni per vedere se � pari(R4=0) o dispari(R4<>0)
		BEQ IN_ZERO__NR_EL_PARI
		B   IN_ZERO__NR_EL_DISP


IN_UNO__NR_EL_PARI


IN_UNO__NR_EL_DISP


IN_ZERO__NR_EL_PARI


IN_ZERO__NR_EL_DISP

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
				
				