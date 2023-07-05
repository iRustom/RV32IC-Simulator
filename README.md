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
#### instDecExec:
The 32-bit instruction word was passed to this function. All relevant word fields are extracted and used to differentiate instructions; then, the instruction is printed in the correct format. A function is called for each instruction to execute its functionality on the registers/memory. In more detail, the function extracts parts of the instruction word to identify the type and which exact function it is; a series of if and case statements are used to decode the instruction word to figure out which specific instruction to execute. When a particular instruction is decoded, it is printed out using the correct mnemonics, registers, and immediate values in hex; these parameters are also passed to a function specific to that instruction that executes it.

#### decompress:
The compressed instruction word is passed to this function; a conditional statement is used to check whether a given function is compressed based on the first 2 bits of the instruction to be extracted. 
If the instruction word is compressed, then it's passed to the decompress function, where it is converted to its 32-bit instruction equivalent. 

### Main Flow
Our main code opens the files given through the command line arguments. The memory is then initialized with the data and text sections 
using the data and text files; then, we start the "fetch" process by fetching a byte from the text section of the memory. The first 2 bits of the first byte are used to differentiate compressed instructions and, based on that, know whether only to extract one or three more bytes to fetch the whole instruction. If the Instruction is compressed, it is passed to the decompress function to get the 32-bit instruction passed to instDecExec, which decodes and executes the instruction. 

## Challenges we faced
