/*
	TO DO:
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

		friend ostream& operator<<(ostream& os, const bit32& reg) {
			os << reg.value;
			return os;
		}
	};

	bit32 arr[32];
public:
	bit32& operator[](int index) {
		return arr[index];
	}

	regfile() {
		memset(arr, 0, sizeof(arr));
		arr[0].is_const = 1;
	}

};
// initialise via regfile registers; all regs would be 0

unsigned int pc;
unsigned int nextPC;
unsigned char memory[(16 + 64) * 1024];
regfile x;

void emitError(const char* s)
{
	cout << s;
	exit(1);
}

void printPrefix(unsigned int instA, unsigned int instW) {
	cout << "0x" << hex << setfill('0') << setw(8) << instA << "\t0x" << setw(8) << instW;
}

void ADD(unsigned int rd, unsigned int rs1, unsigned int rs2)
{
	x[rd] = x[rs1].value + x[rs2].value; 
	
}
void SUB(unsigned int rd, unsigned int rs1, unsigned int rs2)
{
	x[rd] = x[rs1].value - x[rs2].value;
	

}
void XOR(unsigned int rd, unsigned int rs1, unsigned int rs2)
{
	x[rd] = x[rs1].value ^ x[rs2].value;
}
void OR(unsigned int rd, unsigned int rs1, unsigned int rs2)
{
	x[rd] = x[rs1].value | x[rs2].value;
	
}
void AND(unsigned int rd, unsigned int rs1, unsigned int rs2)
{
	x[rd] = x[rs1].value & x[rs2].value;
	
}

void SLL(unsigned int rd, unsigned int rs1, unsigned int rs2)
{
	x[rd] = x[rs1].value << x[rs2].value;
}

void SRL(unsigned int rd, unsigned int rs1, unsigned int rs2)
{
	x[rd] = x[rs1].value >> x[rs2].value;
}

void SRA(unsigned int rd, unsigned int rs1, unsigned int rs2)
{
	x[rd] = (signed int) x[rs1].value >> x[rs2].value;
}
void SLT(unsigned int rd, unsigned int rs1, unsigned int rs2)
{
	x[rd] = ((signed int)x[rs1].value < (signed int)x[rs2].value) ? 1:0;
}
void SLTU(unsigned int rd, unsigned int rs1, unsigned int rs2)
{
	x[rd] = (x[rs1].value < x[rs2].value) ? 1 : 0;
}
void ADDI(unsigned int rd, unsigned int rs1, unsigned int imm)
{
	x[rd] = x[rs1].value + imm;
}
void XORI(unsigned int rd, unsigned int rs1, unsigned int imm)
{
	x[rd] = x[rs1].value ^ imm;
}
void ORI(unsigned int rd, unsigned int rs1, unsigned int imm)
{
	x[rd] = x[rs1].value | imm;
}

// execute Set B
// ANDI
void ANDI(unsigned int rd, unsigned int rs1, unsigned int imm){
	x[rd] = x[rs1].value & imm;
}
// SLLI
void SLLI(unsigned int rd, unsigned int rs1, unsigned int imm){
	x[rd] = x[rs1].value << imm;
}
// SRLI
void SRLI(unsigned int rd, unsigned int rs1, unsigned int imm){
	x[rd] = x[rs1].value >> imm;
}
// SRAI
void SRAI(unsigned int rd, unsigned int rs1, unsigned int imm){
	x[rd] = (signed int)x[rs1].value >> imm;
}
// SLTI
void SLTI(unsigned int rd, unsigned int rs1, unsigned int imm){
	x[rd] = ((signed int)x[rs1].value < (signed int)imm) ? 1 : 0;
}
// SLTIU
void SLTIU(unsigned int rd, unsigned int rs1, unsigned int imm){
	x[rd] = (x[rs1].value < imm) ? 1 : 0;
}
// LB
void LB(unsigned int rd, unsigned int rs1, unsigned int imm){
	x[rd] = memory[x[rs1].value + (int)imm];
	// sign extend to 32 bits
	if(x[rd].value & 0b10000000){
		x[rd].value |= 0xFFFFFF00;
	}
}
// LH
void LH(unsigned int rd, unsigned int rs1, unsigned int imm){
	x[rd] = memory[x[rs1].value + (int)imm];
	// load second byte
	x[rd].value |= memory[x[rs1].value + (int)imm + 1] << 8;
	// sign extend to 32 bits
	if(x[rd].value & 0b1000000000000000){
		x[rd].value |= 0xFFFF0000;
	}
}
// LW
void LW(unsigned int rd, unsigned int rs1, unsigned int imm){
	x[rd] = memory[x[rs1].value + (int)imm];
	// load second byte
	x[rd].value |= memory[x[rs1].value + (int)imm + 1] << 8;
	// load third byte
	x[rd].value |= memory[x[rs1].value + (int)imm + 2] << 16;
	// load fourth byte
	x[rd].value |= memory[x[rs1].value + (int)imm + 3] << 24;
}
// LBU
void LBU(unsigned int rd, unsigned int rs1, unsigned int imm){
	x[rd] = memory[x[rs1].value + (int)imm];
}
// LHU
void LHU(unsigned int rd, unsigned int rs1, unsigned int imm){
	x[rd] = memory[x[rs1].value + (int)imm];
	// load second byte
	x[rd].value |= memory[x[rs1].value + (int)imm + 1] << 8;
}

void SB(unsigned int rs2, unsigned int rs1, int S_imm) {
	unsigned int data = x[rs2].value;
	unsigned int base_address = x[rs1].value + S_imm;
	memory[base_address] = data & 0xFF;
}

void SH(unsigned int rs2, unsigned int rs1, int S_imm) {
	unsigned int data = x[rs2].value;
	unsigned int base_address = x[rs1].value + S_imm;
	memory[base_address] = data & 0xFF;
	memory[base_address + 1] = (data >> 8) & 0xFF;
}

void SW(unsigned int rs2, unsigned int rs1, int S_imm) {
	unsigned int data = x[rs2].value;
	unsigned int base_address = x[rs1].value + S_imm;
	memory[base_address] = data & 0xFF;
	memory[base_address + 1] = (data >> 8) & 0xFF;
	memory[base_address + 2] = (data >> 16) & 0xFF;
	memory[base_address + 3] = (data >> 24) & 0xFF;
}

void BEQ(unsigned int rs1, unsigned int rs2, int B_imm) {
	if (x[rs1].value == x[rs2].value) {
		nextPC = pc + B_imm;
	}
}

void BNE(unsigned int rs1, unsigned int rs2, int B_imm) {
	if (x[rs1].value != x[rs2].value) {
		nextPC = pc + B_imm;
	}
}

void BLT(unsigned int rs1, unsigned int rs2, int B_imm) {
	if ((int)(x[rs1].value) < (int)(x[rs2].value)) {
		nextPC = pc + B_imm;
	}
}

void BGE(unsigned int rs1, unsigned int rs2, int B_imm) {
	if ((int)(x[rs1].value) >= (int)(x[rs2].value)) {
		nextPC = pc + B_imm;
	}
}

void BLTU(unsigned int rs1, unsigned int rs2, int B_imm) {
	if (x[rs1].value < x[rs2].value) {
		nextPC = pc + B_imm;
	}
}

void BGEU(unsigned int rs1, unsigned int rs2, int B_imm) {
	if (x[rs1].value >= x[rs2].value) {
		nextPC = pc + B_imm;
	}
}

void AUIPC(unsigned int rd, int U_imm) {
	x[rd] = pc + U_imm;
}

void LUI(unsigned int rd, int U_imm) {
	x[rd] = U_imm;
}

void JAL(unsigned int rd, int J_imm) {
	x[rd] = nextPC;
	nextPC = pc + J_imm;
}

void JALR(unsigned int rd, unsigned int rs1, int I_imm) {
	x[rd] = nextPC;
	nextPC = (x[rs1].value + I_imm) & 0xFFFFFFFE;	/*"The target address is obtained by adding the sign - extended 12 - bit I - immediate
													to the register rs1, then setting the least - significant bit of the result to zero." from rv documentation*/
}

