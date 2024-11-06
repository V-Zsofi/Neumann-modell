## Table of Contents
- [1 User Interaction](#1-user-interaction)
- [2 Program Input](#2-program-input)
- [3 Possible Instructions](#3-possible-instructions)

## 1 User Interaction
The user interacts with the computer via the terminal (cout/cin). At startup, the computer requests a text file from the user that contains the instructions to be executed. The text file should be placed in the `Neumann_modell\input` directory.

## 2 Program Input
The input file lines contain the instructions and their memory addresses. The first line specifies the memory size. Example program code with 1000 memory capacity that calculates the value of 1 + 2 and outputs it to cout:
 
ADDR &nbsp;&nbsp;&emsp;INSTR &emsp;OPERAND&emsp;&emsp;(This line is not needed in the txt file)  
0x1000  
0x0000 &emsp;LOAD &nbsp;&emsp;0x0101  
0x0001  &emsp;ADD &nbsp;&ensp;&emsp;0x0102  
0x0002  &emsp;STORE &emsp;0x0103  
0x0003  &emsp;PRINT&emsp;&ensp;0x0103  
0x0101  &emsp;VAR     &emsp;&emsp;0x0001  
0x0102  &emsp;VAR     &emsp;&emsp;0x0002  
 
The computer initializes its memory with the contents of the file and begins program execution.
## 3 Possible Instructions
The computer starts execution from memory address 0x0000. The following instructions are possible:

- **LOAD OPERAND** -> Loads the variable at the OPERAND address into the ACC register.
- **STORE OPERAND** -> Saves the content of the ACC register to the OPERAND address as a variable.
- **ADD OPERAND** -> Adds the value at the OPERAND address to the value in the ACC register.
- **SUB OPERAND** -> Subtracts the value at the OPERAND address from the value in the ACC register.
- **READ OPERAND** -> Reads a number from the input (std::cin) and stores it as a variable at the OPERAND address.
- **PRINT OPERAND** -> Prints the variable at the OPERAND address to the output (std::cout).
- **BRANCHGT OPERAND** -> The next instruction address changes to OPERAND if ACC > 0.
- **JUMP OPERAND** -> The next instruction address changes to OPERAND.