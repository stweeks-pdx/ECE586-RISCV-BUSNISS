#ifndef _PROCESSOR_HPP_
#define _PROCESSOR_HPP_
#include <cstdio>
#include <cstdint>
//Masks for bit field
#define OPCODEMASK 0x0000007F
//Instruction types
#define RTYPE 0x33
#define ITYPE 0x13
#define STYPE 0x23
#define BTYPE 0x63
#define UTYPE 0x6F
#define JTYPE 0x67
//Funct3 codes
//Funct7 codes


//structs
struct iType { 
	uint16_t imm;
	uint8_t rs1;
	uint8_t funct3;
	uint8_t rd;
	uint8_t opcode;
};

struct sType { 
	uint16_t imm;
	uint8_t rs2;
	uint8_t rs1;
	uint8_t funct3;
	uint8_t opcode;
};

union instruction {
	iType itype;
	sType stype;
};

void fetch(void);

void decode(uint32_t instr);

void execute(void);

#endif //_PROCESSOR_HPP_
