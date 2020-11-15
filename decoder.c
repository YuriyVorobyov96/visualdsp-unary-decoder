#include "def21060.h"
#define S 8

.SECTION/PM pm_irq_svc;
nop;
jump start;
nop;
nop;

.SECTION/PM spt0_svc;
nop;
jump decode;
nop;
nop;

.SEGMENT/DM dm_data;
.VAR source1[4]; 
.VAR source2[4]; 
.VAR TCB_Block1[S] =0, 0,0, 0,TCB_Block2+S-1,@source1, 1, source1; 
.VAR TCB_Block2[S] = 0, 0, 0, 0, TCB_Block1+S-1, @source2, 1, source2;
.ENDSEG;

.SECTION/PM pm_code;
start:
R0 = 0x3fe3f;
(LAR) = R0;
R0 = 0x04000; 
DM(LCOM) = R0; 
R0 = 0x00100; 
DM(LCTL) = R0; 
R0 = TCB_Block1 + 7; 
DM(CP2) = R0; 
R0 = 0x000C0481;
DM(STCTL0) = R0; 
I0 = source1; 
I1 = source2; 
BIT SET IMASK SPT0I; 
BIT SET MODE1 IRPTEN; 


wait: IDLE;
jump wait;
decode:
	I3 = I2;
	BTST R2 BY R0;
	IF SZ I3 = I1;
	R2 = R1 - R2;
	R3 = 0;



	R1 = DM(LBUF2);
	
	I4 =  slovar;
	M4 = R1;
	R7=0;
	MODIFY(I4,M4);
	R5 = DM(I4,0);
	
	I4 = slovar;
	I5 =  slovar2;
	M5 = R1 ;
	MODIFY(I5,m5);
	R15 = DM(I5,0)
	DM(I3,1) = R15;
	R6 = DM(I4,0);
	LCNTR = 4 ,DO xxx UNTIL LCE;
		I5 =  slovar2;	
		COMP(R6,R5);
		IF GT  JUMP yyy;
		R6 = R6 + 1;
		DM(I4,0) = R6 ;
		M6=R6;
		MODIFY(I5, M6); 
		DM(I5,0) = R7;
		yyy:
		R7=R7+1;
		MODIFY(I4,1);
	xxx:R6 = DM (I4,0);
	
	
	I4 =  slovar;
	M4 = R1;
	MODIFY(I4,M4);
	DM(I4,M4) = 0;
	DM(slovar2) = R1;
	
	
	

	

RTI;
