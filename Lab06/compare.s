.data
n:      .word 25

prompt: .asciiz "Enter an integer: "
str2:   .asciiz "Less than or equal to\n"
str3:   .asciiz "Greater than\n"

.text
.globl main
main:
    # Print prompt
    li $v0, 4
    la $a0, prompt
    syscall

    # Read user input
    li $v0, 5
    syscall
    move $t0, $v0          # $t0 = user input

    # Load n = 25
    lw $t1, n              # $t1 = 25

    # Check: if input > 25 (i.e., t0 > t1)
    slt $t2, $t1, $t0      # t2 = 1 if t1 < t0 (means input > 25)
    bne $t2, $zero, greater

    # Else: input <= 25
    li $v0, 4
    la $a0, str2
    syscall
    j end

greater:
    li $v0, 4
    la $a0, str3
    syscall

end:
    li $v0, 10
    syscall


