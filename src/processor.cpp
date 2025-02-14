#include "processor.hpp"
#include "memory.hpp"
#include "regfile.hpp"
#include <cstdio>
#include <memory>
#include <cstdlib>
#include <cstdint>

extern std::unique_ptr<RegFile> regs;
extern std::unique_ptr<Memory> mem;

void fetch(void){
	uint32_t pc = regs->readPC();
	uint32_t instr = mem->readWord(pc);
	regs->updatePC((regs->readPC() + 4));
	decode(instr);
	return;
};

void decode(uint32_t instr){
	if (instr == 0){
		regs->print();
		mem->print();
		exit(1);
	}
	uint8_t opcode = instr & OPCODEMASK;
	switch (opcode){
	case (RTYPE):
		break;
	case (ITYPE):
		break;
	case (STYPE):
		break;
	case (BTYPE):
		break;
	case (UTYPE):
		break;
	case (JTYPE):
		break;
	default:
		break;
	}
};

void execute(void){
	/*	
		switch (funct3){
			case(LB):
				break;
			case(LH):
				break;
			case(LW):
				break;
			case(LBU):
				break;
			case(LHU):
				break;
			default:
				break;
		}
		*/
};


