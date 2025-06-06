ENTRY(entry)
OUTPUT_FORMAT("binary")
phys = 0x00100000;

SECTIONS
{
    . = phys;

    .entry              : { __entry_start = .;      *(.entry)   }
    .text               : { __text_start = ALIGN(8); KEEP(*(multiboot_header)) *(.text)   }
    .data               : { __data_start = .;       *(.data)    }
    .rodata             : { __rodata_start = .;     *(.rodata)  }
    .bss                : { __bss_start = .;        *(.bss)     }
    
    __end = .;
}