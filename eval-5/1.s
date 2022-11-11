.data
sep: .asciiz ", "

.text
.globl main

main:                    # Test code
    li $a0 1
    li $s0 10
loopmain:
    jal fib
    move $s1 $a0
    move $a0 $v0
    li $v0 1
    syscall
    la $a0 sep
    li $v0 4
    syscall
    move $a0 $s1
    addi $a0 $a0 1
    ble $a0 $s0 loopmain
    li $v0 10
    syscall

fib:                     #   # Begin of answer
    li $t0 0             #   int a = 0;
    li $t1 1             #   int b = 1;
    li $v0 0             #   int c = 0;
    li $t3 1             #   int i = 0;
loop:
    add $v0 $t0 $t1      #   c = a + b;
    move $t0 $t1         #   a = b;
    move $t1 $v0         #   b = c;
    addi $t3 $t3 1       #   i = i + 1;
    blt $t3 $a0 loop     #   if (int i < n)
    jr $ra               #     goto loop
