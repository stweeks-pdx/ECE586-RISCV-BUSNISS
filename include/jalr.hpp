#ifndef _JALR_HPP_
#define _JALR_HHPP_

#include "instr.hpp"

class JALR : public InstrBase {
	private:
		uint32_t imm;
		uint32_t rs1;
		uint32_t rd;
		uint32_t func3;
	public:
		void decode(uint32_t instr) override;
		void execute() override;
};

#endif // _JALR_HPP_
