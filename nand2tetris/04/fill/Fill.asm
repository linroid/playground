// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

(LOOP)
@KBD
D=M

// if keyboard > 0 jump to black
@BLACK
D;JGT

(WHITE)
@color
M=0
@DRAW
0;JEQ

(BLACK)
@color
M=-1

(DRAW)
@SCREEN
D=A
@coord
M=D
@i
M=0

(PIXEL)
// coord = SCREEN[i]
@i
D=M
@SCREEN
D=A+D
@coord
M=D

// SCREEN[coord] = color
@color
D=M
@coord
A=M
M=D

// i = i+1
@i
M=M+1

// if (8192-i == 0), end draw
@8192
D=A
@i
D=D-M
@LOOP
D;JEQ

@LOOP
D;JEQ


// draw next pixel
@PIXEL
0;JEQ
