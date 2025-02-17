#include "store.hpp"
#include "memory.hpp"
#include "regfile.hpp"
#include <memory>
#include <iostream>

extern std::unique_ptr<RegFile> regs;
extern std::unique_ptr<Memory> mem;

constexpr uint32_t REGMASK    = 0x1F;
constexpr uint32_t F3MASK     = 0x07;
constexpr uint32_t IMMUMASK   = 0x0FE0;
constexpr uint32_t IMMLMASK   = 0x1F;
constexpr uint32_t OFFEXTMASK = 0xFFFFF000;
constexpr uint8_t  MSBMASK    = 0x01;
constexpr uint8_t  IMMMSB     = 11;

void STORE::decode(uint32_t instr) {
    imm     = (instr >> 20) & IMMUMASK; // Grabs upper 7 bits of upper 3 nibbles
    rs2     = (instr >> 20) & REGMASK;
    rs1     = (instr >> 15) & REGMASK;
    funct3  = (instr >> 12) & F3MASK;
    imm    |= (instr >>  7) & IMMLMASK; // Grabs lower 5 bits to complete imm field
}

void STORE::execute() {
    uint32_t val;
    uint32_t offset;
    uint32_t address;

    val = regs->read(rs2);
    offset = ((imm >> IMMMSB) & MSBMASK) ? (imm | OFFEXTMASK) : (imm);
    address = regs->read(rs1) + offset;
    
#ifdef DEBUG
    std::cout << "Storing to 0x" << std::hex << address << " from reg " << std::dec << unsigned(rs2) << std::endl;
#endif

    switch (funct3) {
        case SB:
            mem->writeByte(address, val);
#ifdef DEBUG
	    std::cout << "\tVal: 0x" << std::hex << (val & BYTEMASK) << std::endl;
#endif
            break;
        case SH:
            mem->writeHWord(address, val);
#ifdef DEBUG
	    std::cout << "\tVal: 0x" << std::hex << (val & HWORDMASK) << std::endl;
#endif
            break;
        case SW:
            mem->writeWord(address, val);
#ifdef DEBUG
	    std::cout << "\tVal: 0x" << std::hex << val << std::endl;
#endif
             break;
       default:
            std::cout << "Error in STORE operation" << std::endl;
            break;
    }
}
