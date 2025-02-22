#include <cstdio>
#include <memory>
#include <iostream>
#include "regfile.hpp"
#include "alu.hpp"
#include "processor.hpp"

extern std::unique_ptr<RegFile> regs;

int aluAdd_t(void) {
	int test_passed = 0;
	uint32_t eRes;
	uint32_t res;
	ALU alu;

	// Construct r5 + r7 = r10
	uint8_t rs1 = 0x05;
	uint8_t rs2 = 0x07;
	uint8_t rd = 0x0A;
	uint8_t op = ALUOP;
	uint8_t f3 = ADD_SUB;
	uint8_t f7 = 0x00;

	uint32_t instr = (f7 << 25) | (rs2 << 20) | (rs1 << 15) | (f3 << 12) | (rd << 7) | op;
	
	// add values to rs2 and rs1
	regs->write(rs1, 10);
	regs->write(rs2, 5);
	eRes = 10 + 5;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("Add(10+5) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// add 5 + -5
	regs->write(rs1, -5);
	eRes = 5 + (-5);

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("Add(5 + -5) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// add 5 + -4
	regs->write(rs1, -4);
	eRes = 5 + (-4);

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("Add(5 + -4) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// add -5 + -7
	regs->write(rs1, -7);
	regs->write(rs2, -5);
	eRes = (-5) + (-7);

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("Add(-5 + -7) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// add 5 + 0
	regs->write(rs1, 0);
	regs->write(rs2, 5);
	eRes = 5 + 0;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("Add(5 + 0) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	

	return test_passed;
}

int aluSub_t(void) {
	int test_passed = 0;
	uint32_t eRes;
	uint32_t res;
	ALU alu;

	// construct r11 = r28 - r30;
	uint8_t rs1 = 0x1C;
	uint8_t rs2 = 0x1E;
	uint8_t rd = 0x0B;
	uint8_t op = ALUOP;
	uint8_t f3 = ADD_SUB;
	uint8_t f7 = 0x20;

	uint32_t instr = (f7 << 25) | (rs2 << 20) | (rs1 << 15) | (f3 << 12) | (rd << 7) | op;
	
	// sbu 5 - (-5)
	regs->write(rs1, 5);
	regs->write(rs2, -5);
	eRes = 5 - (-5);

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("Sub(5 - (-5)) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// sub 0 - (-5)
	regs->write(rs1, 0);
	regs->write(rs2, -5);
	eRes = 0 - (-5);

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("Sub(0 - (-5)) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// sub 5 - 0
	regs->write(rs1, 5);
	regs->write(rs2, 0);
	eRes = 5 - 0;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("Sub(5 - 0) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// sub 7 - 5
	regs->write(rs1, 7);
	regs->write(rs2, 5);
	eRes = 7 - 5;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("Sub(7 - 5) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}


	// sub 4 - 13
	regs->write(rs1, 4);
	regs->write(rs2, 13);
	eRes = 4 - 13;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("Sub(4 - 13) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// sub -9 - 8
	regs->write(rs1, -9);
	regs->write(rs2, 8);
	eRes = -9 - 8;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("Sub(-9 - 8) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}


	return test_passed;
}

int aluSll_t(void) {
	int test_passed = 0;
	uint32_t eRes = 0;
	uint32_t res = 0;
	ALU alu;

	// construct r7 = r5 <<  r6;
	uint8_t rs1 = 0x05;
	uint8_t rs2 = 0x06;
	uint8_t rd = 0x07;
	uint8_t op = ALUOP;
	uint8_t f3 = SLL;
	uint8_t f7 = 0x00;

	uint32_t instr = (f7 << 25) | (rs2 << 20) | (rs1 << 15) | (f3 << 12) | (rd << 7) | op;

	// 6 << 7
	regs->write(rs1, 6);
	regs->write(rs2, 7);
	eRes = 6 << 7;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(6 << 7) failed: expected %b, got %b\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// -2 << 8
	regs->write(rs1, -2);
	regs->write(rs2, 8);
	eRes = (-2) << 8;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-2 << 8) failed: expected %b, got %b\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// 3 << 1 because we only take lower 5 bits
	regs->write(rs1, 3);
	regs->write(rs2, 33);
	eRes = 3 << 1;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(3 << 1) failed: expected %b, got %b\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// -3 << 0
	regs->write(rs1, -3);
	regs->write(rs2, 0);
	eRes = -3 << 0;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-3 << 1) failed: expected %b, got %b\n", eRes, res);
		test_passed = -1;
		regs->print();
	}


	return test_passed;
}

int aluSlt_t(void) {
	int test_passed = 0;
	bool eRes;
	bool res;
	ALU alu;

	// construct r7 = r5 <  r6;
	uint8_t rs1 = 0x05;
	uint8_t rs2 = 0x06;
	uint8_t rd = 0x07;
	uint8_t op = ALUOP;
	uint8_t f3 = SLT;
	uint8_t f7 = 0x00;

	uint32_t instr = (f7 << 25) | (rs2 << 20) | (rs1 << 15) | (f3 << 12) | (rd << 7) | op;

	// 1 < 2
	regs->write(rs1, 1);
	regs->write(rs2, 2);
	eRes = (1 < 2);

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(1 < 2) failed: expected %b, got %b\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// 2 < 1
	regs->write(rs1, 2);
	regs->write(rs2, 1);
	eRes = (2 < 1);

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(2 < 1) failed: expected %b, got %b\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// 2 < 2
	regs->write(rs1, 2);
	regs->write(rs2, 2);
	eRes = (2 < 2);

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(2 < 2) failed: expected %b, got %b\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// -3 < 2
	regs->write(rs1, -3);
	regs->write(rs2, 2);
	eRes = ((-3) < 2);

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-3 < 2) failed: expected %b, got %b\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// -4 < -5
	regs->write(rs1, -4);
	regs->write(rs2, -5);
	eRes = ((-4) < (-5));

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-4 < -5) failed: expected %b, got %b\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// -4 < 0
	regs->write(rs1, -4);
	regs->write(rs2, 0);
	eRes = ((-4) < 0);

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-4 < 0) failed: expected %b, got %b\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	return test_passed;
}

int aluSltu_t(void) {
	int test_passed = 0;
	bool eRes;
	bool res;
	ALU alu;

	// construct r7 = r5 <  r6;
	uint8_t rs1 = 0x05;
	uint8_t rs2 = 0x06;
	uint8_t rd = 0x07;
	uint8_t op = ALUOP;
	uint8_t f3 = SLTU;
	uint8_t f7 = 0x00;

	uint32_t instr = (f7 << 25) | (rs2 << 20) | (rs1 << 15) | (f3 << 12) | (rd << 7) | op;

	// -5 < 3 (should result in false since it is unsigned)
	regs->write(rs1, -5);
	regs->write(rs2, 3);
	eRes = (static_cast<uint32_t>(-5) < 3);

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-5 < 3) failed: expected %b, got %b\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// -4 < -1 (should result in true since it is unsigned)
	regs->write(rs1, -4);
	regs->write(rs2, -1);
	eRes = (static_cast<uint32_t>(-4) < static_cast<uint32_t>(-1));

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-4 < -1) failed: expected %b, got %b\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// 4 < 2
	regs->write(rs1, 4);
	regs->write(rs2, 2);
	eRes = (4 < 2);

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(4 < 2) failed: expected %b, got %b\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// 2 < 7
	regs->write(rs1, 2);
	regs->write(rs2, 7);
	eRes = (2 < 7);

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(2 < 7) failed: expected %b, got %b\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// special zero case
	instr = (f7 << 25) | (rs2 << 20) | (zero << 15) | (f3 << 12) | (rd << 7) | op;

	regs->write(rs2, -5);
	eRes = ((regs->read(rs2)) != 0);

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("Special case where rs2 = %d failed: expected %b, go %b\n",
				regs->read(rs2), eRes, res);
		test_passed = -1;
		regs->print();
	}

	regs->write(rs2, 0);
	eRes = ((regs->read(rs2)) != 0);

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("Special case where rs2 = %d failed: expected %b, go %b\n",
				regs->read(rs2), eRes, res);
		test_passed = -1;
		regs->print();
	}

	return test_passed;
}

int aluXor_t(void) {
	int test_passed = 0;
	uint32_t eRes;
	uint32_t res;
	ALU alu;

	// construct r7 = r5 XOR r6;
	uint8_t rs1 = 0x05;
	uint8_t rs2 = 0x06;
	uint8_t rd = 0x07;
	uint8_t op = ALUOP;
	uint8_t f3 = XOR;
	uint8_t f7 = 0x00;

	uint32_t instr = (f7 << 25) | (rs2 << 20) | (rs1 << 15) | (f3 << 12) | (rd << 7) | op;
	
	// 15 ^ 130
	regs->write(rs1, 15);
	regs->write(rs2, 130);
	eRes = 15 ^ 130;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(15 xor 130) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// -32 ^ -170
	regs->write(rs1, -32);
	regs->write(rs2, -170);
	eRes = static_cast<int32_t>(-32) ^ static_cast<int32_t>(-170);

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-32 xor -170) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// -18 ^ 47
	regs->write(rs1, -18);
	regs->write(rs2, 47);
	eRes = static_cast<int32_t>(-18) ^ static_cast<int32_t>(47);

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-18 xor 47) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}
	
	return test_passed;
}

