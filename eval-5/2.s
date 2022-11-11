.data
array:
    .word    1
    .word    2
    .word    3
    .word    4
    .word    5
sep: .asciiz ", "

.text
.globl main

main: # testing stuff :)
    la $a0 array
    li $a1 5
    li $t0 3
    li $t1 5
    li $t2 4

    li $t3 0 # begin problem
    li $s0 0
    li $s1 0
    li $s2 0
    li $s3 0
    ble $t0 $t1 swap
    move $t4 $t1
    move $t1 $t0
    move $t0 $t4
swap:
    ble $t1 $t2 loop
    move $t4 $t1
    move $t1 $t2
    move $t2 $t4
loop:
    mul $t4 $t3 4 
    add $t4 $a0 $t4
    lw $t4 ($t4)
    ble $t0 $t4 greater
    addi $s0 $s0 1
    j end
greater:
    blt $t4 $t2 middle
    addi $s3 $s3 1
    j end
middle:
    blt $t4 $t1 lowermiddle
    addi $s1 $s1 1
    j end
lowermiddle:
    addi $s2 $s2 1
end:
    addi $t3 $t3 1
    blt $t3 $a1 loop

    li $v0 1 # then some more testing stuff
    move $a0 $s0
    syscall

    li $v0 4
    la $a0 sep
    syscall

    li $v0 1
    move $a0 $s1
    syscall

    li $v0 4
    la $a0 sep
    syscall
    
    li $v0 1
    move $a0 $s2
    syscall

    li $v0 4
    la $a0 sep
    syscall
    
    li $v0 1
    move $a0 $s3
    syscall

    li $v0 10
    syscall
