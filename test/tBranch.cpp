#include <cstdio>
#include <memory>
#include <iostream>
#include <array>
#include "regfile.hpp"
#include "branch.hpp"
#include "processor.hpp"

extern std::unique_ptr<RegFile> regs;

constexpr int OPCODE = 0x63;
constexpr std::array<int,5> tVal1 = {1, 2, 0, -2, 1};
constexpr std::array<int,5> tVal2 = {2, 1, 0, 1, -2};

int branchCheck(int funct, std::array<int, 5> &expected) {
	int test_passed = 0;
	BRANCH branch;
	uint32_t target = 0x00000AAC;

	int imm_u = 0x15;
	int imm_l = 0x0D;
	int rs1 = 4;
	int rs2 = 5;

	// Make instr
	uint32_t instr = (imm_u << 25) | (rs2 << 20) | (rs1 << 15) | (funct << 12) | (imm_l << 7) | (OPCODE);

	// Iterate over array
	for (int i = 0; i < 5; i++) {
		regs->updatePC(0x00000004);
		regs->write(rs1, tVal1[i]);
		regs->write(rs2, tVal2[i]);
		
		branch.decode(instr);
		branch.execute();
		
		if ((regs->readPC() == target) != expected[i]) test_passed |= -1;
#ifdef DEBUG
		std::cout << "PC after branch: " << std::hex << regs->readPC() << std::endl;
#endif
	}


	return test_passed;
}

int immCheck(void) {
	int test_passed = 0;
	BRANCH branch;
	int val = 1;
	int funct = 0b000;
	uint32_t target, instr;
	int imm_u, imm_l;
	int rs1 = 4;
	int rs2 = 5;
	
	regs->write(rs1, val);
	regs->write(rs2, val);

	// TEST: Checking for sign extension
	target = 0xFFFFFFFC;
	imm_u = 0x7F;
	imm_l = 0x1D;
	
	// Make 2nd instr
	instr = (imm_u << 25) | (rs2 << 20) | (rs1 << 15) | (funct << 12) | (imm_l << 7) | (OPCODE);

	regs->updatePC(0x00000004);
	
	branch.decode(instr);
	branch.execute();
	
	if (regs->readPC() != target) test_passed |= -1;
#ifdef DEBUG
	std::cout << "PC after branch: " << std::hex << regs->readPC() << std::endl;
#endif

	return test_passed;
}

int branch_t(void) {
	int test_passed = 0;
	int funct;
	std::array<int, 5> expected;

	std::cout << "++++ Testing BRANCH imm. sign extention ++++" << std::endl;
	test_passed |= immCheck();


	std::cout << "++++ Testing BRANCH BEQ ++++" << std::endl;
	// Set values
	funct = 0b000;
	expected = {0, 0, 1, 0, 0};

	// Call branchCheck
	test_passed |= branchCheck(funct, expected);


	std::cout << "++++ Testing BRANCH BNE ++++" << std::endl;
	// Set values
	funct = 0b001;
	expected = {1, 1, 0, 1, 1};

	// Call branchCheck
	test_passed |= branchCheck(funct, expected);


	std::cout << "++++ Testing BRANCH BLT ++++" << std::endl;
	// Set values
	funct = 0b100;
	expected = {1, 0, 0, 1, 0};

	// Call branchCheck
	test_passed |= branchCheck(funct, expected);


	std::cout << "++++ Testing BRANCH BGE ++++" << std::endl;
	// Set values
	funct = 0b101;
	expected = {0, 1, 1, 0, 1};

	// Call branchCheck
	test_passed |= branchCheck(funct, expected);


	std::cout << "++++ Testing BRANCH BLTU ++++" << std::endl;
	// Set values
	funct = 0b110;
	expected = {1, 0, 0, 0, 1};

	// Call branchCheck
	test_passed |= branchCheck(funct, expected);


	std::cout << "++++ Testing BRANCH BGEU ++++" << std::endl;
	// Set values
	funct = 0b111;
	expected = {0, 1, 1, 1, 0};

	// Call branchCheck
	test_passed |= branchCheck(funct, expected);

	return test_passed;
}
