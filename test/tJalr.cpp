#include <cstdio>
#include <memory>
#include <iostream>
#include "regfile.hpp"
#include "processor.hpp"
#include "jalr.hpp"

extern std::unique_ptr<RegFile> regs;

int posJump(){
	int test_passed = 0;
	uint32_t testJump;
	uint8_t op = JALROP;
	uint8_t func3 = 0;
	uint8_t rs1 = 0x14;
	uint8_t rd = ra;
	uint16_t imm = 0x07B1;
	JALR jalr;

	testJump = (imm << 20) | (rs1 << 15) | (func3 << 12) | (rd << 7) | op;
	
	regs->updatePC(0x0);
	regs->write(rs1, 0x50);

	uint32_t ePC = ((regs->read(rs1) + imm) >> 1) << 1;
	uint32_t eRA = regs->readPC();

	jalr.decode(testJump);
	jalr.execute();

	uint32_t res = regs->readPC();

	if (ePC != res || eRA != regs->read(rd)){
		printf("Positive displacement jump test failed. New PC 0x%X, expected 0x%X. RA value 0x%X, expected 0x%X", res, ePC, regs->read(rd), eRA);
		test_passed = -1;
		regs->print();
	}

	return test_passed;
};

int negJump(){
	int test_passed = 0;
	uint32_t testJump;
	uint8_t op = JALROP;
	uint8_t func3 = 0;
	uint8_t rs1 = 0x14;
	uint8_t rd = ra;
	uint32_t imm = 0xFFFFFEB1;
	uint32_t ePC;
	JALR jalr;

	testJump = (imm << 20) | (rs1 << 15) | (func3 << 12) | (rd << 7) | op;

	regs->updatePC(0x0);
	regs->write(rs1, 0x50);

	ePC = (regs->read(rs1) + imm) >> 1 << 1;
	uint32_t eRA = regs->readPC();

	jalr.decode(testJump);
	jalr.execute();

	uint32_t res = regs->readPC();

	if (ePC != res || eRA != regs->read(rd)){
		printf("Negative displacement jump test failed. New PC 0x%X, expected 0x%X. RA value 0x%X, expected 0x%X", res, ePC, regs->read(rd), eRA);
		test_passed = -1;
		regs->print();
	}

	return test_passed;
};

int badJump(){
	int test_passed = 0;
	uint32_t testJump;
	uint8_t op = JALROP;
	uint8_t func3 = 1;
	uint8_t rs1 = 0x14;
	uint8_t rd = 0x12;
	uint16_t imm = 0xFF01;
	JALR jalr;

	testJump = (imm << 20) | (rs1 << 15) | (func3 << 12) | (rd << 7) | op;

	regs->write(rs1, 0x50);

	uint32_t ePC = regs->readPC();
	uint32_t eRA = regs->read(rd);

	jalr.decode(testJump);
	jalr.execute();

	uint32_t res = regs->readPC();

	if (ePC != res || eRA != regs->read(rd)){
		printf("Bad jump test failed. New PC 0x%X, expected 0x%X. RA value 0x%X, expected 0x%X", res, ePC, regs->read(rd), eRA);
		test_passed = -1;
		regs->print();
	}

	return test_passed;
};

int exitJump(){
	int test_passed = 0;
	uint32_t testJump;
	uint8_t op = JALROP;
	uint8_t func3 = 0;
	uint8_t rs1 = 0x00;
	uint8_t rd = ra;
	uint16_t imm = 0x0000;
	JALR jalr;

	testJump = (imm << 20) | (rs1 << 15) | (func3 << 12) | (rd << 7) | op;

	regs->write(rs1, 0x50);

	jalr.decode(testJump);
	jalr.execute();

	test_passed = -1;

	printf("Did not end simulation as expected. Fail. RD: %d, target: 0x%X", rd, regs->readPC());

	return test_passed;
};

int jalrTest(){
	int test_passed = 0;
	std::cout << "++++ Testing positive displacement jalr ++++" << std::endl;
	test_passed |= posJump();
	std::cout << "++++ Testing negative displacement jalr ++++" << std::endl;
	test_passed |= negJump();
	std::cout << "++++ Testing incorrectly encoded jalr ++++" << std::endl;
	test_passed |= badJump();
	std::cout << "++++ Testing jalr that should exit simulation ++++" << std::endl;
	test_passed |= badJump();
	return test_passed;
};
