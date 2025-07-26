.syntax unified
.cpu cortex-m0
.thumb

.global Reset_Handler
.global _estack

.section .isr_vector, "a", %progbits
.type isr_vector, %object
isr_vector:
  .word _estack
  .word Reset_Handler
  .word Default_Handler /* NMI */
  .word Default_Handler /* HardFault */
  .word 0, 0, 0
  .word Default_Handler /* SVCall */
  .word 0
  .word 0
  .word Default_Handler /* PendSV */
  .word Default_Handler /* SysTick */
  .word Default_Handler /* IRQ0 */
  /* Add more IRQs as needed */

.section .text.Reset_Handler
Reset_Handler:
  /* Init stack and jump to main */
  bl main
  b .

.type Default_Handler, %function
Default_Handler:
  b .

