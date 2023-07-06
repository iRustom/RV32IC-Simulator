# Computer Organization and Assembly Language - Project I - RV32IC-Simulator
## How to Build Simulator
Clone the repo onto your device, then, compile rvsim.cpp into an executable.
On linux this would mean running the following commands while in the cloned repositories directory:
```
make rvsim
chmod o+rx rvsim
```
This will create an executable named rvsim and give the executable the necessary permissions.

If you wish to be able to run rvsim commands without a path to rvsim then run the following commands while in the cloned repoistory where rvsim executable was made:
```
sudo mv rvsim /usr/local/bin/rvsim
```

## How to Use Simulator

Using command line pass the two files containing the text and data section to rvsim. 
use: rvsim <machine_code_file_name> <data_file_name>, where data file is optional

A comman mistake is forgetting to include the path to each file when your current directory is different than the directory of the files you want to give to rvsim.

## Project Members:
- Ahmed Ali
- Omar Elfouly
- Bavly Labieb

## Contribution
Issues were created for every task that each member was responsible for. In general, each member contributed to all parts of the code, where a group of instructions was assigned to each member to complete, whether to decompress, decode, or execute.

## Simulator design
Our code mainly used the following functions:

#### instDecExec:
The 32-bit instruction word was passed to this function. All relevant word fields are extracted and used to differentiate instructions, then, the instruction is printed in the correct format. A function is called for each instruction to execute its functionality on the registers/memory. In more detail, the function extracts parts of the instruction word to identify the type and which exact function it is; a series of if and case statements are used to decode the instruction word to figure out which specific instruction to execute. When a particular instruction is decoded, it is printed out using the correct mnemonics, registers, and immediate values in hex. These parameters are also passed to a function specific to the instruction, which performs the execution.

#### decompress:
The compressed instruction word is passed to this function. A conditional statement is used to check whether a given function is compressed based on the first 2 bits of the instruction to be extracted. If the instruction word is compressed, then it's passed to the decompress function, where it is converted to its 32-bit instruction equivalent. 

### Main Flow
Our main code opens the files provided through the command line arguments. The memory is then initialized with the data and text sections using the data and text files, then, we start the "fetch" process by fetching two bytes from the text section of the memory. The first 2 bits of the first byte are used to differentiate between compressed and uncompressed instructions and, based on that, we know whether or not to extract two more bytes to fetch the whole instruction. If the instruction is compressed, it is passed to the decompress function to get the 32-bit instruction passed to instDecExec, which decodes and executes the instruction. 

## Challenges we Faced
Debugging some test cases was a tedious task because we had to make sure each instruction does what it was supposed to do, especially when the number of dynamic instructions in some test cases was relatively large, but we eventually ironed out any bugs that were present in the code.

## How we tested

To test each instruction the following website and code were used:

- https://luplab.gitlab.io/rvcodecjs/ : website to assemble individual instructions
  
- Code for testing compressed instructions:

  ```
	unsigned int compressedInsttructionWord = <compressed instruction word from website>;
	string compressedInstructionString = "";
	unsigned int decompressedInstructionWord = decompress(compressedInsttructionWord, compressedInstructionString);
	instDecExec(decompressedInstructionWord, compressedInstruction);
  ```
- Code for testing uncompressed instructions:

  ```
	unsigned int uncompressedInsttructionWord = <uncompressed instruction word from website>;
	instDecExec(uncompressedInsttructionWord, "");
  ```

## Issues with program

Currently, there are no known issues with our program.

## Issues with test cases

Currently, t4 and t5 will not run correctly for the following reasons:
- t4.asm initialises the sp to an adress in data, whcih eventually leads to both data being lost and items saved by stack pointer (such as ra) being lost. This is why the output of the string print is programmis awesome and is also the reason why Jalr zero, ra, 0 fails due to ra's value being lost when data section is written to.
- t5-d.bin is empty which means the program is missing the data necessary to run correctly
