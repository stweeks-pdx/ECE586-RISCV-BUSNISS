#include "branch.hpp"
#include "regfile.hpp"
#include <memory>
#include <iostream>

constexpr uint32_t REGMASK  = 0x1F;
constexpr uint32_t F3MASK   = 0x07;
constexpr uint32_t BIT1MASK = 0x01;
constexpr uint32_t BIT4MASK = 0x0F;
constexpr uint32_t BIT6MASK = 0x3F;
constexpr uint32_t BEXTMASK = 0xFFFFE000;

extern std::unique_ptr<RegFile> regs;

void BRANCH::decode(uint32_t instr) {
    uint8_t imm12, imm11, imm10_5, imm4_1;
    imm = 0;

    imm12   =  instr >> 31;
    imm10_5 = (instr >> 25) & BIT6MASK;
    rs2     = (instr >> 20) & REGMASK;
    rs1     = (instr >> 15) & REGMASK;
    funct3  = (instr >> 12) & F3MASK;
    imm4_1  = (instr >>  8) & BIT4MASK;
    imm11   = (instr >>  7) & BIT1MASK;
    imm     = (imm12 << 12) | (imm11 << 11) | (imm10_5 << 5) | (imm4_1 << 1);
}

void BRANCH::execute() {
    uint32_t base = regs->readPC() - 4;
    uint32_t offset = ((imm >> 12) & BIT1MASK) ? (imm | BEXTMASK) : (imm);
    uint32_t target = base + offset;
    uint32_t uval1 = regs->read(rs1);
    uint32_t uval2 = regs->read(rs2);
    int32_t  val1  = static_cast<int32_t>(uval1);
    int32_t  val2  = static_cast<int32_t>(uval2);

    if ((target % 4) != 0) throwException(&target); 

#ifdef DEBUG
    std::cout << "Branch target: " << std::hex << target << std::endl;
#endif

    switch (funct3) {
        case BEQ:
            check((val1 == val2), target);
            break;
        case BNE:
            check((val1 != val2), target);
            break;
        case BLT:
            check((val1 < val2), target);
            break;
        case BGE:
            check((val1 >= val2), target);
            break;
        case BLTU:
            check((uval1 < uval2), target);
            break;
        case BGEU:
            check((uval1 >= uval2), target);
            break;
       default:
            std::cout << "Error in BRANCH operation" << std::endl;
            break;
    }
}

void BRANCH::check(bool taken, uint32_t target) {
    if (taken){
#ifdef DEBUG
        std::cout << "\tBRANCH TAKEN" << std::endl;
#endif
        regs->updatePC(target);
    } else {
#ifdef DEBUG
        std::cout << "\tBRANCH NOT TAKEN" << std::endl;
#endif
    }
}

void BRANCH::throwException(uint32_t* target) {
#ifdef DEBUG	
	std::cout << "ERROR: Misaligned target" << std::endl;
#endif

#ifdef CONTINUE 
	*target = *target - (*target%4);
#elif  ISR
	// TODO: Connect to ISR
#else  
	abort();
#endif	
}
