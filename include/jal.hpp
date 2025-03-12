#ifndef _JAL_HPP_
#define _JAL_HPP_


#include "instr.hpp"


class JAL : public InstrBase {
	private:
		uint8_t rd;
		uint32_t imm;
	public:
		void decode(uint32_t instr) override;
		void execute() override;
};

#endif // _JAL_HPP_
