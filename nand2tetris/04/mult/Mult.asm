// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.

// i=0
@i
M=0

// sum=0
@R2
M=0

// go to end if RAM[0] == 0
@R0
D=M
@END
D;JEQ


(LOOP)

// if (i - RAM[1] <= 0) goto END
@R1
D=M
@i
D=D-M
@END
D;JLE

// sum = sum + M[0]
@R2
D=M
@R0
D=D+M
@R2
M=D

// i = i + 1
@i
D=M+1
M=D

@LOOP
0;JEQ

(END)
@END
0;JEQ