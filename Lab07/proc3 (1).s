.data
msg1:   .asciiz "p + q: "
newline: .asciiz "\n"

.text
.globl main

j main   # MARS needs a jump to main

# ----------------- bar(a, b, c): return (b - a) << c -----------------
bar:
    addi $sp, $sp, -4
    sw $ra, 0($sp)

    sub $t0, $a1, $a0      # b - a
    sllv $v0, $t0, $a2     # (b - a) << c

    lw $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra

# ----------------- foo(m, n, o) --------------------------------------
# p = bar(m+o, n+o, m+n)
# q = bar(m-o, n-m, n+n)
# print p+q
# return p+q
foo:
    addi $sp, $sp, -20
    sw $ra, 0($sp)
    sw $s0, 4($sp)   # p
    sw $s1, 8($sp)   # q
    sw $s2, 12($sp)
    sw $s3, 16($sp)

    move $s2, $a0    # m
    move $s3, $a1    # n
    move $t5, $a2    # o

    # ---- p = bar(m+o, n+o, m+n) ----
    add $a0, $s2, $t5       # a0 = m + o
    add $a1, $s3, $t5       # a1 = n + o
    add $a2, $s2, $s3       # a2 = m + n
    jal bar
    move $s0, $v0           # p = result

    # ---- q = bar(m - o, n - m, n + n) ----
    sub $a0, $s2, $t5       # a0 = m - o
    sub $a1, $s3, $s2       # a1 = n - m
    add $a2, $s3, $s3       # a2 = n + n
    jal bar
    move $s1, $v0           # q = result

    # ---- p + q ----
    add $t0, $s0, $s1       # t0 = p + q

    # Print "p + q: "
    li $v0, 4
    la $a0, msg1
    syscall

    # Print value of t0
    li $v0, 1
    move $a0, $t0
    syscall

    # Newline
    li $v0, 4
    la $a0, newline
    syscall

    move $v0, $t0           # return p + q

    lw $ra, 0($sp)
    lw $s0, 4($sp)
    lw $s1, 8($sp)
    lw $s2, 12($sp)
    lw $s3, 16($sp)
    addi $sp, $sp, 20
    jr $ra

# ----------------- main() -----------------
main:
    li $t0, 2        # x = 2
    li $t1, 4        # y = 4
    li $t3, 6        # z = 6

    # Save x + y + z in $t4
    add $t4, $t0, $t1    # x + y
    add $t4, $t4, $t3    # x + y + z

    # Call foo(x, y, z)
    move $a0, $t0        # m = x
    move $a1, $t1        # n = y
    move $a2, $t3        # o = z
    jal foo              # result in $v0 (p + q)

    add $t2, $t4, $v0    # t2 = x + y + z + foo()

    # Print "p + q: ..." was already done inside foo

    li $v0, 1            # print z (t2)
    move $a0, $t2
    syscall

    li $v0, 4
    la $a0, newline
    syscall

    li $v0, 10           # exit
    syscall




