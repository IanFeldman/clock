/* Entry point (Reset_Handler is in startup file) */
ENTRY(Reset_Handler)

/* Define memory layout */
MEMORY {
  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 16K
  RAM   (rwx): ORIGIN = 0x10000000, LENGTH = 4K
}

SECTIONS {
  /* Interrupt vector table and code */
  .text : {
    KEEP(*(.isr_vector))   /* vector table at 0x0000_0000 */
    *(.text*)              /* actual code */
    *(.rodata*)            /* read-only data (const) */
    _etext = .;
  } > FLASH

  /* Initialized data section: copied from FLASH to RAM on startup */
  .data : AT(_etext) {
    _data = .;
    *(.data*)
    _edata = .;
  } > RAM

  /* Uninitialized data (zero-initialized on startup) */
  .bss : {
    _bss = .;
    *(.bss*)
    *(COMMON)
    _ebss = .;
  } > RAM

  /* Stack pointer (top of RAM) */
  . = ORIGIN(RAM) + LENGTH(RAM);
  _estack = .;
}

