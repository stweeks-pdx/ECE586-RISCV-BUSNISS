#include "alu.hpp"
#include "regfile.hpp"
#include <memory>
#include <iostream>

constexpr uint32_t REGMASK   = 0x1F;
constexpr uint32_t F3MASK    = 0x07;
constexpr uint32_t SHIFTMASK = 0x1F;

extern std::unique_ptr<RegFile> regs;

void ALU::decode(uint32_t instr) {
	funct7  = (instr >> 25);
	rs2     = (instr >> 20) & REGMASK;
	rs1     = (instr >> 15) & REGMASK;
	funct3  = (instr >> 12) & F3MASK;
	rd      = (instr >> 7)  & REGMASK;
}

void ALU::execute() {
	uint32_t result = -1;
	int32_t addendum1;
	int32_t addendum2;
	int32_t comp1;
	int32_t comp2;
	uint32_t compU1;
	uint32_t compU2;
	uint32_t shifteeU;
	int32_t shiftee;
	uint32_t shamt;
	uint32_t valU1;
	uint32_t valU2;

	switch (funct3) {
		case ADD_SUB:
			if (funct7 == 0) {
				// Do ADD
				addendum1 = static_cast<int32_t>(regs->read(rs1));
				addendum2 = static_cast<int32_t>(regs->read(rs2));
				result = addendum1 + addendum2;
				regs->write(rd, result);
			} else {
				// Do SUB
				addendum1 = static_cast<int32_t>(regs->read(rs1));
				addendum2 = static_cast<int32_t>(regs->read(rs2));
				result = addendum1 - addendum2;
				regs->write(rd, result);
			}
			break;
		case SLL:
			shifteeU = regs->read(rs1);
			shamt = regs->read(rs2);
			shamt &= SHIFTMASK;
			result = shifteeU << shamt;
			regs->write(rd, result);
			break;
		case SLT:
			comp1 = static_cast<int32_t>(regs->read(rs1));
			comp2 = static_cast<int32_t>(regs->read(rs2));
			result = comp1 < comp2;
			regs->write(rd, result);
			break;
		case SLTU:
			if (rs1 == zero) {
				compU2 = regs->read(rs2);
				result = compU2 != 0;
				regs->write(rd, result);
			} else {
				compU1 = regs->read(rs1);
				compU2 = regs->read(rs2);
				result = compU1 < compU2;
				regs->write(rd, result);
			}
			break;
		case XOR:
			valU1 = regs->read(rs1);
			valU2 = regs->read(rs2);
			result = valU1 ^ valU2;
			regs->write(rd, result);
			break;
		case SRL_A:
			if (funct7 == 0) {
				// Do SRL
				shifteeU = regs->read(rs1);
				shamt = regs->read(rs2);
				shamt &= SHIFTMASK;
				result = shifteeU >> shamt;
				regs->write(rd, result);
			} else {
				// Do SRA
				shiftee = static_cast<int32_t>(regs->read(rs1));
				shamt = regs->read(rs2);
				shamt &= SHIFTMASK;
				result = shiftee >> shamt;
				regs->write(rd, static_cast<uint32_t>(result));
			}
			break;
		case OR:
			valU1 = regs->read(rs1);
			valU2 = regs->read(rs2);
			result = valU1 | valU2;
			regs->write(rd, result);
			break;
		case AND:
			valU1 = regs->read(rs1);
			valU2 = regs->read(rs2);
			result = valU1 & valU2;
			regs->write(rd, result);
			break;
		default:
			std::cout << "Error in ALU operation" << std::endl;
			break;
	}
}

