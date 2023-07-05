# Computer Organization and Assembly Language - Project I - RV32IC-Simulator
## How to Build and Use The Simulator

## Project Members:
- Ahmed Ali
- Omar Elfouly
- Bavly Labieb

## Contribution

## Simulator design

Our code mainly used the following functions:
### instDecExec:
The 32-bit instruction word was passed to this function. All relevant word fields are extracted and used to differentiate instructions; then, the instruction is printed in the correct format. A function is called for each instruction to execute its functionality on the registers/memory.

### decompress:
The compressed instruction word is passed to this function; a conditional statement is used to check whether a given function is compressed based on the first 2 bits of the instruction to be extracted. 
If the instruction word is compressed, then it's passed to the decompress function, where it is converted to its 32-bit instruction equivalent. 

## Challenges we faced
