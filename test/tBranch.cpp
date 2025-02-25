#include <cstdio>
#include <memory>
#include <iostream>
#include <array>
#include "regfile.hpp"
#include "branch.hpp"
#include "processor.hpp"

extern std::unique_ptr<RegFile> regs;

constexpr int OPCODE = 0x63;
int branchCheck(int imm_u, int funct, int imm_l, std::array<int, 5> &expected) {
	int test_passed = 0;
	
	// Make instr
	
	// Iterate over array
	
	return test_passed;
}

int immCheck(int imm_u, int imm_l) {

}

int branch_t(void) {
	int test_passed = 0;
	int imm_u, val1, val2, funct, imm_l;
	std::array<int, 5> expected;

	// TEST for offset alignment
	// TEST for offset sign extension

	std::cout << "++++ Testing BRANCH BEQ ++++" << std::endl;
	// Set values
	
	// Call branchCheck
	test_passed |= branchCheck(imm_u, funct, imm_l, std::array<int, 5> &expected);

	// Repeat for each BRANCHOP

	return test_passed;
}
