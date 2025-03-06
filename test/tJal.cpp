#include <iostream>
#include <memory>
#include <cstdio>
#include "regfile.hpp"
#include "jal.hpp"
#include "processor.hpp"

extern std::unique_ptr<RegFile> regs;

int positiveJump(){
	int testPassed = 0;
	uint32_t jump;
	uint8_t opcode = JALOP;
	uint8_t rd = ra;
	uint32_t imm = 0x759A4;
	JAL jal;

	jump = (imm << 12) | (rd << 7) | opcode;

	regs->updatePC(0x4);

	uint32_t ePC = 0xA4F58;
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

int negativeJump(){
	int testPassed = 0;
	uint32_t jump;
	uint8_t opcode = JALOP;
	uint8_t rd = ra;
	uint32_t imm = 0xE59A4;
	JAL jal;

	jump = (imm << 12) | (rd << 7) | opcode;

	regs->updatePC(0x4);

	uint32_t ePC = 0xFFFA4E58;
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

int badImmJump(){
	int testPassed = 0;
	uint32_t jump;
	uint8_t opcode = JALOP;
	uint8_t rd = 0x22;
	uint32_t imm = 0x75AAB;
	JAL jal;

	jump = (imm << 12) | (rd << 7) | opcode;

	regs->updatePC(0x4);

	uint32_t ePC = 0x4; //We shouldn't take this jump, bad imm field
        uint32_t eRA = regs->read(rd);

	jal.decode(jump);
	jal.execute();

	if (ePC != regs->readPC() || eRA != regs->read(rd)){
		printf("Bad jump test failed! PC is 0x%X, expected is 0x%X, RA is 0x%X, expected is 0x%X", regs->readPC(), ePC, regs->read(rd), eRA);
		testPassed = -1;
		regs->print();
	}	

	return testPassed;

}

int jal_t(){
	int testPassed = 0;
	std::cout << "++++ Testing positive displacement ++++" << std::endl;
	testPassed |= positiveJump();
	std::cout << "++++ Testing negative displacement ++++" << std::endl;
	testPassed |= negativeJump();
	std::cout << "++++ Testing incorrectly encoded imm field ++++" << std::endl;
	testPassed |= badImmJump();

	return testPassed;
}

