.data
array1:
    .word    1
    .word    2
    .word    3
    .word    4
    .word    5
array2:
    .word    6
    .word    7
    .word    8
    .word    9
    .word    10

sep: .asciiz ", "
nl: .asciiz "\n"

.text
.globl main

main:
    la $a0 array1 # testing stuff
    la $a1 array2
    la $a2 5

    li $t0 0      # begin problem
loop:
    mul $t1 $t0 4
    add $t2 $a0 $t1
    add $t1 $a1 $t1
    lw $t3 ($t2)
    lw $t4 ($t1)
    sw $t3 ($t1)
    sw $t4 ($t2)
    addi $t0 $t0 1
    blt $t0 $a2 loop

    li $t0 0      # more testing stuff
printloop1:
    mul $t1 $t0 4
    add $t1 $a0 $t1
    lw $t1 ($t1)
    move $t2 $a0
    li $v0 1
    move $a0 $t1
    syscall
    li $v0 4
    la $a0 sep
    syscall
    move $a0 $t2
    addi $t0 $t0 1
    blt $t0 $a2 printloop1
    li $v0 4
    la $a0 nl
    syscall
    li $t0 0
printloop2:
    mul $t1 $t0 4
    add $t1 $a1 $t1
    lw $t1 ($t1)
    move $t2 $a0
    li $v0 1
    move $a0 $t1
    syscall
    li $v0 4
    la $a0 sep
    syscall
    move $a0 $t2
    addi $t0 $t0 1
    blt $t0 $a2 printloop2
    li $v0 10
    syscall
