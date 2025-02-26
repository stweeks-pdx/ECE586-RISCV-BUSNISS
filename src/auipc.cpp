#include "auipc.hpp"
#include "regfile.hpp"
#include <memory>
#include <iostream>

extern std::unique_ptr<RegFile> regs;

constexpr uint32_t REGMASK = 0x1F;
constexpr uint32_t IMMMASK = 0xFFFFF000;

void AUIPC::decode(uint32_t instr) {
    imm = instr & IMMMASK;
    rd  = (instr >> 7) & REGMASK;
}

void AUIPC::execute() {
    uint32_t val = regs->readPC() - 4;

#ifdef DEBUG
    std::cout << "PC: " << std::hex << val << std::endl;
#endif
    
    val += imm;

#ifdef DEBUG
    std::cout << "\tLoading to " << unsigned(rd) << "\tVal: 0x" << std::hex << val << std::endl;
#endif

    regs->write(rd, val);

    if (regs->read(rd) != val)
        std::cout << "Error in AUIPC operation" << std::endl;
}
