#ifndef _AUIPC_HPP_
#define _AUIPC_HPP_

#include "instr.hpp"

class AUIPC : public InstrBase {
	private:
		uint32_t imm;
		uint8_t  rd;
	public:
		void decode(uint32_t instr) override;
		void execute() override;
};

#endif // _AUIPC_HPP_
