;========1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2=========
;Author information
;  Author name: William Murmann
;  Author email: wmurmann@csu.fullerton.edu or wmurmann@gmail.com
;  Author location: CSUF
;Course information
;  Course number: CPSC240
;  Assignment number: 7
;  Due date: 2015-May-14
;Project information
;  Project title: Stack Fun!
;  Purpose: To view the stack, print rpb's of nested c++ programs and change variables via the stack
;  Status: This module is working correctly
;  Project files: findframe.asm, backupmacro.inc, c1.cpp, c2.cpp, c3.cpp, c4.cpp c5.cpp
;Module information
;  This module's call name: findframe
;  Language: X86-64
;  Syntax: Intel
;  Date last modified: 2015-May-13
;  Purpose: To view the stack, print rpb's of nested c++ programs and change variables via the stack
;  File name: findframe.asm
;  Status: This module is working properly
;  Future enhancements: None
;Translator information
;  Linux: nasm -f elf64 -l findframe.lis -o findframe.o findframe.asm
;References and credits
;  Professor Holliday
;Format information
;  Page width: 172 columns
;  Begin comments: 61
;  Optimal print specification: Landscape, 7 points or smaller, monospace, 8Â½x11 paper
;
;===== Begin code area =================================================================================================================

%include "debug.inc"
%include "backupmacro.inc"

extern printf                                               
extern scanf                                                ;External C++ function for reading from the standard input device

global findframe                                            ;This makes findframe callable by functions outside of this file.
global backupregisters
global backupcomponents
global restoreComponents
global restoreRegisters


segment .data                                               ;Place initialized data here

;===== Declare some messages ============================================================================================================
hex_msg  db     "RBP:  0X%016lx", 10, 0

xsavenotsupported.notsupportedmessage db "The xsave instruction and the xrstor instruction are not supported in this microprocessor.", 10
                                      db "However, processing will continue without backing up state component data", 10, 0

stringformat db "%s", 0                                     ;general string format

xsavenotsupported.stringformat db "%s", 0

eight_byte_format db "%lf", 0                               ;general 8-byte float format
int_format        db "%ld", 0

segment .bss                                                ;Place un-initialized data here.

align 64                                                    ;Insure that the inext data declaration starts on a 64-byte boundar.
backuparea resb 832                                         ;Create an array for backup storage having 832 bytes.
localbackup resb 832                                        ;Create an array for backup storage having 832 bytes.
;===== Begin executable instructions here =====================================================================

segment .text                                               ;Place executable instructions in this segment.

findframe:                                                  ;Entry point.  Execution begins here.

;=========== Back up GPRs and Component Macros ===========================================================

backupGPR

backupComponents 1

;===================================================================================================================
startapplication: 

;Inspect the stack visually.  
mov       r9, rbp                                           ;rbp is copied safely into r9
mov       rbp, rsp                                          ;The starting address for dumpstack must be in rsp: This ruins the nice link list.
dumpstack 21,0,120                                          ;View 120 quadwords of stack
mov       rbp, r9                                           ;The former value of rbp is restored

mov       r15, 0 											;start loop counter

start:
cmp        r15, 767 										;end of loop counter
JG	   end


	align 16                                                ;get ready to print in hex
	mov qword  rax, 0                                       ;no avx registers to print
	mov        rdi, hex_msg									;RBP: value
	mov        rsi, [rsp+r15]								;get rbp from stack
	call       printf										;print 

	add        r15, 256                                     ;increment to get next rbp

jmp        start                                            ;jump back to top of loop
end:                                                        ;end of loop


mov qword [rsp + 392], 16383 								;change value of 8 in program c1.cpp

dumpstack 21,0,120                                          ;View 120 quadwords of stack

;========== Restore registers and components        =======================================================

restorecomponents
restoreGPR     

;========== End of program harmonic.asm =======================================================================================

