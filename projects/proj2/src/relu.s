.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
# 	a0 (int*) is the pointer to the array
#	a1 (int)  is the # of elements in the array
# Returns:
#	None
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 78.
# Test:
# cd unittests
# python3 -m unittest unittests.TestRelu -v
# ==============================================================================
relu:
    ble a1, x0, exit
    # Prologue
    addi sp, sp, -12
    sw s0, 0(sp) # s0: saves the pointer to the array
    sw s1, 4(sp) # s1: saves the # of elements in the array
    sw s2, 8(sp) # s2: saves cur step
    add s0, a0, x0
    add s1, a1, x0
    addi t0, x0, 0 # k
loop_start:
    ble s1, x0, loop_end # if num == 0, end
    # get next num
    slli s2, t0, 2 # update cur pointer step in s2
    add t1, s2, s0 # get cur pointer position t1
    lw a0, 0(t1) # a0 = s0[k]
    # abs(num)
    bge a0, zero, loop_continue # if t0 >= 0
    sub a0, a0, a0 # else if t0 < 0
    # put num back
    sw a0, 0(t1)
    addi t0, t0, 1 # k++
    addi s1, s1, -1 # num--
    jal x0, loop_start

loop_continue:
    # move the pointer
    addi t0, t0, 1 # k++
    addi s1, s1, -1 # num--
    jal x0,loop_start

loop_end:
    add a0, s0, x0
    add a1, s1, x0
    # Epilogue
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    addi sp, sp, 12
    
	ret
exit:
    li a1, 78
    j exit2
