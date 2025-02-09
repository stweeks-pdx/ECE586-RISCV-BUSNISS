#include <cstdio>
#include <iostream>
#include "regfile.hpp"

int registers_t(void);

int main() {
	int test_passed = 0;
	
	std::cout << "Running register file test" << std::endl;
	test_passed = registers_t();

	std::cout << "TEST " << ((test_passed == 0) ? "PASSED" : "FAILED") << std::endl;

	return test_passed;
}

