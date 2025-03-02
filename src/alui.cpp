#include "alui.hpp"
#include "regfile.hpp"
#include <memory>
#include <iostream>

constexpr uint32_t REGMASK    = 0x1F;
constexpr uint32_t F3MASK     = 0x07;
constexpr uint32_t SHIFTMASK  = 0x1F;
constexpr uint32_t OFFEXTMASK = 0xFFFFF000;
constexpr uint8_t  MSBMASK    = 0x1;
constexpr uint8_t  IMMSB      = 11;

extern std::unique_ptr<RegFile> regs;

void ALUI::decode(uint32_t instr) {
	imm = (instr >> 20);
	rs1 = (instr >> 15) & REGMASK;
	funct3 = (instr >> 12) & F3MASK;
	rd = (instr >> 7) & REGMASK;
	funct7 = (imm >> 5);
}

void ALUI::execute() {
	uint32_t result = -1;
	int32_t addendum;
	uint32_t Ushiftee;
	int32_t  shiftee;
	uint32_t shamt;
	int32_t comp;
	uint32_t Ucomp;
	uint32_t Uval;

	uint32_t signExImm = ((imm >> IMMSB) & MSBMASK) ? (OFFEXTMASK | imm) : imm;

	switch (funct3) {
		case ADDI:
			addendum = static_cast<int32_t>(regs->read(rs1));
			result = addendum + static_cast<int32_t>(signExImm);
			regs->write(rd, result);
			break;
		case SLLI:
			Ushiftee = regs->read(rs1);
			shamt = imm & SHIFTMASK;
			result = Ushiftee << shamt;
			regs->write(rd, result);
			break;
		case SLTI:
			comp = static_cast<int32_t>(regs->read(rs1));
			result = (comp < static_cast<int32_t>(signExImm));
			regs->write(rd, result);
			break;
		case SLTIU:
			Ucomp = regs->read(rs1);
			result = (Ucomp < signExImm);
			regs->write(rd, result);
			break;
		case XORI:
			Uval = regs->read(rs1);
			result = Uval ^ signExImm;
			regs->write(rd, result);
			break;
		case SRL_A_I:
			if (!funct7) {
				// SRLI
				Ushiftee = regs->read(rs1);
				shamt = imm & SHIFTMASK;
				result = Ushiftee >> shamt;
				regs->write(rd, result);
			} else {
				// SRAI
				shiftee = static_cast<int32_t>(regs->read(rs1));
				shamt = imm & SHIFTMASK;
				result = shiftee >> shamt;
				regs->write(rd, result);
			}
			break;
		case ORI:
			Uval = regs->read(rs1);
			result = Uval | signExImm;
			regs->write(rd, result);
			break;
		case ANDI:
			Uval = regs->read(rs1);
			result = Uval & signExImm;
			regs->write(rd, result);
			break;
		default:
			std::cout << "Error in ALUI operation" << std::endl;
			break;
	}
}
