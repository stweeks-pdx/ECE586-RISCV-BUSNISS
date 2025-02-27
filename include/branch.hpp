#ifndef _BRANCH_HPP_
#define _BRANCH_HPP_

#include "instr.hpp"

constexpr uint8_t BEQ  = 0x0;
constexpr uint8_t BNE  = 0x1;
constexpr uint8_t BLT  = 0x4;
constexpr uint8_t BGE  = 0x5;
constexpr uint8_t BLTU = 0x6;
constexpr uint8_t BGEU = 0x7;

class BRANCH : public InstrBase {
	private:
		uint16_t imm;
		uint8_t  rs2;
		uint8_t  rs1;
		uint8_t  funct3;
		void check(bool taken, uint32_t target);
		void throwException(void);
	public:
		void decode(uint32_t instr) override;
		void execute() override;
};

#endif // _BRANCH_HPP_
