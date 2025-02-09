#include <cstdio>
#include "regfile.hpp"

int registers_t(void) {
	int test_passed = 0;
	uint32_t program_counter = 0;
	uint32_t stack_pointer = 0x1000;

	RegFile testReg(program_counter, stack_pointer);

	printf("++++++ Testing Reg Print ++++++\n");
	testReg.print();

	printf("+++++ Testing Reg write/read ++++++\n");
	for (uint32_t i = 0; i < REGWIDTH; i++) {
		testReg.write(i, i);
	}

	for (uint32_t i = 0; i < REGWIDTH; i++) {
		if (testReg.read(i) != i) {
			printf("Incorrect value for reg[%d]. Expected: 0x%x Got: 0x%x \n",
					i, i, testReg.read(i));
			test_passed = -1;
		}
	}
	
	printf("++++++ Testing Zero Register ++++++\n");
	testReg.write(zero, 0x100);
	if (testReg.read(zero) != 0) {
		printf("Zero register failed. Expected: 0, Got: 0x%x\n",
				testReg.read(zero));
		test_passed = -1;
	}

	printf("++++++ Test updading and reading PC ++++++\n");
	program_counter = 0x3000;
	testReg.updatePC(0x3000);
	if (testReg.readPC() != 0x3000) {
		printf("PC update failed! Expected: 0x%x Got: 0x%x\n",
				program_counter, testReg.readPC());
		test_passed = -1;
	}

	printf("++++++ Make sure we can't write to PC through base interface ++++++\n");
	program_counter = 0x4000;
	testReg.write(PC, program_counter);
	if (testReg.readPC() == program_counter) {
		printf("We should not be writing to the program counter through the generic interface!\n");
		test_passed = -1;
	}

	return test_passed;

}
