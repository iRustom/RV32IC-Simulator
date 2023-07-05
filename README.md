# Computer Organization and Assembly Language - Project I - RV32IC-Simulator
## How to Build and Use The Simulator

## Project Members:
- Ahmed Ali
- Omar Elfouly
- Bavly Labieb

## Contribution
Issues were created for every task that each member was responsible for. In general, each member contributed to all parts of the code, where a group of instructions was assigned to each member to complete, whether to decompress, decode, or execute.

## Simulator design

Our code mainly used the following functions:
### instDecExec:
The 32-bit instruction word was passed to this function. All relevant word fields are extracted and used to differentiate instructions; then, the instruction is printed in the correct format. A function is called for each instruction to execute its functionality on the registers/memory.

### decompress:
The compressed instruction word is passed to this function; a conditional statement is used to check whether a given function is compressed based on the first 2 bits of the instruction to be extracted. 
If the instruction word is compressed, then it's passed to the decompress function, where it is converted to its 32-bit instruction equivalent. 

## Challenges we faced
