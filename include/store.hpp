#ifndef _STORE_HPP_
#define _STORE_HPP_

#include "instr.hpp"

constexpr uint8_t SB = 0x0;
constexpr uint8_t SH = 0x1;
constexpr uint8_t SW = 0x2;

class STORE : public InstrBase {
    private:
        uint16_t imm;
        uint8_t rs2;
        uint8_t rs1;
        uint8_t funct3;
    public:
        void decode(uint32_t instr) override;
        void execute() override;
};

#endif // _STORE_HPP_
