#include "jalr.hpp"
#include "regfile.hpp"
#include <memory>
#include <iostream>


extern std::unique_ptr<RegFile> regs;
//extern bool continueSim;

constexpr uint32_t REGMASK = 0x0000001F;
constexpr uint32_t IMMMASK = 0x00000FFF;
constexpr uint32_t FUNCMASK = 0x00000007;
constexpr uint32_t SIGNMASK = 0xFFFFF000;
constexpr uint32_t TARMASK = 0xFFFFFFFE;
constexpr uint32_t ALIGNMASK = 0x3;

void JALR::decode(uint32_t instr) {
	imm = (instr >> 31) ? ((instr >> 20) | SIGNMASK) : (instr >> 20);
	rs1 = (instr >> 15) & REGMASK;
	func3 = (instr >> 12) & FUNCMASK;
	rd = (instr >> 7) & REGMASK;
}

void JALR::execute() {
	if (!func3){
	uint32_t target = (regs->read(rs1) + imm) & TARMASK;
		if ((target & ALIGNMASK) != 0){
			//exception == true
			#ifdef DEBUG
			printf("Misaligned memory reference in JALR instruction");
			#endif
			return;
		}
	regs->write(rd, regs->readPC());
	regs->updatePC(target);
	#ifdef DEBUG
	printf("Writing 0x%8X to register %d, new PC address is 0x%8X. RS1(%d) value was 0x%8X\n", regs->readPC(), rd, target, rs1, regs->read(rs1));
	#endif
		if(rd == ra && target == 0){
			//#ifdef DEBUG
			printf("Goodbye! Target is 0x%x", target);
			//#endif
			exit(0);
			//continueSim = false;	
		}
	}
	else{
		//exception = true;
		#ifdef DEBUG
		printf("Decoding detects incorrectly encoded jalr instruction, exception!");
		#endif
		return;
	}


}
