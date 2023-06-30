/*
	This is just a skeleton. It DOES NOT implement all the requirements.
	It only recognizes the RV32I "ADD", "SUB" and "ADDI" instructions only.
	It prints "Unkown Instruction" for all other instructions!

	References:
	(1) The risc-v ISA Manual ver. 2.1 @ https://riscv.org/specifications/
	(2) https://github.com/michaeljclark/riscv-meta/blob/master/meta/opcodes
*/

#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <iomanip>

using namespace std;

unsigned int pc;
unsigned char memory[(16 + 64) * 1024];

void emitError(const char* s)
{
	cout << s;
	exit(0);
}

void printPrefix(unsigned int instA, unsigned int instW) {
	cout << "0x" << hex << std::setfill('0') << std::setw(8) << instA << "\t0x" << std::setw(8) << instW;
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
	S_imm = ((funct7 <<5) | rd) | (((instWord >> 31) ? 0xFFFFF800 : 0x0));
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
			default: cout << "\tUnkown I Instruction \n";
		}
	}
	else if (opcode == 0x63) {	//B-type

	switch (funct3) {
	case 0: cout << "\tbeq\tx" << dec << rs1 << ", x" << rs1 << ", " << hex << "0x" << (int)B_imm << "\n";
			break;
		case 1: cout << "\tbne\tx" << dec << rs1 << ", x" << rs1 << ", " << hex << "0x" << (int)B_imm << "\n";
			break;
		case 4: cout << "\tblt\tx" << dec << rs1 << ", x" << rs1 << ", " << hex << "0x" << (int)B_imm << "\n";
			break;
		case 5: cout << "\tbge\tx" << dec << rs1 << ", x" << rs1 << ", " << hex << "0x" << (int)B_imm << "\n";
			break;
		case 6:cout << "\tbltu\tx" << dec << rs1 << ", x" << rs1 << ", " << hex << "0x" << (int)B_imm << "\n";
			break;
		case 7: cout << "\tbgeu\tx" << dec << rs1 << ", x" << rs1 << ", " << hex << "0x" << (int)B_imm << "\n";
			break;
	}

	}
	
	else if (opcode == 0x6F) {	//J-type
		// only jal
		cout << "\tjal\tx" << dec << rd << ", " << hex << "0x" << (int)J_imm << "\n";

	}
	/*else if (opcode == 0x17) {	//U-type (AUIPC)

	}
	else if (opcode == 0x37) {	//U-type (LUI)

	}
	else if (opcode == 0x67) {	//I-type (JALR)

	}*/
	else {
		cout << "\tUnkown Instruction \n";
	}
}

int main(int argc, char* argv[]) {

	unsigned int instWord = 0;
	ifstream inFile;
	ofstream outFile;

	if (argc !=2) emitError("use: rvsim <machine_code_file_name>\n");

	inFile.open(argv[1], ios::in | ios::binary | ios::ate);

	if (inFile.is_open())
	{
		int fsize = inFile.tellg();

		inFile.seekg(0, inFile.beg);
		if (!inFile.read((char*)memory, fsize)) emitError("Cannot read from input file\n");

		while (true) {
			instWord = (unsigned char)memory[pc] |
				(((unsigned char)memory[pc + 1]) << 8) |
				(((unsigned char)memory[pc + 2]) << 16) |
				(((unsigned char)memory[pc + 3]) << 24);
			pc += 4;
			// remove the following line once you have a complete simulator
			if (pc == 32) break;			// stop when PC reached address 32
			instDecExec(instWord);
		}
	}
	else emitError("Cannot access input file\n");
}
