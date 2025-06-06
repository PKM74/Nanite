ENTRY(start)

SECTIONS
{
    . = 1M;

    .boot               : { KEEP(*(.multiboot_header))}
    .entry              : { __entry_start = .;      *(.entry)   }
    .text               : { __text_start = .; *(.text)   }
    .data               : { __data_start = .;       *(.data)    }
    .rodata             : { __rodata_start = .;     *(.rodata)  }
    .bss                : { __bss_start = .;        *(.bss)     }
    
    __end = .;
}