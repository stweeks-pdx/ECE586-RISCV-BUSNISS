#ifndef _ALU_HPP_
#define _ALU_HPP_

#include "instr.hpp"

constexpr uint8_t ADD_SUB = 0x0;
constexpr uint8_t SLL = 0x1;
constexpr uint8_t SLT = 0x2;
constexpr uint8_t SLTU = 0x3;
constexpr uint8_t XOR = 0x4;
constexpr uint8_t SRL_A = 0x5;
constexpr uint8_t OR = 0x6;
constexpr uint8_t AND = 0x7;

class ALU : public InstrBase {
	private:
		uint8_t funct7;
		uint8_t rs2;
		uint8_t rs1;
		uint8_t funct3;
		uint8_t rd;
	public:
		void decode(uint32_t instr) override;
		void execute() override;
};

#endif // _ALU_HAPP_
