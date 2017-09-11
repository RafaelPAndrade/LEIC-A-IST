# IAC README #

## Information about IAC - P3 Manual ##

In IAC (Introduction to Computer Architeture), we learned Assembly.
However, it was not x86, nor RISC-V, nor Arm assembly. It was 16-bit
assembly on what was the implementation of a CPU as described in the
class book (that unfortunately is not readily available in pdf format,
because it is actively sold). In this commit, I add the quick guide
that guided us during the project, containing everything needed to
write assembly for this specific class; unfortunately, it is also in
portuguese.

Following is a brief summary about the P3, based on the documentation
and on what I still remember.

====

The board, sporting a 16-bit CPU, is known as P3. P3 has 16 registers,
but only 8 are for general use (from R0 to R7). Due to a quirk of the
processor, R0 as always the value 0, and nothing can be stored; it has
also a Program Counter (PC), Stack Pointer (SP) and State Register(RE)
that keeps the flags, which are:

-	O: overflow
-	N: negative
-	C: carry
-	Z: zero
-	E: enable interrupts

This flags can be changed by certain instructions; and they were then
used in conditional branches/jumps/calls.

P3 can address a whopping 64k words in memory (16 bit addresses), and
each word is 16 bit long (16-bit CPU, duh!).

I/O is memory mapped, between FFF0h and FFFFh. These correspond to:

-	FFF0-3h: 7-segment display,

-	FFF4-5h: LCD display, size: 16x2 characters; 4 controls 
	the cursor, 5 controls the character to write

-	FFF6-7h: Timer; 6 controls the value between interrupts 
	(in 100ms), 7 controls the timer

-	FFF8h: 16 independent led lights, ranging from red to green

-	FFF9h: 8 independent switches (8 bits storing the state)

-	FFFAh: interrupt mask; enables each of the 15 keys in the
	keypad and the timer (highest bit)

-	FFFBh: ???? (I can't find information about this one)

-	FFFC-Fh:  VGA/DVI(?) port, with a fixed size of 80x24;

	-	C:  Controls the position of the cursor
	-	D:  Flags if any key was pressed
	-	E:  Controls the character to write
	-	F:  Stores the last pressed button


In this class. we wrote assembly that would then be passed to the
assembler present in IAC/scripts_apoio/p3as-linux.zip. Then, we could
run the code in the simulator, IAC/scripts_apoio/p3sim.jar; or load
it to the board.

The assembler supported more than 30 different instructions, including
multiplication and division.


## Project ##
  
This version has:

-	a program flow schematic (fluxo_rtype_g10.pdf)

-	a report on the development/ main architecture ideas
	(Relatorio_rtype_g10.pdf)

-	a "nicely" formatted pdf version of the code (Rtype_p3print_g10.pdf)
    
The final grade on this project was around 18.5/19.
