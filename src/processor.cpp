#include "processor.hpp"
#include "memory.hpp"
#include "regfile.hpp"
#include <cstdio>
#include <memory>
#include <cstdlib>
#include <cstdint>
#include <unordered_map>
#include "instr.hpp"
#include "alu.hpp"
#include "load.hpp"

extern std::unique_ptr<RegFile> regs;
extern std::unique_ptr<Memory> mem;

static std::unordered_map<uint8_t, std::unique_ptr<InstrBase>> instrMap;

static std::unique_ptr<ALU> aluOp;
static std::unique_ptr<LOAD> loadOp;

void constructMap(void) {
	// create ALU operation
	aluOp = std::make_unique<ALU>();
	instrMap[ALUOP] = std::move(aluOp);

	// create LOAD operation
	loadOp = std::make_unique<LOAD>();
	instrMap[LOADOP] = std::move(loadOp);
}

void fetch(void) {
	uint32_t pc = regs->readPC();
	uint32_t instr = mem->readWord(pc);
	regs->updatePC((regs->readPC() + 4));
	
	// TODO: REMOVE WITH JUMP CLASS DOING THIS
	if (instr == 0) {
		regs->print();
		mem->print('z');
		exit(0);
	}

	uint8_t opcode = instr & OPCODEMASK;
	std::unique_ptr<InstrBase>& opRef = instrMap.at(opcode);

	opRef->decode(instr);

	opRef->execute();
	return;
}
