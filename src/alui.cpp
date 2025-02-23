#include "alui.hpp"
#include "regfile.hpp"
#include <memory>
#include <iostream>

constexpr uint32_t REGMASK = 0x1F;
constexpr uint32_t F3MASK  = 0x07;

extern std::unique_ptr<RegFile> regs;

void ALUI::decode(uint32_t instr) {
	imm = (instr >> 20);
	rs1 = (instr >> 15) & REGMASK;
	funct3 = (instr >> 12) & F3MASK;
	rd = (instr >> 7) & REGMASK;
	funct7 = (imm >> 5);
}

void ALUI::execute() {

	switch (funct3) {
		case ADDI:
			// do stuff
			break;
		case SLLI:
			// do stuff
			break;
		case SLTI:
			// do stuff
			break;
		case SLTIU:
			// do stuff
			break;
		case XORI:
			// do stuff
			break;
		case SRL_A_I:
			if (funct7 == 0) {
				// SRLI
			} else {
				// SRAI
			}
			break;
		case ORI:
			// do stuff
			break;
		case ANDI:
			// do stuff
			break;
		default:
			std::cout << "Error in ALUI operation" << std::endl;
			break;
	}
}
