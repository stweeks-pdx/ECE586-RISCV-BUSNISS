#include "load.hpp"
#include "memory.hpp"
#include "regfile.hpp"
#include <memory>
#include <iostream>

extern std::unique_ptr<RegFile> regs;
extern std::unique_ptr<Memory> mem;

constexpr uint32_t REGMASK    = 0x0000001F;
constexpr uint32_t F3MASK     = 0x00000007;
constexpr uint32_t BEXTMASK   = 0xFFFFFF00;
constexpr uint32_t HWEXTMASK  = 0xFFFF0000;
constexpr uint32_t OFFEXTMASK = 0xFFFFF000;
constexpr uint8_t  MSBMASK = 0x01;
constexpr uint8_t  IMMMSB = 11;
constexpr uint8_t  BMSB = 7;
constexpr uint8_t  HWMSB = 15;

void LOAD::decode(uint32_t instr) {
    imm     = (instr >> 20);
    rs1     = (instr >> 15) & REGMASK;
    funct3  = (instr >> 12) & F3MASK;
    rd      = (instr >> 7)  & REGMASK;
}

void LOAD::execute() {
    uint32_t val;
    uint32_t offset;
    uint32_t address;

    offset = ((imm >> IMMMSB) & MSBMASK) ? (imm | OFFEXTMASK) : (imm);
    address = regs->read(rs1) + offset;

#ifdef DEBUG
    std::cout << "Loading to " << unsigned(rd) << " from " std::hex << address << std::endl;
#endif

    switch (funct3) {
        case LB:
            val = mem->readByte(address) & BYTEMASK;
            val = ((val >> BMSB) & MSBMASK) ? (val | BEXTMASK) : (val);
            regs->write(rd, val);
            break;
        case LH:
            val = mem->readHWord(address) & HWORDMASK;
            val = ((val >> HWMSB) & MSBMASK) ? (val | HWEXTMASK) : (val);       
            regs->write(rd, val);
            break;
        case LW:
            val = mem->readWord(address);
            regs->write(rd, val);
            break;
        case LBU:
            val = mem->readByte(address) & BYTEMASK;
            regs->write(rd, val);            
            break;
        case LHU:
            val = mem->readHWord(address) & HWORDMASK;
            regs->write(rd, val);
            break;
        default:
            std::cout << "Error in LOAD operation" << std::endl;
            break;
    }
#ifdef DEBUG
    std::cout << "\tVal: " << std::hex << val << std::endl;
#endif
}

