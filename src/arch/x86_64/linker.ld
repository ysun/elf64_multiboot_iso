ENTRY(start)

SECTIONS {
    . = 0x30000;

    .boot :
    {
        /* ensure that the multiboot header is at the beginning */
        *(.multiboot_header)
    }

    . = 0x40000;
    .text :
    {
        *(.text)
    }
/*
    . = 0x50000;
    .text.1 :
    {
        *(.text.1)
    }
*/

}
