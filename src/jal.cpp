#include "jal.hpp"
#include "regfile.hpp"
#include <memory>
#include <iostream>
#include <cstdio>
#include <cstdlib>


extern std::unique_ptr<RegFile> regs;

constexpr uint32_t REGMASK = 0x1F;
constexpr uint32_t BIT1MASK = 0x1;
constexpr uint32_t BIT8MASK = 0xFF;
constexpr uint32_t BIT10MASK = 0x3FF;
constexpr uint32_t SIGNMASK = 0xFFF00000;

void JAL::decode(uint32_t instr){
	uint8_t imm20,imm11,imm19_12;
	uint16_t imm10_1;
	
	imm = 0;

	imm20 = instr >> 31;
	imm11 = (instr >> 20) & BIT1MASK;
	imm19_12 = (instr >> 12) & BIT8MASK;
	imm10_1 = (instr >> 21) & BIT10MASK;
	imm = (imm20 << 20) | (imm19_12 << 12) | (imm11 << 11) | (imm10_1 << 1);
	//Check MSB of immediate field and sign extend accordingly 
	imm = (imm >> 20) ? (imm | SIGNMASK) : imm; 
	rd = (instr >> 7) & REGMASK;
}

void JAL::execute(){
	uint32_t target = ((regs->readPC() - 4) + imm);

	if((target % 4) != 0){
		std::cout<< "Misaligned memory reference in JAL instruction" << std::endl;
		exit(1);
	}
	regs->write(rd, regs->readPC());
	regs->updatePC(target);

	#ifdef DEBUG
	printf("Writing 0x%8X to register %d, new PC address is 0x%8X\n",regs->readPC(), rd, target);
	#endif	
}


	
