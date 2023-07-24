.globl argmax

.text
# =================================================================
# FUNCTION: Given a int vector, return the index of the largest
#	element. If there are multiple, return the one
#	with the smallest index.
# Arguments:
# 	a0 (int*) is the pointer to the start of the vector
#	a1 (int)  is the # of elements in the vector
# Returns:
#	a0 (int)  is the first index of the largest element
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 77.
# Testing:
#  python3 -m unittest unittests.TestArgmax -v
# =================================================================
argmax:
    ble a1, x0, exit
    # Prologue
    addi sp, sp, -12
    sw s0, 0(sp) # a0
    sw s1, 4(sp) # a1
    sw s2, 8(sp) # 4k
    add s0, a0, x0
    add s1, a1, x0
    addi t0, x0, 0 # k (index)
    addi t2, x0, 0 # max
loop_start:
    ble s1, x0, loop_end
    slli s2, t0, 2 # k << 2
    add t1, s2, s0
    lw a0, 0(t1)
    ble a0, t2, loop_continue # if t0 <= t1 then continue
    add t2, t0, x0
    jal x0, loop_continue

loop_continue:
    addi t0, t0, 1 # k++
    addi s1, s1, -1 # num--
    jal x0, loop_start

loop_end:
    add a0, t2, x0
    # Epilogue
    lw s0, 0(sp) # a0
    lw s1, 4(sp) # a1
    lw s2, 8(sp) # 4k
    addi sp, sp, 12
    ret
exit:
    li a1, 77
    j exit2
