; x86-to-C Interface Programming Project
; Burayag, Ethan Axl S. - S20A
; x86-64 ASM File

section .text
bits 64
default rel

global DAXPY_x86

DAXPY_x86:
    PUSH RBP
    MOV  RBP, RSP
    ADD  RBP, 16
    
    VMOVSD XMM0, [RBP + 32]

    JECXZ END            
    L1: 
        VMOVSD XMM1, [RDX]
        VMULSD XMM2, XMM1, XMM0
        VMOVSD XMM3, [R8]
        VADDSD XMM4, XMM3, XMM2
        VMOVSD [R9], XMM4
        
        ADD RDX, 8
        ADD R8, 8
        ADD R9, 8
        
        LOOP L1
    
    END:
        POP RBP
        RET