extern backupregisters

%macro backupGPR 0

push       rbp                                              ;Save a copy of the stack base pointer
mov        rbp, rsp                                         ;We do this in order to be 100% compatible with C and C++.
push       rbx                                              ;Back up rbx
push       rcx                                              ;Back up rcx
push       rdx                                              ;Back up rdx
push       rsi                                              ;Back up rsi
push       rdi                                              ;Back up rdi
push       r8                                               ;Back up r8
push       r9                                               ;Back up r9
push       r10                                              ;Back up r10
push       r11                                              ;Back up r11
push       r12                                              ;Back up r12
push       r13                                              ;Back up r13
push       r14                                              ;Back up r14
push       r15                                              ;Back up r15
pushf                                                       ;Back up rflags

%endmacro

extern backupcomponents


%macro backupComponents 1

;=====================================================================================================================================
;===== Begin State Component Backup =======================================================================================================================================
;=====================================================================================================================================

;=========== Before proceeding verify that this computer supports xsave and xrstor ==================================================
;Bit #26 of rcx, written rcx[26], must be 1; otherwise xsave and xrstor are not supported by this computer.
;Preconditions: rax holds 1.
mov        rax, %1

;Execute the cpuid instruction
cpuid

;Postconditions: If rcx[26]==1 then xsave is supported.  If rcx[26]==0 then xsave is not supported.

;=========== Extract bit #26 and test it ===============================================================================================

and        rcx, 0x0000000004000000                          ;The mask 0x0000000004000000 has a 1 in position #26.  Now rcx is either all zeros or
                                                            ;has a single 1 in position #26 and zeros everywhere else.
cmp        rcx, 0                                           ;Is (rcx == 0)?
je         xsavenotsupported                                ;Skip the section that backs up state component data.

;========== Call the function to obtain the bitmap of state components =================================================================

;Preconditions
mov        rax, 0x000000000000000d                          ;Place 13 in rax.  This number is provided in the Intel manual
mov        rcx, 0                                           ;0 is parameter for subfunction 0

;Call the function
cpuid                                                       ;cpuid is an essential function that returns information about the cpu

;Postconditions (There are 2 of these):

;1.  edx:eax is a bit map of state components managed by xsave.  At the time this program was written (2014 June) there were exactly 3 state components.  Therefore, bits
;    numbered 2, 1, and 0 are important for current cpu technology.
;2.  ecx holds the number of bytes required to store all the data of enabled state components. [Post condition 2 is not used in this program.]
;This program assumes that under current technology (year 2014) there are at most three state components having a maximum combined data storage requirement of 832 bytes.
;Therefore, the value in ecx will be less than or equal to 832.

;Precaution: As an insurance against a future time when there will be more than 3 state components in a processor of the X86 family the state component bitmap is masked to
;allow only 3 state components maximum.

mov        r15, 7                                           ;7 equals three 1 bits.
and        rax, r15                                         ;Bits 63-3 become zeros.
mov        r15, 0                                           ;0 equals 64 binary zeros.
and        rdx, r15                                         ;Zero out rdx.

;========== Save all the data of all three components except GPRs ====================================================================

;The instruction xsave will save those state components with on bits in the bitmap.  At this point edx:eax continues to hold the state component bitmap.

;Precondition: edx:eax holds the state component bit map.  This condition has been met by the two pops preceding this statement.
xsave      [backuparea]                                     ;All the data of state components managed by xsave have been written to backuparea.

push qword -1                                               ;Set a flag (-1 = true) to indicate that state component data were backed up.
jmp        startapplication

;========== Show message xsave is not supported on this platform ======================================================================
xsavenotsupported:

mov        rax, 0
mov        rdi, .stringformat
mov        rsi, .notsupportedmessage                        ;"The xsave instruction is not suported in this microprocessor.
call       printf

push qword 0                                                ;Set a flag (0 = false) to indicate that state component data were not backed up.

;=====================================================================================================================================
;===== End of State Component Backup =================================================================================================



%endmacro


extern restoreRegisters

%macro restoreGPR 0

;=========== Restore GPR values and return to the caller =======================================================================

popf                                                        ;Restore rflags
pop        r15                                              ;Restore r15
pop        r14                                              ;Restore r14
pop        r13                                              ;Restore r13
pop        r12                                              ;Restore r12
pop        r11                                              ;Restore r11
pop        r10                                              ;Restore r10
pop        r9                                               ;Restore r9
pop        r8                                               ;Restore r8
pop        rdi                                              ;Restore rdi
pop        rsi                                              ;Restore rsi
pop        rdx                                              ;Restore rdx
pop        rcx                                              ;Restore rcx
pop        rbx                                              ;Restore rbx
pop        rbp                                              ;Restore rbp

ret                                                         ;No parameter with this instruction.  This instruction will pop 8 bytes from
       
%endmacro

extern restoreComponents

%macro restorecomponents 0

;===============================================================================================================================
;===== Begin State Component Restore ===========================================================================================
;===============================================================================================================================

;===== Check the flag to determine if state components were really backed up ===================================================

pop        rbx                                              ;Obtain a copy of the flag that indicates state component backup or not.
cmp        rbx, 0                                           ;If there was no backup of state components then jump past the restore section.
je         setreturnvalue                                   ;Go to set up the return value.

;Continue with restoration of state components;

;Precondition: edx:eax must hold the state component bitmap.  Therefore, go get a new copy of that bitmap.

;Preconditions for obtaining the bitmap from the cpuid instruction
mov        rax, 0x000000000000000d                          ;Place 13 in rax.  This number is provided in the Intel manual
mov        rcx, 0                                           ;0 is parameter for subfunction 0

;Call the function
cpuid                                                       ;cpuid is an essential function that returns information about the cpu

;Postcondition: The bitmap in now in edx:eax

;Future insurance: Make sure the bitmap is limited to a maximum of 3 state components.
mov        r15, 7
and        rax, r15
mov        r15, 0
and        rdx, r15

xrstor     [backuparea]

;===============================================================================================================================
;===== End State Component Restore =============================================================================================
;===============================================================================================================================


setreturnvalue: ;=========== Set the value to be returned to the caller ========================================================

push       r14                                              ;r14 continues to hold the first computed floating point value.
movsd      xmm0, [rsp]                                      ;That first computed floating point value is copied to xmm0[63-0]
pop        r14                                              ;Reverse the push of two lines earlier.

%endmacro