OUTPUT_FORMAT(binary)

SECTIONS
{
  .text 0x0 : { *(.text) }
  .data : { *(.data) }
  .rodata : { *(.rodata) }
  .bss : { *(.bss) }
}