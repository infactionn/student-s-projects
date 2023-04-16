	.def	_dotp
_dotp:
	MVK .S1 256, A1
	MVK .S2 2,B6
	ZERO .L1 A7
loop: 
	LDH .D1 *A4++, A2
	LDH .D2 *B4++, B2
	NOP 4
	SUB .L2x A2,B2,B7
	NOP 2
	MPY .M2x B7,B7,B5
	NOP
	ADD .L1 A7, B5, A7
	NOP
	SUB .S1 A1, 1, A1
 [A1] B .S2 loop
	NOP 5
	ADD .L1 A7,A7,A7
	MV .S1 A7, A4
	B .S2 B3