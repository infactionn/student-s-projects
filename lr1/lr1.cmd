
MEMORY

{
    VECS:    o=00000000h    l=00000200h    
    PMEM:    o=00000200h l=0000FE00h 
    BMEM:    o=80000000h l=01000000h
}
SECTIONS
{
    .intvecs    >    0h
    .text        >    BMEM
    .rtdx_text    >    BMEM
    .far        >    BMEM
    .stack        >    BMEM
    .bss        >    BMEM
    .cinit        >    BMEM
    .pinit        >    BMEM
    .cio        >    BMEM
    .const        >    BMEM
    .data        >    BMEM
    .rtdx_data    >    BMEM
    .switch        >    BMEM
    .system        >    BMEM
}