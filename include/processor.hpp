#ifndef _PROCESSOR_HPP_
#define _PROCESSOR_HPP_
#include <cstdio>
#include <cstdint>
//Masks for bit field
constexpr uint32_t OPCODEMASK 0x0000007F
//Instruction types
constexpr uint8_t RTYPE 0x33
constexpr uint8_t ITYPE 0x13
constexpr uint8_t STYPE 0x23
constexpr uint8_t BTYPE 0x63
constexpr uint8_t UTYPE 0x6F
constexpr uint8_t JTYPE 0x67
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
