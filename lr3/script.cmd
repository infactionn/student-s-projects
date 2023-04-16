-c
-heap 0x1000
-stack 0x1000
-u __vectors
-u _auto_init
_HWI_Cache_Control = 0;
_RTDX_interrupt_mask = ~0x000001808;
MEMORY
{
	VECS:  o=00000000h l=00000200h /*  interrupt vectors */
	PMEM:  o=00000200h l=0000FE00h /*  Internal  RAM (L2) mem */
	BMEM:  o=80000000h l=01000000h /* CE0, SDRAM, 16 MBytes  */
}
SECTIONS
{
	.intvecs >  0h
	.text >  BMEM
	.rtdx_text  >  BMEM
	.far >  BMEM
	.stack  >  BMEM
	.bss >  BMEM
	.cinit  >  BMEM
	.pinit  >  PMEM
	.cio >  BMEM
	.const  >  BMEM
	.data >  BMEM
	.rtdx_data  >  BMEM
	.switch  >  BMEM
	.sysmem  >  BMEM
}