int aluSrl_t(void) {
	int test_passed = 0;
	uint32_t eRes;
	uint32_t res;
	ALU alu;

	// construct r7 = r5 >> r6;
	uint8_t rs1 = 0x05;
	uint8_t rs2 = 0x06;
	uint8_t rd = 0x07;
	uint8_t op = ALUOP;
	uint8_t f3 = SRL_A;
	uint8_t f7 = 0x00;

	uint32_t instr = (f7 << 25) | (rs2 << 20) | (rs1 << 15) | (f3 << 12) | (rd << 7) | op;

	// 16 >> 2
	regs->write(rs1, 16);
	regs->write(rs2, 2);
	eRes = 16 >> 2;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(16 >> 2) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// -1 >> 4
	regs->write(rs1, -1);
	regs->write(rs2, 4);
	eRes = static_cast<uint32_t>(-1) >> 4;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-1 >> 4) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// 32 >> 34 (which is by 2 with the lower 5 registers)
	regs->write(rs1, 32);
	regs->write(rs2, 34);
	eRes = 32 >> 2;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-1 >> 4) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	return test_passed;
}

int aluSra_t(void) {
	int test_passed = 0;
	uint32_t eRes;
	uint32_t res;
	ALU alu;

	// construct r7 = r5 >> r6;
	uint8_t rs1 = 0x05;
	uint8_t rs2 = 0x06;
	uint8_t rd = 0x07;
	uint8_t op = ALUOP;
	uint8_t f3 = SRL_A;
	uint8_t f7 = 0x20;

	uint32_t instr = (f7 << 25) | (rs2 << 20) | (rs1 << 15) | (f3 << 12) | (rd << 7) | op;

	// -8 >> 2
	regs->write(rs1, -8);
	regs->write(rs2, 2);
	eRes = static_cast<int32_t>(-8) >> 2;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("Arith(-8 >> 2) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// 32 >> 4
	regs->write(rs1, 32);
	regs->write(rs2, 4);
	eRes = 32 >> 4;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("Arith(32 >> 4) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// -16 >> 34 (which is shift by 2 with the lower five registers)
	regs->write(rs1, -16);
	regs->write(rs2, 34);
	eRes = ~(16 >> 2) + 1;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("Arith(-8 >> 2) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	return test_passed;
}

int aluOr_t(void) {
	int test_passed = 0;
	uint32_t eRes;
	uint32_t res;
	ALU alu;

	// construct r7 = r5 OR r6;
	uint8_t rs1 = 0x05;
	uint8_t rs2 = 0x06;
	uint8_t rd = 0x07;
	uint8_t op = ALUOP;
	uint8_t f3 = OR;
	uint8_t f7 = 0x00;

	uint32_t instr = (f7 << 25) | (rs2 << 20) | (rs1 << 15) | (f3 << 12) | (rd << 7) | op;

	// 10 | 32
	regs->write(rs1, 10);
	regs->write(rs2, 32);
	eRes = 10 | 32;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(10 or 32) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// -16 | 3
	regs->write(rs1, -16);
	regs->write(rs2, 3);
	eRes = -16 | 3;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-16 or 3) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// -256 | -16
	regs->write(rs1, -256);
	regs->write(rs2, -16);
	eRes = -16 | -256;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-256 or -16) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	return test_passed;
}

int aluAnd_t(void) {
	int test_passed = 0;
	uint32_t eRes;
	uint32_t res;
	ALU alu;

	// construct r7 = r5 AND r6;
	uint8_t rs1 = 0x05;
	uint8_t rs2 = 0x06;
	uint8_t rd = 0x07;
	uint8_t op = ALUOP;
	uint8_t f3 = AND;
	uint8_t f7 = 0x00;

	uint32_t instr = (f7 << 25) | (rs2 << 20) | (rs1 << 15) | (f3 << 12) | (rd << 7) | op;

	// 5 & 4
	regs->write(rs1, 5);
	regs->write(rs2, 4);
	eRes = 5 & 4;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(5 and 4) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// -1 & 7
	regs->write(rs1, -1);
	regs->write(rs2, 7);
	eRes = -1 & 7;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-1 and 7) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// -256 & -2
	regs->write(rs1, -256);
	regs->write(rs2, -2);
	eRes = -256 & -2;

	alu.decode(instr);
	alu.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-256 and -2) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}
	
	return test_passed;
}

int alu_t(void) {
	int test_passed = 0;
	std::cout << "++++ Testing ALU ADD ++++" << std::endl;
	test_passed |= aluAdd_t();

	std::cout << "++++ Testing ALU SUB ++++" << std::endl;
	test_passed |= aluSub_t();

	std::cout << "++++ Testing ALU SLL ++++" <<std::endl;
	test_passed |= aluSll_t();

	std::cout << "++++ Testing ALU SLT ++++" <<std::endl;
	test_passed |= aluSlt_t();

	std::cout << "++++ Testing ALU SLTU ++++" << std::endl;
	test_passed |= aluSltu_t();

	std::cout << "++++ Testing ALU XOR ++++" << std::endl;
	test_passed |= aluXor_t();

	std::cout << "++++ Testing ALU SRL ++++" << std::endl;
	test_passed |= aluSrl_t();

	std::cout << "++++ Testing ALU SRA ++++" << std::endl;
	test_passed |= aluSra_t();

	std::cout << "++++ Testing ALU OR ++++" << std::endl;
	test_passed |= aluOr_t();

	std::cout << "++++ Testing ALU AND ++++" << std::endl;
	test_passed |= aluAnd_t();

	return test_passed;
}

