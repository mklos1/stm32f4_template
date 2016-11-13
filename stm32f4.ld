ENTRY(Reset_Handler)

MEMORY
{
  RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 64K
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1024K
}

__stack = ORIGIN(RAM) + LENGTH(RAM);

_estack = __stack; 	/* STM specific definition */


SECTIONS
{       
    .isr_vectors : 
    {
      . = ALIGN(4);
      _isr_start = .;
      . = ALIGN(4);
      KEEP(*(.isr_vectors))
      . = ALIGN(4);
      _isr_end = .;      
    } >FLASH
    
    .text :
    {
      . = ALIGN(4);
      _flash_code_start = .;
        *(.text)   
      *(.text.*) 
      *(.glue_7)         /* glue arm to thumb code */
      *(.glue_7t)        /* glue thumb to arm code */      
      *(.rodata)
      *(.rodata*)   
      . = ALIGN(4);
      _flash_data_start = .;
    } >FLASH
    
    .data : 
    {
      . = ALIGN(4);
      _data_start = .;
      *(.data_begin .data_begin.*)
      *(.data .data.*)      
      *(.data_end .data_end.*)
      *(.ramsection)
      . = ALIGN(4);
      _data_end = .;    
    } >RAM AT>FLASH

    .bss (NOLOAD) :
    {
      . = ALIGN(4);
      _bss_start = .;
      *(.bss)  
      *(COMMON)     
      _bss_end = .;
    } >RAM          
}

