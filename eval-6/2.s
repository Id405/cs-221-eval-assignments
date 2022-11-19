.data
array:
    .word 27
    .word 3
    .word 13
    .word 95
    .word 0
    .word 32
array2:
    .word 32
    .word 9
    .word 2
    .word 6
    .word 472
    .word 19
array3:
    .align 48
sep: .asciiz ", "

.text
.globl main

main:
    la $a0 array
    la $a1 array2
    la $a2 array3
	li $a3 6
	jal array_product

	li $t0 0
loop_print:
    mul $t1 $t0 8
    addu $t1 $t1 $a2
    lh $a0 4($t1)
    li $v0 1
    syscall
    la $a0 sep
    li $v0 4
    syscall
    
	addu $t0 $t0 1
    blt $t0 $a3 loop_print

    li $v0 10
    syscall
array_product:
    push $ra
    push $s0
    push $s1
    push $s2
    push $s3
	push $s4
	move $s0 $a0
	move $s1 $a1
	move $s2 $a2
	move $s3 $a3

	li $s4 0
loop:
	mulu $t0 $s4 4
	addu $a0 $s0 $t0
	addu $a1 $s1 $t0
	mulu $t0 $s4 8
	addu $t0 $s2 $t2

	jal product
	sh ($t0) $v1
	sh 4($t0) $v0
	addu $s4 $s4 1
	blt $s4 $s3 loop
    
	pop $s4
	pop $s3
    pop $s2
    pop $s1
    pop $s0
    pop $ra
    jr $ra
product:
    mul $v0 $a0 $a1
    mfhi $v1
    jr $ra
