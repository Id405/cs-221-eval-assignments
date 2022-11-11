.data
node4:
    .word 0
    .half 8
    .align 2
    
node3:
    .word node4
    .half 6
    .align 2
    
node2:
    .word node3
    .half 10
    .align 2
    
node1:
    .word node2
    .half 15
    .align 2

.text
.globl main

main:
    la $a0 node1 # for testing :)

    li $v0 0
loop:
    lw $t1 ($a0)
    addi $a0 $a0 4
    lh $t2 ($a0)
    add $v0 $v0 $t2
    move $a0 $t1
    bne $a0 0 loop

	move $a0 $v0
    li $v0 1 # then some testing stuff :)
    syscall
    li $v0 10
    syscall
