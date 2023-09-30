.section .text {#0}
.section .text {#1}
EntryPoint:
L4:
    push rbp
    mov rbp, rsp
    sub rsp, 0x20
    lea rdx, [Ldata_0]
    mov ecx, 0
    mov r8, 0x7FF628EA92D5
    mov r9d, 0
    call 0x7FF628EA1E10
L3:
    mov rsp, rbp
    pop rbp
    ret
.section .data {#2}
Ldata_0:
.db 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x20, 0x21, 0x00
