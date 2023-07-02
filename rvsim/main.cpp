/*
	TO DO:
	Decompress RVC instructions
	Execute
	Read data section

	References:
	(1) The risc-v ISA Manual ver. 2.1 @ https://riscv.org/specifications/
	(2) https://github.com/michaeljclark/riscv-meta/blob/master/meta/opcodes
*/

#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <iomanip>
#include <cstring> //for memset

using namespace std;

// data structure for registers

class regfile {

  struct bit32 {
    unsigned int value;
    bool is_const;

    template <typename T>
    unsigned int operator=(T x) {
      if (!is_const) {
        value = x;
      }
      return value;
    }

    friend ostream &operator<<(ostream &os, const bit32 &reg) {
      os << reg.value;
      return os;
    }
  };

  bit32 arr[32];
public:
  bit32 &operator[](int index) {
    return arr[index];
  }

  regfile() {
    memset(arr, 0, sizeof(arr));
    arr[0].is_const = 1;
  }

};
// initialise via rv registers; all regs would be 0

unsigned int pc;
unsigned char memory[(16 + 64) * 1024];
regfile x;

void emitError(const char* s)
{
	cout << s;
	exit(0);
}

void printPrefix(unsigned int instA, unsigned int instW) {
	cout << "0x" << hex << setfill('0') << setw(8) << instA << "\t0x" << setw(8) << instW;
}

