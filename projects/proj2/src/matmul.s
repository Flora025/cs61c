.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
# 	d = matmul(m0, m1)
# Arguments:
# 	a0 (int*)  is the pointer to the start of m0 
#	a1 (int)   is the # of rows (height) of m0
#	a2 (int)   is the # of columns (width) of m0
#	a3 (int*)  is the pointer to the start of m1
# 	a4 (int)   is the # of rows (height) of m1
#	a5 (int)   is the # of columns (width) of m1
#	a6 (int*)  is the pointer to the the start of d
# Returns:
#	None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 72.
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 73.
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 74.
# =======================================================
matmul:

    # Error checks
    ble a1, x0, exit72
    ble a2, x0, exit72
    ble a4, x0, exit73
    ble a5, x0, exit73
    bne a2, a4, exit74
    # Prologue
    addi sp, sp, -44
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw s4, 16(sp)
    sw s5, 20(sp)
    sw s6, 24(sp)
    sw s7, 28(sp)
    sw s8, 32(sp)
    sw s9, 36(sp)
    sw ra, 40(sp)
    mv s0, a0 # s0: p0
    mv s1, a1 # s1: nRow0
    mv s2, a2 # s2: nCol0
    mv s3, a3 # s3: p1
    mv s4, a4 # s4: nRow1
    mv s5, a5 # s5: nCol1
    mv s6, a6 # s6: pD
    mv s7, x0 # i=0
    li s9, 0 # global k
outer_loop_start:
    # for each row of m0
    beq s7, s1, outer_loop_end
    add s8, x0, x0 # j=0
    # mv s5, a5 # s5: nCol1
inner_loop_start:
    # for each col of m1
    beq s8, s5, inner_loop_end
    # arrange args for dot
    slli t0, s7, 2
    mul t0, t0, s2
    add a0, s0, t0 # m0[i]
    slli t1, s8, 2
    add a1, s3, t1 # m1[j]
    mv a2, s2
    addi a3, x0, 1
    mv a4, s5
    # call dot
    jal dot
    # save res
    slli t1, s9, 2 # step = i << 2
    add t1, t1, s6 # cur Pos
    sw a0, 0(t1)

    addi s8, s8, 1 # j++
    # addi s5, s5, -1 # nCol1--
    addi s9, s9, 1 # k++
    jal x0, inner_loop_start

inner_loop_end:
    addi s7, s7, 1 # i++
    # addi s1, s1, -1
    jal x0, outer_loop_start

outer_loop_end:
    # Epilogue
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw s4, 16(sp)
    lw s5, 20(sp)
    lw s6, 24(sp)
    lw s7, 28(sp)
    lw s8, 32(sp)
    lw s9, 36(sp)
    lw ra, 40(sp)
    addi sp, sp, 44
    
    ret

exit72:
    li a1, 72
    j exit2
exit73:
    li a1, 73
    j exit2
exit74:
    li a1, 74
    j exit2
