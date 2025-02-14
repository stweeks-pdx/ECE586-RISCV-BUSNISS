#ifndef _INSTR_HPP_
#define _INSTR_HPP_
#include <cstdint>

class InstrBase {
	public:
		virtual void decode(uint32_t instr) = 0; // Make decode a pure virtual function
		virtual void execute() = 0; // Make execute a pure virtual function
		virtual ~InstrBase() = default; // Virtual destructor
};

#endif // _INSTR_HPP_