void instDecExec(unsigned int instWord)
{
	unsigned int rd, rs1, rs2, funct3, funct7, opcode;
	unsigned int I_imm, S_imm, B_imm, U_imm, J_imm;
	unsigned int address;

	unsigned int instPC = pc - 4;

	opcode = instWord & 0x0000007F;
	rd = (instWord >> 7) & 0x0000001F;
	funct3 = (instWord >> 12) & 0x00000007;
	rs1 = (instWord >> 15) & 0x0000001F;
	rs2 = (instWord >> 20) & 0x0000001F;
	funct7 = (instWord >> 25) & 0x0000007F;

	// â€” inst[31] â€” inst[30:25] inst[24:21] inst[20]
	I_imm = ((instWord >> 20) & 0x7FF) | (((instWord >> 31) ? 0xFFFFF800 : 0x0));
	B_imm = (rd & 0b11110) | ((funct7 & 0b0111111) << 5) | ((rd & 0b00001) << 11) | ((funct7 & 0b1000000) << 6);
	S_imm = ((funct7 <<5) | rd) | (((instWord >> 31) ? 0xFFFFF800 : 0x0));
	U_imm = (instWord & 0xFFFFF000);
	J_imm = (((instWord>>21)&0x3FF)<<1) | (((instWord>>20)&0x1)<<11) | (((instWord>>12)&0xFF)<<12) | ((instWord>>31)?0xFFF80000:0x0);

	printPrefix(instPC, instWord);

	if (opcode == 0x33) {		// R Instructions
		switch (funct3) {
		case 0: if (funct7 == 32) {
			cout << "\tSUB\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";	//added "dec" to output rd, rs1, and rs2 as decimal
		}
			  else {
			cout << "\tADD\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
		}
			  break;

		case 1: cout << "\tSLL\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			break;

		case 2: cout << "\tSLT\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			break;

		case 3: cout << "\tSLTU\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			break;

		case 4: cout << "\tXOR\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			break;

		case 5: if (funct7 == 32) {
			cout << "\tSRA\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
		}
			  else {
			cout << "\tSRL\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
		}
			  break;

		case 6: cout << "\tOR\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			break;

		case 7: cout << "\tAND\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			break;

		default:
			cout << "\tUnkown R Instruction \n";
		}
	}
	else if (opcode == 0x13) {	// I instructions
		switch (funct3) {
		case 0:	cout << "\tADDI\tx" << dec << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";	//added "dec" to output rd and rs1 as decimal
			break;

		case 1:	cout << "\tSLLI\tx" << dec << rd << ", x" << rs1 << ", " << hex << "0x" << ((unsigned int)I_imm & 0x01F) << "\n";
			break;

		case 2:	cout << "\tSLTI\tx" << dec << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;

		case 3:	cout << "\tSLTIU\tx" << dec << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;

		case 4:	cout << "\tXORI\tx" << dec << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;

		case 5: if (funct7 == 32) {
			cout << "\tSRAI\tx" << dec << rd << ", x" << rs1 << ", " << hex << "0x" << ((unsigned int)I_imm & 0x01F) << "\n";
		}
			  else {
			cout << "\tSRLI\tx" << dec << rd << ", x" << rs1 << ", " << hex << "0x" << ((unsigned int)I_imm & 0x01F) << "\n";
		}
			  break;

		case 6: cout << "\tORI\tx" << dec << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;

		case 7: cout << "\tANDI\tx" << dec << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			break;

		default:
			cout << "\tUnkown I Instruction \n";
		}
	}
	else if(opcode == 0x3) {	// I-type load instructions
		switch (funct3) {
		case 0: cout << "\tLB\tx" << dec << rd << ", " << (int)I_imm << "(x" << rs1 << ")\n";	//added "dec" to output rd, rs1, and the offset as decimal
			break;

		case 1: cout << "\tLH\tx" << dec << rd << ", " << (int)I_imm << "(x" << rs1 << ")\n";
			break;

		case 2: cout << "\tLW\tx" << dec << rd << ", " << (int)I_imm << "(x" << rs1 << ")\n";
			break;

		case 4: cout << "\tLBU\tx" << dec << rd << ", " << (int)I_imm << "(x" << rs1 << ")\n";
			break;

		case 5: cout << "\tLHU\tx" << dec << rd << ", " << (int)I_imm << "(x" << rs1 << ")\n";
			break;

		default:
			cout << "\tUnkown I Instruction \n";
		}
	}
	else if (opcode == 0x23) {	//S-type
		// rd is now imm[4:0]
		// funct7 is now imm[11:5]
		switch(funct3){
			case 0: cout << "\tSB\tx" << dec << rs2 << ", " << (int)S_imm << "(x" << dec << rs1 <<")\n";
				break;
			case 1: cout << "\tSH\tx" << dec << rs2 << ", " << (int)S_imm << "(x" << dec << rs1 <<")\n";
				break;
			case 2: cout << "\tSW\tx" << dec << rs2 << ", " << (int)S_imm << "(x" << dec << rs1 <<")\n";
				break;
			default: cout << "\tUnkown S Instruction \n";
		}
	}
	else if (opcode == 0x63) {	//B-type
	switch (funct3) {
	case 0: cout << "\tBEQ\tx" << dec << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)B_imm << "\n";
		break;
	case 1: cout << "\tBNE\tx" << dec << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)B_imm << "\n";
		break;
	case 4: cout << "\tBLT\tx" << dec << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)B_imm << "\n";
		break;
	case 5: cout << "\tBGE\tx" << dec << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)B_imm << "\n";
		break;
	case 6:cout << "\tBLTU\tx" << dec << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)B_imm << "\n";
		break;
	case 7: cout << "\tBGEU\tx" << dec << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)B_imm << "\n";
		break;
	default:
		cout << "\tUnkown B Instruction \n";
		}
	}
	else if (opcode == 0x17) {	//U-type (AUIPC)
		cout << "\tAUIPC\tx" << dec << rd << ", " << hex << "0x" << ((int)U_imm >> 12) << "\n";
	}
	else if (opcode == 0x37) {	//U-type (LUI)
		cout << "\tLUI\tx" << dec << rd << ", " << hex << "0x" << ((int)U_imm >> 12) << "\n";
	}
	else if (opcode == 0x6F) {	//J-type (JAL)
		cout << "\tJAL\tx" << dec << rd << ", " << hex << "0x" << (int)J_imm << "\n";
	}
	else if (opcode == 0x67) {	//I-type (JALR)
		cout << "\tJALR\tx" << dec << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
	}
	else if (opcode == 0x73) {	//(ECALL)
			cout << "\tECALL\n";
	}
	else {
		cout << "\tUnkown Instruction \n";
	}
}

