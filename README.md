A course repo for [CS61C (fa20)](https://inst.eecs.berkeley.edu/~cs61c/fa20/).

## Summary of the Course

Centered on several great ideas in computer architecture. Specifically,

1. The first half of the course teaches what's called "the **old school** machine structures".

   - High level language program - C [lec3-6]

   - Assembly language program - RISC-V [lec7-13]

   - Machine Language - still RISC-V, but without pseudo instructions [lec7-13]

   - Hardware architecture description - block diagrams, datapaths, cache, pipelining, virtual mem, etc. [lec17-27]

   - Logic circuit description [lec14-16]

Basically, that's everything from the top -- the programmer-friendly high level language C--, to the bottom arch -- circuits, logic gates, and transistors--.

In terms of actual sequence, it's like top -> middle, then bottom -> middle, and finally the two lines meet at around project3 (DIY a CPU datapath).

2. The second half teaches the **new-school structures**, which include more recent ideas of **parallelism** / high performance programming that companies hardware improvements.

   - data-level parallelism - SIMD [lec32], MapReduce, Spark, etc. [lec36]

   - thread-level parallelism - threads, cache coherency, OpenMP, etc. [lec33-35]

   - dependability [lec38]

## Summary of the Labs

Not including ones I didn't manage to set up.

- **Lab1 Number Rep, C and CGDB**: familiarize you with c and debugging tools
- **Lab2 Advanced C**: bit manipulations, memory allocation, and pointers in C
- **Lab3 RISCV Assembly**: ask u to figure out how simple C programs work on a lower level and write RISC-V assembly code
- **Lab4 RISCV Functions, Pointers**: still RISC-V practices, asking you to modify code to make the program work
- **Lab5 Logisim**: ~ build logic gates and practise with combinational logic
- **Lab7 Caches**: back to RISC-V, implement and optimize matrix-related functions to understand how cache works. This lab is valuable as it touches on one way to squeeze out performance.
- **Lab8 OS, I/O, DMA, Disks, Networking & Virtual Memory**: ~ play with a virtual memory simulator to understand how it works
- **Lab9 SIMD Instructions**: ~ work on single instruction multiple data (SIMD) -- write C functions and improve their performance with x86 intrinsics. It's like inserting assembly code into C code. (Note that ARM users unfortunately would have to use ARM NEON intrin to be able to compile the programs.)
- **Lab10 Thread Level Parallelism**: have you experience parallel programing with C + OpenMP. Ask you to apply parallelism to the implementation of sum vector and dot product C funcs.

## Progress

Planned to complete the course within 30 study days, and achieved the goal!

- [x] 【0611】setup, lab00
- [x] 【0615】lec1&2
- [x] 【0616】lec3
- [x] 【0617】lec4
- [x] 【0625】lec5, lab01
- [x] 【0626】lec6
- [x] 【0627】proj1A
- [x] 【0702/03】proj1 Fin
- [x] 【0704】K&Rch1-2
- [x] 【0705】lec7+8.1, lab2
- [x] 【0706】disc2
- [x] 【0715】lec8-10
- [x] 【0716】lab3
- [x] 【0719】disc3, disc4
- [x] 【0724】proj2 partA 50%
- [x] 【0725】proj2 partA fin
- [x] 【0801】lec11-13
- [x] 【0802】disc5, lab4, lec14-15
- [x] 【0803】lecs16+SDS State Logic handouts, lec17
- [x] 【0804】lab5, lec 18-19
- [x] 【0805】lec20-27 (fin CPU Pipelining Caches), disc6-8
- [x] 【0806】disc9, lab7, lec28-2931 (fin OS VMi)
- [x] 【0807】lec30-31(VMii I/O), disc10, lab8, disc11
- [x] 【0808】lec32-35 (SIMD/MIMD, Parallelism), lec36-38 (MapReduce, WSC, RAID)
- [x] 【0809】disc12, lab9, lab10, disc13-14
- 【skipped due to compatibility probs】proj4, proj3, lab6,  lab11

## Postscript

should've been preparing for the incoming semester, projects and stuff but couldn't resist the temptation of learning how computer works :>