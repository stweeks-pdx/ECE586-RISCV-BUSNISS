#ifndef _ALUI_HPP_
#define _ALUI_HPP_

#include "instr.hpp"

constexpr uint8_t ADDI = 0x0;
constexpr uint8_t SLLI = 0x1;
constexpr uint8_t SLTI = 0x2;
constexpr uint8_t SLTIU = 0x3;
constexpr uint8_t XORI = 0x4;
constexpr uint8_t SRL_A_I = 0x5;
constexpr uint8_t ORI = 0x6;
constexpr uint8_t ANDI = 0x7;

class ALUI : public InstrBase {
	private:
		uint16_t imm;
		uint8_t rs1;
		uint8_t funct3;
		uint8_t rd;
		uint8_t funct7;
	public:
		void decode(uint32_t instr) override;
		void execute() override;
};

#endif // _ALUI_HPP_
