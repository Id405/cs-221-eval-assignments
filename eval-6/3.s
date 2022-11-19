.data
sunday: .asciiz "sunday"
monday: .asciiz "monday"
tuesday: .asciiz "tuesday"
wednesday: .asciiz "wednesday"
thursday: .asciiz "thursday"
friday: .asciiz "friday"
saturday: .asciiz "saturday"
daytable: .word su mo tu we th fr sa default
string: .align 10

.text
.globl main

main:
    li $a0 2
    la $a1 string 
    jal day
    move $a0 $a1
    li $v0 4
    syscall
    li $v0 10
    syscall
day:
    mult $a0 4
    lw $t0 daytable($a0)
    jr $t0
su:
    la $t1 sunday
    j string_copy
mo:
    la $t1 monday
    j string_copy
tu:
    la $t1 tuesday
    j string_copy
we:
    la $t1 wednesday
    j string_copy
th:
    la $t1 thursday
    j string_copy
fr:
    la $t1 friday
    j string_copy
sa:
    la $t1 saturday
    j string_copy
string_copy:
   	li $t0 0
string_copy_loop:
    addu $t2 $t1 $t0
    lb $t2 $t2
    addu $t3 $a1 $t0
    sb $t2 $a1
    bne $t2 0 string_copy_loop
    li $v0 1
    jr $ra
default:
    la $v0 0
    jr $ra
