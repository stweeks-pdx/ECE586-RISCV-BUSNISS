#include <iostream>
#include <memory>
#include <cstdio>
#include "regfile.hpp"
#include "jal.hpp"
#include "processor.hpp"

extern std::unique_ptr<RegFile> regs;

int posJump(){
	int testPassed = 0;
	uint32_t jump;
	uint8_t opcode = JALOP;
	uint8_t rd = ra;
	uint32_t imm = 0x759A4;
	JAL jal;

	test = (imm << 12) | (rd << 7) | opcode;

	regs->updatePC(0x4);

	uint32_t ePC = 0x527AC;
        uint32_t eRA = regs->readPC();	
	
	jal.decode(jump);
	jal.execute();


	if (ePC != regs->readPC() || eRA != regs->read(rd)){
		printf("Pos jump test failed! PC is 0x%X, expected is 0x%X, RA is 0x%X, expected is 0x%X", regs->readPC(), ePC, regs->read(rd), eRA);
		testPassed = -1;
		regs->print();
	}

	return testPassed;
}

int negJump(){
	int testPassed = 0;
	uint32_t jump;
	uint8_t opcode = JALOP;
	uint8_t rd = ra;
	uint32_t imm = 0xE59A4;
	JAL jal;

	test = (imm << 12) | (rd << 7) | opcode;

	regs->updatePC(0x4);

	uint32_t ePC = 0xD272C;
	uint32_t eRA = regs->readPC();

	jal.decode(jump);
	jal.execute();

	if (ePC != regs->readPC() || eRA != regs->read(rd)){
		printf("Neg jump test failed! PC is 0x%X, expected is 0x%X, RA is 0x%X, expected is 0x%X", regs->readPC(), ePC, regs->read(rd), eRA);
		testPassed = -1;
		regs->print();
	}

	return testPassed;

}

int badJump(){
	int testPassed = 0;
	uint32_t jump;
	uint8_t opcode = JALOP;
	uint8_t rd = 0x22;
	uint32_t imm = 0x759AB;
	JAL jal;

	test = (imm << 12) | (rd << 7) | opcode;

	regs->updatePC(0x4);



}



