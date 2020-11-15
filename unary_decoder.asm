#include "def21060.h" 
#define N 5			// input buffer size
#define M 2			// output buffer size
#define WORD_SIZE 32

#define S 8				// TCB size 
#define BIT_ORIGINAL 32
#define BIT_CODE 4
#define STEPS_NUMBER 16

.SECTION/PM pm_irq_svc;         
		nop;         
		jump start;         
		nop;         
		nop; 
          
.SECTION/PM spt0_svc;
		//jump work_func; 
  
.SEGMENT/DM dm_data;
		.VAR source[M] = 
			0x00000001,
			0x10010021
		;
		.VAR destination[N];
		.VAR TCB_Block1[S] = 
				0,              // For SPORTx doesn't use 
                0,              // For SPORTx doesn't use 
                0,              // Register DB - in 1D-DMA doesn't use 
                0,              // Register GP - doesn't use
                TCB_Block2+S-1, // Register CP - pointer on next TCB 
                @source,      	// Register C - counter 
                1,              // Register IM - register-modificator 
                source;       	// Register II - buffer address 
        .VAR TCB_Block2[S] = 
                0, 
                0, 
                0, 
                0, 
                TCB_Block1+S-1, 
                @destination,                 
                1,                 
                destination;
		.VAR output_size;
.ENDSEG; 

.SECTION/PM pm_code; 
start:
	I0 = source;
	I1 = destination;
	R4 = destination + N; // Last elements address
	M0 = 1;
	R1 = 1;
	R6 = WORD_SIZE - 1;
	DO source_cycle UNTIL GE;
		R2 = PASS R6 , R0 = DM(I0, M0);
		
		LCNTR = WORD_SIZE, DO count_cycle UNTIL LCE;
			BTST R0 By R2;
			IF NOT SZ R1 = R1 XOR R1, DM(I1, M0) = R1;
			R1 = R1 + 1;
	count_cycle:R2 = R2 - 1;
	R3 = I1;
	COMP(R3, R4);
	nop;
	nop;
source_cycle: nop;
	wait: 
		IDLE;         
		jump wait;
