#include "regfile.hpp"
#include "alui.hpp"
#include "processor.hpp"
#include <cstdio>
#include <memory>
#include <iostream>

extern std::unique_ptr<RegFile> regs;

uint32_t constructInstr(uint16_t imm, uint8_t rs1, uint8_t f3, uint8_t rd, uint8_t op) {
	return ((imm << 20) | (rs1 << 15) | (f3 << 12) | (rd << 7) | op);
}

int aluAddI_t(void) {
	int test_passed = 0;
	uint32_t eRes;
	uint32_t res;
	uint32_t instr;
	ALUI alui;

	// construct r6(3) + 7 = r11
	uint16_t imm = 7;
	uint8_t rs1 = 0x06;
	uint8_t f3 = ADDI;
	uint8_t rd = 0x0B;
	uint8_t op = ALUIOP;

	instr = constructInstr(imm, rs1, f3, rd, op);

	regs->write(rs1, 3);
	eRes = 3 + 7;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(3+7) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(-8) + 7 = r11
	regs->write(rs1, -8);
	eRes = (-8) + 7;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-8+7) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(-7) + 7 = r11
	regs->write(rs1, -7);
	eRes = (-7) + 7;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-7+7) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(0) + 7 = r11
	regs->write(rs1, 0);
	eRes = 0 + 7;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(0+7) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(-16) + (-16) = r11
	imm = (-16);

	instr = constructInstr(imm, rs1, f3, rd, op);

	regs->write(rs1, -16);
	eRes = (-16) + (-16);

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-16+-16) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	return test_passed;
}

int alui_t(void) {
	int test_passed = 0;
	
	std::cout << "++++ Testing ALU ADDI ++++" << std::endl;
	test_passed |= aluAddI_t();

	return test_passed;
}