void ECALL() {
	switch (x[17].value) {
	case 1: cout << "Integer print: " << dec << (int)x[10].value << endl;
		break;
	case 4: {
		cout << "String print: ";
		unsigned int base_address = x[10].value;
		while (memory[base_address] != '\0') {
			cout << memory[base_address];
			base_address++;
		}
		cout << endl;
	}
		  break;
	case 10:{ cout << "Program exit(0)\n";
		exit(0);
		break;
	}
	default: emitError("Illegal ecall number\n");
	}
}

void instDecExec(unsigned int instWord)
{
	unsigned int rd, rs1, rs2, funct3, funct7, opcode;
	unsigned int I_imm, S_imm, B_imm, U_imm, J_imm;
	unsigned int address;

	unsigned int instPC = pc;

	opcode = instWord & 0x0000007F;
	rd = (instWord >> 7) & 0x0000001F;
	funct3 = (instWord >> 12) & 0x00000007;
	rs1 = (instWord >> 15) & 0x0000001F;
	rs2 = (instWord >> 20) & 0x0000001F;
	funct7 = (instWord >> 25) & 0x0000007F;

	// â€” inst[31] â€” inst[30:25] inst[24:21] inst[20]
	I_imm = ((instWord >> 20) & 0x7FF) | (((instWord >> 31) ? 0xFFFFF800 : 0x0));
	B_imm = (rd & 0b11110) | ((funct7 & 0b0111111) << 5) | ((rd & 0b00001) << 11) | ((funct7 & 0b1000000) << 6) | ((instWord >> 31) ? 0xFFFFF000 : 0x0);
	S_imm = ((funct7 <<5) | rd) | (((instWord >> 31) ? 0xFFFFF800 : 0x0));
	U_imm = (instWord & 0xFFFFF000);
	J_imm = (((instWord>>21)&0x3FF)<<1) | (((instWord>>20)&0x1)<<11) | (((instWord>>12)&0xFF)<<12) | ((instWord>>31)?0xFFF80000:0x0);

	printPrefix(instPC, instWord);

	if (opcode == 0x33) {		// R Instructions
		switch (funct3) {
		case 0: if (funct7 == 32) {
			cout << "\tSUB\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";	//added "dec" to output rd, rs1, and rs2 as decimal
			SUB(rd, rs1, rs2);
		}
			  else {
			cout << "\tADD\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			ADD(rd, rs1, rs2);
		}
			break;

		case 1: cout << "\tSLL\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			SLL(rd, rs1, rs2);
			break;

		case 2: cout << "\tSLT\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
				SLT(rd, rs1, rs2);
			break;

		case 3: cout << "\tSLTU\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
				SLTU(rd, rs1, rs2);
			break;

		case 4: cout << "\tXOR\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
				XOR(rd, rs1, rs2);
			break;

		case 5: if (funct7 == 32) {
			cout << "\tSRA\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			SRA(rd, rs1, rs2);
		}
			  else {
			cout << "\tSRL\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
			SRL(rd, rs1, rs2);
		}
			  break;

		case 6: cout << "\tOR\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
				OR(rd, rs1, rs2);
			break;

		case 7: cout << "\tAND\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
				AND(rd, rs1, rs2);
			break;

		default:
			cout << "\tUnkown R Instruction \n";
		}
	}
	else if (opcode == 0x13) {	// I instructions
		switch (funct3) {
		case 0:	cout << "\tADDI\tx" << dec << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";	//added "dec" to output rd and rs1 as decimal
			ADDI(rd, rs1, I_imm);
			break;

		case 1:	cout << "\tSLLI\tx" << dec << rd << ", x" << rs1 << ", " << hex << "0x" << ((unsigned int)I_imm & 0x01F) << "\n";
			SLLI(rd, rs1, I_imm&0x01F);
			break;

		case 2:	cout << "\tSLTI\tx" << dec << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			SLTI(rd, rs1, I_imm);
			break;

		case 3:	cout << "\tSLTIU\tx" << dec << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
			SLTIU(rd, rs1, I_imm);
			break;

		case 4:	cout << "\tXORI\tx" << dec << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
				XORI(rd, rs1, I_imm);
			break;

		case 5: if (funct7 == 32) {
			cout << "\tSRAI\tx" << dec << rd << ", x" << rs1 << ", " << hex << "0x" << ((unsigned int)I_imm & 0x01F) << "\n";
			SRAI(rd, rs1, I_imm&0x01F);
		}else {
			cout << "\tSRLI\tx" << dec << rd << ", x" << rs1 << ", " << hex << "0x" << ((unsigned int)I_imm & 0x01F) << "\n";
			SRLI(rd, rs1, I_imm&0x01F);
		}
			  break;

		case 6: cout << "\tORI\tx" << dec << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
				ORI(rd, rs1, I_imm);
			break;

		case 7: cout << "\tANDI\tx" << dec << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
				ANDI(rd, rs1, I_imm);
			break;

		default:
			cout << "\tUnkown I Instruction \n";
		}
	}
	else if(opcode == 0x3) {	// I-type load instructions
		switch (funct3) {
		case 0: cout << "\tLB\tx" << dec << rd << ", " << (int)I_imm << "(x" << rs1 << ")\n";	//added "dec" to output rd, rs1, and the offset as decimal
			LB(rd, rs1, I_imm);
			break;

		case 1: cout << "\tLH\tx" << dec << rd << ", " << (int)I_imm << "(x" << rs1 << ")\n";
			LH(rd, rs1, I_imm);
			break;

		case 2: cout << "\tLW\tx" << dec << rd << ", " << (int)I_imm << "(x" << rs1 << ")\n";
			LW(rd, rs1, I_imm);
			break;

		case 4: cout << "\tLBU\tx" << dec << rd << ", " << (int)I_imm << "(x" << rs1 << ")\n";
			LBU(rd, rs1, I_imm);
			break;

		case 5: cout << "\tLHU\tx" << dec << rd << ", " << (int)I_imm << "(x" << rs1 << ")\n";
			LHU(rd, rs1, I_imm);
			break;

		default:
			cout << "\tUnkown I Instruction \n";
		}
	}
	else if (opcode == 0x23) {	//S-type
		// rd is now imm[4:0]
		// funct7 is now imm[11:5]
		switch(funct3){
		case 0: {
			cout << "\tSB\tx" << dec << rs2 << ", " << (int)S_imm << "(x" << dec << rs1 << ")\n";
			SB(rs2, rs1, S_imm);
			}
			break;

		case 1: {
			cout << "\tSH\tx" << dec << rs2 << ", " << (int)S_imm << "(x" << dec << rs1 << ")\n";
			SH(rs2, rs1, S_imm);
			}
			break;

		case 2: {
			cout << "\tSW\tx" << dec << rs2 << ", " << (int)S_imm << "(x" << dec << rs1 << ")\n";
			SW(rs2, rs1, S_imm);
			}
			break;

			default: cout << "\tUnkown S Instruction \n";
		}
	}
	else if (opcode == 0x63) {	//B-type
	switch (funct3) {
	case 0: {
		cout << "\tBEQ\tx" << dec << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)B_imm << "\n";
		BEQ(rs1, rs2, B_imm);
	}
		break;
	case 1: {
		cout << "\tBNE\tx" << dec << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)B_imm << "\n";
		BNE(rs1, rs2, B_imm);
	}
		break;
	case 4: {
		cout << "\tBLT\tx" << dec << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)B_imm << "\n";
		BLT(rs1, rs2, B_imm);
	}
		break;
	case 5: {
		cout << "\tBGE\tx" << dec << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)B_imm << "\n";
		BGE(rs1, rs2, B_imm);
	}
		break;
	case 6: {
		cout << "\tBLTU\tx" << dec << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)B_imm << "\n";
		BLTU(rs1, rs2, B_imm);
	}
		break;
	case 7: {
		cout << "\tBGEU\tx" << dec << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)B_imm << "\n";
		BGEU(rs1, rs2, B_imm);
	}
		break;
	default:
		cout << "\tUnkown B Instruction \n";
		}
	}
	else if (opcode == 0x17) {	//U-type (AUIPC)
		cout << "\tAUIPC\tx" << dec << rd << ", " << hex << "0x" << ((int)U_imm >> 12) << "\n";
		AUIPC(rd, U_imm);
	}
	else if (opcode == 0x37) {	//U-type (LUI)
		cout << "\tLUI\tx" << dec << rd << ", " << hex << "0x" << ((int)U_imm >> 12) << "\n";
		LUI(rd, U_imm);
	}
	else if (opcode == 0x6F) {	//J-type (JAL)
		cout << "\tJAL\tx" << dec << rd << ", " << dec << (int)J_imm << "\n";
		JAL(rd, J_imm);
	}
	else if (opcode == 0x67) {	//I-type (JALR)
		cout << "\tJALR\tx" << dec << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << "\n";
		JALR(rd, rs1, I_imm);
	}
	else if (opcode == 0x73) {	//(ECALL)
		cout << "\tECALL\t";
		ECALL();
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


	unsigned int funct2 = (instWord & 0x0C00) >> 10;
	unsigned int funct6 = (instWord & 0xFC00) >> 10;
	unsigned int funct2AL = (instWord & 0x0060) >> 5;
	unsigned int funct4 = (instWord & 0xF000) >> 12;
	if(opcode == 0){
		switch(funct3){
			case 0b000:
			{
				// C.ADDI4SPN
				// addi rd ′, x2, nzuimm[9:2]
				unsigned int int32 = 0;
				unsigned int rd = ((instWord >> 2) & 0b111)+8;
				unsigned int nzuimm = 0 | (((instWord>>5)&0b1)<<3) | (((instWord>>6)&0b1)<<2) | (((instWord>>7)&0b1111)<<6) | (((instWord>>11)&0b11)<<4);
				int32 |= 0b0010011; //opcode for addi
				int32 |= (0b000<<12); // funct3 for addi, technically unrequired but kept for clarity
				int32 |= ((rd)<<7); // rd for addi
				int32 |= ((2)<<15); // rs1 for addi
				int32 |= ((nzuimm)<<20); // nzuimm for addi
				instWord=int32;
				break;
			}
			case 0b010: {
				// C.LW
				unsigned int rd_3bit = ((instWord >> 2) & 0b111) + 8;	//+8 to get x8-x15.
				unsigned int imm = (((instWord >> 6) & 0b1) | (((instWord >> 5) & 0b1) << 4) | (((instWord >> 10) & 0b111) << 1)) << 2;
				unsigned int rs1_3bit = ((instWord >> 7) & 0b111) + 8;
				instWord = 0b0000011 | (rd_3bit << 7) | (0b010 << 12) | (rs1_3bit << 15) | (imm << 20);
			
				break;
			}
			case 0b110: {
				// C.SW
				unsigned int rs2_3bit = ((instWord >> 2) & 0b111) + 8;	//+8 to get x8-x15.
				unsigned int imm = (((instWord >> 6) & 0b1) | (((instWord >> 5) & 0b1) << 4) | (((instWord >> 10) & 0b111) << 1)) << 2;
				unsigned int rs1_3bit = ((instWord >> 7) & 0b111) + 8;
				instWord = 0b0100011 | (rs2_3bit << 20) | (0b010 << 12) | (rs1_3bit << 15) | ((imm & 0b11111) << 7) | (((imm & 0b1100000) >> 5) << 25);
			
				break;
			}
			default:
				cout << "\tUnkown Compressed Instruction \n";
		}
	}else if(opcode == 1){
		switch(funct3){
			case 0b000:
			{
				// C.NOP
				// C.ADDI
				if(instWord==0b0000000000000001){
					// C.NOP
					instWord = 0b00000000000000000000000000010011;
				}else{
					// C.ADDI
					// addi rd, rd, imm[5:0]
					unsigned int inst32 = 0;
					unsigned int rd = (instWord >> 7) & 0b11111;
					unsigned int imm = 0 | ((instWord>>2)&0b11111) | ((instWord>>7)&0b100000);
					// sign extend imm to 12 bits using imm[5]
					if(imm & 0b100000){
						imm |= 0b111111000000;
					}
					inst32 |= 0b0010011; //opcode for addi
					inst32 |= (0b000<<12); // funct3 for addi, technically unrequired but kept for clarity
					inst32 |= ((rd)<<7); // rd for addi
					inst32 |= ((rd)<<15); // rs1 for addi
					inst32 |= ((imm)<<20); // imm for addi
					instWord=inst32;
				}
			
				break;
			}
			case 0b001: {
				// C.JAL
				unsigned int imm = (((instWord >> 3) & 0b111) | (((instWord >> 11) & 0b1) << 3) | (((instWord >> 2) & 0b1) << 4) | (((instWord >> 7) & 0b1) << 5) | (((instWord >> 6) & 0b1) << 6) | (((instWord >> 9) & 0b11) << 7) | (((instWord >> 8) & 0b1) << 9) | (((instWord >> 12) & 0b1) << 10)) << 1 | (((instWord >> 12) & 0b1) ? 0xFFFFF000 : 0x0);
				instWord = 0b1101111 | (0b00001 << 7) | (imm & 0xFF000) | (((imm >> 11) & 0b1) << 20) | (((imm >> 1) & 0b1111111111) << 21) | ((imm >> 20) & 0b1) << 31;
			
				break;
			}
			case 0b010:
			{
				// C.LI
				// addi rd,x0, imm[5:0]
				unsigned int inst32 = 0;
			 	unsigned int rd = (instWord >> 7) & 0b11111;
				unsigned int imm = 0 | ((instWord>>2)&0b11111) | ((instWord>>7)&0b100000);
				// sign extend imm to 12 bits using imm[5]
				if(imm & 0b100000){
					imm |= 0b111111000000;
				}
				inst32 |= 0b0010011; //opcode for addi
				inst32 |= (0b000<<12); // funct3 for addi, technically unrequired but kept for clarity
				inst32 |= ((rd)<<7); // rd for addi
				inst32 |= ((imm)<<20); // imm for addi
				instWord=inst32;
				break;
			}
			
			case 0b011:
			{
				// C.ADDI16SP
				// C.LUI
				// detect if bit 7 to 11 in instword is 2
				if(((instWord>>7)& 0b11111) == 2){
					// C.ADDI16SP
					// addi x2, x2, nzimm[9:4]
					unsigned int nzimm = 0 | (((instWord>>2)&0b1)<<5) | (((instWord>>3)&0b11)<<7) | (((instWord>>5)&0b1)<<6) | (((instWord>>6)&0b1)<<4) | (((instWord>>12)&0b1)<<9);
					// sign extend nzimm to 12 bits using nzimm[9]
					if(nzimm & 0b1000000000){
						nzimm |= 0b110000000000;
					}
					unsigned int rd = 2;
					unsigned int inst32 = 0;
					inst32 |= 0b0010011; //opcode for addi
					inst32 |= (0b000<<12); // funct3 for addi, technically unrequired but kept for clarity
					inst32 |= ((rd)<<7); // rd for addi
					inst32 |= ((rd)<<15); // rs1 for addi
					inst32 |= ((nzimm)<<20); // nzimm for addi
					instWord=inst32;
				}else{
					// C.LUI
					// lui rd, nzimm[17:12]
					unsigned int nzimm = 0 | (((instWord>>2)&0b11111)) | (((instWord>>12)&0b1)<<5);
					// sign extend nzimm to 20 bits using nzimm[5]
					if(nzimm & 0b100000){
						nzimm |= 0b111111111111111000000;
					}
					unsigned int rd = (instWord >> 7) & 0b11111;
					unsigned int inst32 = 0;
					inst32 |= 0b0110111; //opcode for lui
					inst32 |= ((rd)<<7); // rd for lui
					inst32 |= ((nzimm)<<12); // nzimm for lui
					instWord=inst32;
				}
				break;
			}
			case 0b100:
			{
				if (funct2 == 0b00)
				{
					// C.SRLI
					unsigned int shamt = ((instWord & 0x007c) >> 2); 
					unsigned int reg = (((instWord & 0x0380) >> 7) + 8);
					instWord = 0x00000000 | (shamt << 20) | (reg << 15) | 0x00005000 | (reg << 7) | 0x00000013;
				}

				if (funct2 == 0b01)
				{
					// C.SRAI
					unsigned int shamt = ((instWord & 0x007c) >> 2); 
					unsigned int reg = (((instWord & 0x0380) >> 7) + 8);
					instWord = 0x40000000 | (shamt << 20) | (reg << 15) | 0x00005000 | (reg << 7) | 0x00000013;
				}

				if (funct2 == 0b10)
				{
					// C.ANDI
					unsigned int imm = ((instWord & 0x007c) >> 2) | ((instWord & 0x1000) >> 7);
					(instWord & 0x1000) ? (imm = imm | 0xFC0) : (imm = imm | 0x0);
					unsigned int reg = (((instWord & 0x0380) >> 7) + 8);
					instWord = (imm << 20) | (reg << 15) | 0x00000000 | (reg << 7) | 0x00000013;

				}	

				if (funct6 == 0b100011)
				{
					switch (funct2AL)
					{
					case 0b00:
					{
						// C.SUB
						unsigned int reg1 = (((instWord & 0x0380) >> 7) + 8);
						unsigned int reg2 = (((instWord & 0x001C) >> 2) + 8);
						instWord = 0x40000000 | (reg2 << 20) | (reg1 << 15) | (reg1 << 7) | 0x00000033;
						break;
					}
					case 0b01:
					{
						// C.XOR
						unsigned int reg1 = (((instWord & 0x0380) >> 7) + 8);
						unsigned int reg2 = (((instWord & 0x001C) >> 2) + 8);
						instWord = 0x00000000 | (reg2 << 20) | (reg1 << 15) | 0x00004000 |(reg1 << 7) | 0x00000033;
						break;
					}
					case 0b10:
					{
						// C.OR
						unsigned int reg1 = (((instWord & 0x0380) >> 7) + 8);
						unsigned int reg2 = (((instWord & 0x001C) >> 2) + 8);
						instWord = 0x00000000 | (reg2 << 20) | (reg1 << 15) | 0x00006000 | (reg1 << 7) | 0x00000033;
						break;
					}
					case 0b11:
					{
						// C.AND
						unsigned int reg1 = (((instWord & 0x0380) >> 7) + 8);
						unsigned int reg2 = (((instWord & 0x001C) >> 2) + 8);
						instWord = 0x00000000 | (reg2 << 20) | (reg1 << 15) | 0x00007000 | (reg1 << 7) | 0x00000033;
						break;
					}
					default:
						break;
					}


				
				}
				
				break;
			}
			case 0b101: {
				// C.J
				unsigned int imm = (((instWord >> 3) & 0b111) | (((instWord >> 11) & 0b1) << 3) | (((instWord >> 2) & 0b1) << 4) | (((instWord >> 7) & 0b1) << 5) | (((instWord >> 6) & 0b1) << 6) | (((instWord >> 9) & 0b11) << 7) | (((instWord >> 8) & 0b1) << 9) | (((instWord >> 12) & 0b1) << 10)) << 1 | (((instWord >> 12) & 0b1) ? 0xFFFFF000 : 0x0);
				instWord = 0b1101111 | (0b00000 << 7) | (imm & 0xFF000) | (((imm >> 11) & 0b1) << 20) | (((imm >> 1) & 0b1111111111) << 21) | ((imm >> 20) & 0b1) << 31;
			
				break;
			}
			case 0b110:
			{
				// C.BEQZ
				// beq rs1', x0, offset
				unsigned int inst32 = 0;
				unsigned int rs1dash = (instWord >> 7) & 0b111;
				unsigned int offset = 0 | ((instWord & 0b100) <<3) | ((instWord & 0b11000) >> 2) | ((instWord & 0b1100000) << 1) | ((instWord & 0b110000000000) >> 7) | ((instWord & 0b1000000000000)>> 4);
				// sign extend to 12 bits offset using offset[8]
				if(offset & 0b100000000){
					offset |= 0b1111000000000;
				}

				inst32 |= 0b1100011; //opcode for beq
				inst32 |= (0b000<<12); // funct3 for beq, technically unrequired but kept for clarity
				rs1dash = rs1dash + 8;
				inst32 |= ((rs1dash)<<15); // rs1 for beq
				inst32 |= (0b00000<<20); // rs2 for beq, technically unrequired but kept for clarity
				// put offset into imm fields
				// put offset [ 10: 5] into index 25 to 30 of inst32
				inst32 |= ((offset & 0b11111100000) << 20);
				// put offset [4:1] into index 8 to 11 of inst32
				inst32 |= ((offset & 0b11110) << 7);
				// put offset [11] into index 7 of inst32
				inst32 |= ((offset & 0b100000000000) >> 4);
				// put offset [12] into index 31 of inst32
				inst32 |= ((offset & 0b1000000000000) << 19);
				instWord=inst32;
				break;
			}
			case 0b111:
			{
				// C.BNEZ
				// bne rs1 ′, x0, offset[8:1]
				unsigned int inst32 = 0;
				unsigned int rs1dash = (instWord >> 7) & 0b111;
				unsigned int offset = 0 | ((instWord & 0b100) <<3) | ((instWord & 0b11000) >> 2) | ((instWord & 0b1100000) << 1) | ((instWord & 0b110000000000) >> 7) | ((instWord & 0b1000000000000)>> 4);
				// sign extend to 12 bits offset using offset[8]
				if(offset & 0b100000000){
					offset |= 0b1111000000000;
				}

				inst32 |= 0b1100011; //opcode for beq
				inst32 |= (0b001<<12); // funct3 for beq, technically unrequired but kept for clarity
				rs1dash = rs1dash + 8;
				inst32 |= ((rs1dash)<<15); // rs1 for beq
				inst32 |= (0b00000<<20); // rs2 for beq, technically unrequired but kept for clarity
				// put offset into imm fields
				// put offset [ 10: 5] into index 25 to 30 of inst32
				inst32 |= ((offset & 0b11111100000) << 20);
				// put offset [4:1] into index 8 to 11 of inst32
				inst32 |= ((offset & 0b11110) << 7);
				// put offset [11] into index 7 of inst32
				inst32 |= ((offset & 0b100000000000) >> 4);
				// put offset [12] into index 31 of inst32
				inst32 |= ((offset & 0b1000000000000) << 19);
				instWord=inst32;
				break;
			}
			default:
				cout << "\tUnkown Compressed Instruction \n";
		}
	}else if(opcode == 2){
		switch(funct3){
			case 0b000:
			{
				// C.SLLI
				// slli rd, rd, shamt[5:0]
				unsigned int inst32 = 0;
				unsigned int rd = (instWord >> 7) & 0b11111;
				unsigned int shamt = 0 | ((instWord>>2)&0b11111) | ((instWord>>7)&0b100000);
				inst32 |= 0b0010011; //opcode for slli
				inst32 |= (0b001<<12); // funct3 for slli
				inst32 |= ((rd)<<7); // rd for slli
				inst32 |= ((rd)<<15); // rs1 for slli
				inst32 |= ((shamt)<<20); // shamt for slli
				instWord=inst32;
				break;
			}
			case 0b010: 
			{
				// C.LWSP
				unsigned int rd = instWord & 0xF80;
				unsigned int imm = (((instWord >> 4) & 0b0111) | (((instWord >> 2) & 0b11) << 4) | (((instWord >> 12) & 0b1) << 3)) << 2;
				unsigned int rs1 = 0b10;
				instWord = 0b0000011 | rd | (0b010 << 12) | (rs1 << 15) | (imm << 20);
			
				break;
			}
			case 0b100:
			{
				unsigned int funct1, funct2;
				funct1 = (instWord >> 12) & 0b1;
				funct2 = (instWord >> 2) & 0b11111;
				if (funct1 == 0 && funct2 == 0) {
					// C.JR
					unsigned int rs1 = (instWord >> 7) & 0b11111;
					instWord = 0b1100111 | (0b0 << 7) | (0b000 << 12) | (rs1 << 15);
				}
				else if (funct1 == 0) {
					// C.MV
					// add rd, x0, rs2
					unsigned int reg1 = ((instWord & 0x0F80) >> 7);
					unsigned int reg2 = ((instWord & 0x007C) >> 2);
					instWord = (reg2 << 20) | (reg1 << 7) | 0x00000033;
				}
				else if (funct1 == 1 && funct2 == 0) {
					// C.JALR
        			unsigned int rs1 = (instWord >> 7) & 0b11111;
					instWord = 0b1100111 | (0b1 << 7) | (0b000 << 12) | (rs1 << 15);
				}
				else if (funct1 == 1) {
					// C.ADD
					unsigned int reg1 = ((instWord & 0x0F80) >> 7);
					unsigned int reg2 = ((instWord & 0x007C) >> 2);
					instWord = (reg2 << 20) | (reg1 << 15) | (reg1 << 7) | 0x00000033;
				}
				else {
					cout << "\tUnkown Compressed Instruction \n";
				}
				break;
			}
			case 0b110: {
				// C.SWSP
				unsigned int rs2 = (instWord >> 2)& 0b11111;
				unsigned int imm = (((instWord >> 9) & 0b1111) | (((instWord >> 7) & 0b11) << 4)) << 2;
				unsigned int rs1 = 0b10;
				instWord = 0b0100011 | (rs2 << 20) | (0b010 << 12) | (rs1 << 15) | ((imm & 0b011111) << 7) | (((imm & 0b11100000) >> 5) << 25);
			
				break;
			}
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

	unsigned int instWord = 0;
	ifstream inFile, dataFile;
	ofstream outFile;

	//unsigned int instWord = 0b00000000000000000000000001110011;
	//instDecExec(instWord);

	// if argc == 3 we want to read data into memory else only read instructions
	if (argc == 3) {
		inFile.open(argv[1], ios::in | ios::binary | ios::ate);
		dataFile.open(argv[2], ios::out | ios::binary | ios::ate);
		if(!dataFile.is_open()){
		emitError("Cannot access data file");
	}
	}
	else if(argc == 2){
		inFile.open(argv[1], ios::in | ios::binary | ios::ate);

	}else{
		emitError("use: rvsim <machine_code_file_name> <data_file_name>\n Where data file is optional\n");
	}

	

	if (inFile.is_open())
	{
		
		int fsize = inFile.tellg();

		inFile.seekg(0, inFile.beg);
		if (!inFile.read((char*)memory, fsize)) emitError("Cannot read from input file\n");
		if(argc==3){
			unsigned char data[16*1024];
			fsize = dataFile.tellg();
			dataFile.seekg(0, dataFile.beg);
			if(!dataFile.read((char*)data, fsize)) emitError("Cannot read from data file\n");
			for(int i = 0; i < 16*1024; i++){
				memory[0x10000+i] = data[i];
			}
		}

		while (true) {
			// condition to check if it is compressed instruction
			if ((memory[pc] & 0b11) == 0b11) {
				instWord = (unsigned char)memory[pc] |
					(((unsigned char)memory[pc + 1]) << 8) |
					(((unsigned char)memory[pc + 2]) << 16) |
					(((unsigned char)memory[pc + 3]) << 24);
				nextPC = pc + 4;
			}
			else {
				instWord = (unsigned char)memory[pc] |
					(((unsigned char)memory[pc + 1]) << 8);
				instWord = decompress(instWord);
				nextPC = pc + 2;
			}

			/* removed to allow for compressed instructions
			instWord = (unsigned char)memory[pc] |
				(((unsigned char)memory[pc + 1]) << 8) |
				(((unsigned char)memory[pc + 2]) << 16) |
				(((unsigned char)memory[pc + 3]) << 24);
			pc += 4;*/

			
			instDecExec(instWord);
			pc = nextPC;
		}
	}
	else emitError("Cannot access input file\n");
}