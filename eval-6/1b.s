.data
array:
    .half 27
    .half 3
    .half 13
    .half 95
    .half 0
    .half 32

.text
.globl main

main:
    la $a0 array
	li $a1 6
	li $a2 5
	jal decaying_sum
	li $v0 1
	syscall
	li $v0 10
	syscall
decaying_sum:
	li $a3 0
decaying_sum_t:
    beq $a1 0 return
    subu $a1 $a1 2
    divu $a3 $a3 $a2
    addu $t0 $a0 $a1
    lhu $t0 ($t0)
    addu $a3 $a3 $t0
    j decaying_sum_t
return:
    move $v0 $a3
    jr $ra
