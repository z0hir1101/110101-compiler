section .data
num1 dd 5

section .text
global _start
_start:

mov rax, 60
mov rdi, [num1]
syscall
