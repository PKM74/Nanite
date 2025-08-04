ENTRY(start)

SECTIONS
{
    . = ALIGN(8);

    .boot               : { KEEP(*(.multiboot_header)) __boot_start = .;        *(.boot)   }
    .entry              : { __entry_start = .;      *(.entry)   }
    .text               : { __text_start = .;       *(.text)   }
    .data               : { __data_start = .;       *(.data)    }
    .rodata             : { __rodata_start = .;     *(.rodata)  }
    .bss                : { __bss_start = .;        *(.bss)     }
    
    __end = .;
}