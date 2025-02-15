#ifndef _LOAD_HPP_
#define _LOAD_HPP_

#include "instr.hpp"

constexpr uint8_t LB = 0x0;
constexpr uint8_t LH = 0x1;
constexpr uint8_t LW = 0x2;
constexpr uint8_t LBU = 0x4;
constexpr uint8_t LHU = 0x5;

class LOAD : public InstrBase {
	private:
		uint16_t imm;
		uint8_t rs1;
		uint8_t funct3;
		uint8_t rd;
	public:
		void decode(uint32_t instr) override;
		void execute() override;
};

#endif // _LOAD_HPP_
