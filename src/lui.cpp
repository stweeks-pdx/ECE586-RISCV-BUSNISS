#include "lui.hpp"
#include "regfile.hpp"
#include <memory>
#include <iostream>

extern std::unique_ptr<RegFile> regs;

constexpr uint32_t REGMASK = 0x1F;
constexpr uint32_t IMMMASK = 0xFFFFF000;

void LUI::decode(uint32_t instr) {
    imm = instr & IMMMASK;
    rd  = (instr >> 7) & REGMASK;
}

void LUI::execute() {
#ifdef DEBUG
    std::cout << "Loading to " << unsigned(rd) << "\tVal: 0x" std::hex << imm << std::endl;
#endif

    regs->write(rd, imm);

    if (regs->read(rd) != imm)
        std::cout << "Error in LUI operation" << std::endl;
}

