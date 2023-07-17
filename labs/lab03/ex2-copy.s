.globl main

.data
source:
    .word   3
    .word   1
    .word   4
    .word   1
    .word   5
    .word   9
    .word   0
dest:
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0

# translate
.text
fun:
    # x is in a0
    addi t0, a0, 1 # (x + 1)
    sub t1, x0, a0 # -x
    mul a0, t0, t1 # x = (-x) * (x + 1)
    jr ra
# updates values in DEST and returns SUM
main:
    # BEGIN PROLOGUE
    addi sp, sp, -20 # space for stack
    sw s0, 0(sp) # save s0
    sw s1, 4(sp) # 4 from -20
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw ra, 16(sp) # save ret addr
    # END PROLOGUE
    # preps before the loop
    addi t0, x0, 0 # k = 0 (t0: k)
    addi s0, x0, 0 # sum = 0 (s0: sum)
    la s1, source # s1 = &source
    la s2, dest # s2 = &dest
loop:
    slli s3, t0, 2 # s3 = k << 2 (s3: delta position)
    add t1, s1, s3 # t1 = s1 + s3 (update t1, t1: current pointer pos)
    lw t2, 0(t1) # source[k] = *t1 (t2: source[k])
    beq t2, x0, exit # branch if source[k] == 0
    add a0, x0, t2 # x = t2 (a0: fun's argument X)
    addi sp, sp, -8 # add space for stack again
    sw t0, 0(sp) # save t0 to stk[-28]
    sw t2, 4(sp) # save t2 to stk[-24]
    jal fun # link and jump to FUN
    lw t0, 0(sp)
    lw t2, 4(sp)
    addi sp, sp, 8 # free
    add t2, x0, a0 # t2 = a0 (a0: fun's argument X)
    add t3, s2, s3 # update desk pointer position t3
    sw t2, 0(t3) # *t3 = t2 (dest[k] = 
    add s0, s0, t2 # sum += t2 (s0: sum)
    addi t0, t0, 1 # t0 += 1
    jal x0, loop
exit:
    add a0, x0, s0
    # BEGIN EPILOGUE
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw ra, 16(sp)
    addi sp, sp, 20 # free the stack
    # END EPILOGUE
    jr ra
