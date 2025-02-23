#include <cstdio>
#include <iostream>
#include "regfile.hpp"
#include "memory.hpp"
#include <memory>

int registers_t(void);
int alu_t(void);
extern int branch_t(void);
int jal_t(void);
int jalrTest(void);
int alui_t(void);
int jal_t(void);
int jalrTest(void);
int alui_t(void);

// These externs are needed for some source files that will be tested
// Placed here for now
uint32_t STACKADDRESS = 0x10080;
uint32_t PROGRAMSTART = 0x00;
std::unique_ptr<RegFile> regs;
std::unique_ptr<Memory> mem;

int main() {
	int test_passed = 0;
	
	std::cout << "Running register file test" << std::endl;
	test_passed |= registers_t();
	
	// ALU Test
	std::cout << "Running ALU test" << std::endl;
	regs = std::make_unique<RegFile>(PROGRAMSTART, STACKADDRESS);
	test_passed |= alu_t();

	// Branch Test
	std::cout << "Running Branch test" << std::endl;
	test_passed |= branch_t();

	//JALR Test
	std::cout << "Running JALR op test" << std::endl;
	test_passed |= jalrTest();

	// ALUI Test
	// reset regs file
	regs->write(0x06, 0);
	regs->write(0x0B, 0);
	std::cout << "Running ALUI test" << std::endl;
	test_passed |= alui_t();

	// JAL Test
	std::cout << "Running JAL test" << std::endl;
	test_passed |= jal_t();

	//JALR Test
	std::cout << "Running JALR op test" << std::endl;
	test_passed |= jalrTest();

	// ALUI Test
	// reset regs file
	regs->write(0x06, 0);
	regs->write(0x0B, 0);
	std::cout << "Running ALUI test" << std::endl;
	test_passed |= alui_t();

	std::cout << "TEST " << ((test_passed == 0) ? "PASSED" : "FAILED") << std::endl;

	return test_passed;
}
