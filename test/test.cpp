#include <cstdio>
#include <iostream>
#include "regfile.hpp"
#include "memory.hpp"
#include <memory>

int registers_t(void);

// These externs are needed for some source files that will be tested
// Placed here for now
uint32_t STACKADDRESS = 0x10080;
std::unique_ptr<RegFile> regs;
std::unique_ptr<Memory> mem;

int main() {
	int test_passed = 0;
	
	std::cout << "Running register file test" << std::endl;
	test_passed = registers_t();

	std::cout << "TEST " << ((test_passed == 0) ? "PASSED" : "FAILED") << std::endl;

	return test_passed;
}