// function to decompress compressed instructions into 32 bit instructions
unsigned int decompress(unsigned int instWord) {
	// if opcode
	// switch funct 3
	unsigned int opcode = instWord & 0b11;
	unsigned int funct3 = (instWord & 0xE000)>>13;
	if(opcode == 0){
		switch(funct3){
			case 0b000:
				// C.ADDI4SPN
				break;
			case 0b010:
				// C.LW
				break;
			case 0b110:
				// C.SW
				break;
			default:
				cout << "\tUnkown Compressed Instruction \n";
		}
	}else if(opcode == 1){
		switch(funct3){
			case 0b000:
				// C.NOP
				// C.ADDI
				break;
			case 0b001:
				// C.JAL
				break;
			case 0b010:
				// C.LI
				break;
			case 0b011:
				// C.ADDI16SP
				// C.LUI
				break;
			case 0b100:
				// C.SRLI
				// C.SRAI
				// C.ANDI
				// C.SUB
				// C.XOR
				// C.OR
				// C.AND
				break;
			case 0b101:
				// C.J
				break;
			case 0b110:
				// C.BEQZ
				// beq rs1', x0, offset
				unsigned int inst32 = 0;
				inst32 |= 0b1100011; //opcode for beq
				inst32 |= (0b000<<12); // funct3 for beq, technically unrequired but kept for clarity
				inst32 |= (0b00000<<7); // rs1 for beq, technically unrequired but kept for clarity
				inst32 |= (0b00000<<20); // rs2 for beq, technically unrequired but kept for clarity


				break;
			case 0b111:
				// C.BNEZ
				break;
			default:
				cout << "\tUnkown Compressed Instruction \n";
		}
	}else if(opcode == 2){
		switch(funct3){
			case 0b000:
				// C.SLLI
				break;
			case 0b010:
				// C.LWSP
				break;
			case 0b100:
				// C.JR
				// C.MV
				// C.JALR
				// C.ADD
				break;
			case 0b110:
				// C.SWSP
				break;
			default:
				cout << "\tUnkown Compressed Instruction \n";
		}
	}
	else {
		cout << "\tUnkown Compressed Instruction \n";
	}

	return instWord;
}

	

int main(int argc, char* argv[]) {

	//unsigned int instWord = 0;
	ifstream inFile;
	ofstream outFile;

	unsigned int instWord = 0b00000001100001001000010001100111;
	instDecExec(instWord);

	if (argc !=2) emitError("use: rvsim <machine_code_file_name>\n");

	inFile.open(argv[1], ios::in | ios::binary | ios::ate);

	if (inFile.is_open())
	{
		int fsize = inFile.tellg();

		inFile.seekg(0, inFile.beg);
		if (!inFile.read((char*)memory, fsize)) emitError("Cannot read from input file\n");

		while (true) {
			// condition to check if it is compressed instruction
			if ((memory[pc] & 0b11) == 0b11) {
				instWord = (unsigned char)memory[pc] |
					(((unsigned char)memory[pc + 1]) << 8) |
					(((unsigned char)memory[pc + 2]) << 16) |
					(((unsigned char)memory[pc + 3]) << 24);
				pc += 4;
			}
			else {
				instWord = (unsigned char)memory[pc] |
					(((unsigned char)memory[pc + 1]) << 8);
				// instword = decompress(instWord);
				pc += 2;
			}

			/* removed to allow for compressed instructions
			instWord = (unsigned char)memory[pc] |
				(((unsigned char)memory[pc + 1]) << 8) |
				(((unsigned char)memory[pc + 2]) << 16) |
				(((unsigned char)memory[pc + 3]) << 24);
			pc += 4;*/

			// remove the following line once you have a complete simulator
			if (pc == 32) break;			// stop when PC reached address 32
			instDecExec(instWord);
		}
	}
	else emitError("Cannot access input file\n");
}
