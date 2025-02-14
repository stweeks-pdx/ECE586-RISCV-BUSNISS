#include "alu.hpp"
#include <iostream>

constexpr uint32_t REGMASK = 0x1F;
constexpr uint32_t F3MASK  = 0x3;

void ALU::decode(uint32_t instr) {
	funct7  = (instr >> 25);
	rs2     = (instr >> 20) & REGMASK;
	rs1     = (instr >> 15) & REGMASK;
	funct3  = (instr >> 12) & F3MASK;
	rd      = (instr >> 7)  & REGMASK;
}

void ALU::execute() {
	switch (funct3) {
		case ADD_SUB:
			if (funct7 == 0) {
				// do ADD
			} else {
				// do SUB
			}
			break;
		case SLL:
			// do SLL
			break;
		case SLT:
			// do SLT
			break;
		case SLTU:
			// do SLTU
			break;
		case XOR:
			// do XOR
			break;
		case SRL_A:
			if (funct7 == 0) {
				// do SRL
			} else {
				// do SRA
			}
			break;
		case OR:
			// do OR
			break;
		case AND:
			// do AND
			break;
		default:
			std::cout << "Error in ALU operation" << std::endl;
			break;
	}
}

