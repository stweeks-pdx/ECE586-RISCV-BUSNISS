#ifndef _LUI_HPP_
#define _LUI_HPP_

#include "instr.hpp"

class LUI : public InstrBase {
	private:
		uint32_t imm;
		uint8_t  rd;
	public:
		void decode(uint32_t instr) override;
		void execute() override;
};

#endif // _LUI_HPP_
