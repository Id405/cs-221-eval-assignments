.data
array:
    .float 10.5
    .float 30.2
   	.float 0.9
    .float 0.67

.text
.globl main

main:
    li.s $f0 2.13
  	mfc1 $a0 $f0
  	la $a1 array
  	li $a2 4
	jal accumulator_exponent

accumulator_exponent:
    mfc1 $f0 $a0
	li $t0 0
loop:
    mult $t1 $t0 4
    lh.s $f1 array($t1)
    add.s $f0 $f1
    addu $t0 4
    blt $t0 loop

    mfc1 $v0 $f0
    srl $v0 $v0 23
    and $v0 $v0 255
    jr $ra
