.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int vectors
# Arguments:
#   a0 (int*) is the pointer to the start of v0
#   a1 (int*) is the pointer to the start of v1
#   a2 (int)  is the length of the vectors
#   a3 (int)  is the stride of v0
#   a4 (int)  is the stride of v1
# Returns:
#   a0 (int)  is the dot product of v0 and v1
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 75.
# - If the stride of either vector is less than 1,
#   this function terminates the program with error code 76.
# Testing:
# python3 -m unittest unittests.TestDot -v
# =======================================================
dot:
    ble a2, x0, exit75
    ble a3, x0, exit76
    ble a4, x0, exit76
    # Prologue
    addi sp, sp, -20
    sw s0, 0(sp) # a0, pointer to the start of v0
    sw s1, 4(sp) # a1, pointer to the start of v1
    sw s2, 8(sp) # a2, len of vec
    sw s3, 12(sp) # a3, stride of v0
    sw s4, 16(sp) # a4, stride of v1
    addi t0, x0, 0 # t0: sum
    add s0, a0, x0 # s0: p0
    add s1, a1, x0 # s1: p1
    add s2, a2, x0 # s2: len
    add s3, a3, x0 # s3: stride0
    add s4, a4, x0 # s4: stride1
    addi t1, x0, 0 # t1: k
loop_start:
    ble s2, x0, loop_end
    slli t2, t1, 2 # step0 = k << 2
    slli t3, t1, 2 # step1
    mul t2, t2, s3 # stride0
    mul t3, t3, s4 # stride1
    add t2, t2, s0 # curPos0
    add t3, t3, s1 # curPos1
    lw a0, 0(t2)
    lw a1, 0(t3)
    mul t4, a0, a1
    add t0, t0, t4 # sum += product

    addi t1, t1, 1 # k++
    addi s2, s2, -1 # num--
    jal x0, loop_start

loop_end:
    add a0, t0, x0
    # Epilogue
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw s4, 16(sp)
    addi sp, sp, 20
    ret
exit75:
    li a1, 75
    j exit2
exit76:
    li a1, 76
    j exit2
