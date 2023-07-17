.globl factorial

.data
n: .word 8

.text
main:
    la t0, n # t0 = &n
    lw a0, 0(t0) # a0 = *t0
    jal ra, factorial # ra: return addr

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    # YOUR CODE HERE
    # s0: res
    # s1: k
    # prologue
    addi sp, sp, -8
    sw s0, 0(sp)
    sw s1, 4(sp)
    # end of prologue
    addi s0, x0, 1 # res = 1
    add s1, a0, x0 # k = n
    bne s1, x0, loop
loop:
    beq s1, x0, exit
    mul s0, s0, s1 # res = res * k
    addi s1, s1, -1
    jal, x0, loop
exit:
    add a0, x0, s0
    # epilogue
    lw s0, 0(sp)
    lw s1, 4(sp)
    addi sp, sp, 8
    # end of epilogue
    jr ra
    