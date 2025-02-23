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

int aluAddi_t(void) {
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

int aluSlli_t(void) {
	int test_passed = 0;
	uint32_t eRes;
	uint32_t res;
	uint32_t instr;
	ALUI alui;

	// construct r6(3) << 4 = r11
	uint16_t imm = 0x4;
	uint8_t rs1 = 0x06;
	uint8_t f3 = SLLI;
	uint8_t rd = 0x0B;
	uint8_t op = ALUIOP;

	instr = constructInstr(imm, rs1, f3, rd, op);

	regs->write(rs1, 3);
	eRes = 3 << 4;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(3 << 4) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(-1) << 4 = r11
	regs->write(rs1, -1);
	eRes = (-1) << 4;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-1 << 4) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// shift all 0
	imm = 31;
	instr = constructInstr(imm, rs1, f3, rd, op);
	regs->write(rs1, -2);
	eRes = (-2) << 31;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-2 << 31) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	return test_passed;
}

int aluSlti_t(void) {
	int test_passed = 0;
	uint32_t eRes;
	uint32_t res;
	uint32_t instr;
	ALUI alui;

	// construct r6(1) < 2 = r11
	uint16_t imm = 0x2;
	uint8_t rs1 = 0x06;
	uint8_t f3 = SLTI;
	uint8_t rd = 0x0B;
	uint8_t op = ALUIOP;

	instr = constructInstr(imm, rs1, f3, rd, op);

	regs->write(rs1, 1);
	eRes = 1 < 2;
	
	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(1 < 2) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(3) < 2 = r11
	regs->write(rs1, 3);
	eRes = 3 < 2;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(3 < 2) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(-2) < 2 = r11
	regs->write(rs1, -2);
	eRes = (-2) < 2;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-2 < 2) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(1) < -3 = r11
	imm = -3;
	instr = constructInstr(imm, rs1, f3, rd, op);
	regs->write(rs1, 1);
	eRes = 1 < (-3);

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(1 < -3) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(-12) < -3 = r11
	regs->write(rs1, -12);
	eRes = (-12) < (-3);

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-12 < -3) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(-3) < -3 = r11
	regs->write(rs1, -3);
	eRes = (-3) < (-3);

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-3 < -3) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	return test_passed;
}

int aluSltiu_t(void) {
	int test_passed = 0;
	uint32_t eRes;
	uint32_t res;
	uint32_t instr;
	ALUI alui;

	// construct r6(1) < 2 = r11
	uint16_t imm = 0x2;
	uint8_t rs1 = 0x06;
	uint8_t f3 = SLTIU;
	uint8_t rd = 0x0B;
	uint8_t op = ALUIOP;

	instr = constructInstr(imm, rs1, f3, rd, op);

	regs->write(rs1, 1);
	eRes = 1 < 2;
	
	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(1 < 2) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(-1) < 2 = r11
	regs->write(rs1, -1);
	eRes = static_cast<uint32_t>(-1) < 2;
	
	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-1 < 2) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(1) < -2 = r11
	imm = -2;
	instr = constructInstr(imm, rs1, f3, rd, op);
	regs->write(rs1, 1);
	eRes = 1 < static_cast<uint32_t>(-2);
	
	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(1 < -2) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}
	
	// construct r6(-1) < -2 = r11
	regs->write(rs1, -1);
	eRes = static_cast<uint32_t>(-1) < static_cast<uint32_t>(-2);
	
	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-1 < -2) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// test SNEQZ
	imm = 1;
	instr = constructInstr(imm, rs1, f3, rd, op);
	regs->write(rs1, 0);
	eRes = 0 < 1;
	
	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(SNEQZ) failed: expected %d, got %d\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	return test_passed;
}

int aluXori_t(void) {
	int test_passed = 0;
	uint32_t eRes;
	uint32_t res;
	uint32_t instr;
	ALUI alui;

	// construct r6(2) ^ 3 = r11
	uint16_t imm = 0x3;
	uint8_t rs1 = 0x06;
	uint8_t f3 = XORI;
	uint8_t rd = 0x0B;
	uint8_t op = ALUIOP;

	instr = constructInstr(imm, rs1, f3, rd, op);

	regs->write(rs1, 0x02);
	eRes = 0x02 ^ 0x03;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(2 XOR 3) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(15) ^ 3 = r11
	regs->write(rs1, 0x0F);
	eRes = 0x0F ^ 0x03;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(15 XOR 3) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(5) ^ -1 = r11
	// (NOT operation)
	imm = -1;
	instr = constructInstr(imm, rs1, f3, rd, op);
	regs->write(rs1, 0x05);
	eRes = 0x05 ^ -1;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(NOT) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(-3) ^ -2 = r11
	imm = -2;
	instr = constructInstr(imm, rs1, f3, rd, op);
	regs->write(rs1, -3);
	eRes = -3 ^ -2;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-3 XOR -2) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(5) ^ -2 = r11
	regs->write(rs1, 0x05);
	eRes = 0x05 ^ -2;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(5 XOR -2) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	return test_passed;
}

int aluSrli_t(void) {
	int test_passed = 0;
	uint32_t eRes;
	uint32_t res;
	uint32_t instr;
	ALUI alui;

	// construct r6(16) >> 4 = r11
	uint16_t imm = 0x4;
	uint8_t rs1 = 0x06;
	uint8_t f3 = SRL_A_I;
	uint8_t rd = 0x0B;
	uint8_t op = ALUIOP;

	instr = constructInstr(imm, rs1, f3, rd, op);

	regs->write(rs1, 16);
	eRes = 16 >> 4;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(16 >> 4) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(-1) >> 4 = r11
	regs->write(rs1, -1);
	eRes = static_cast<uint32_t>(-1) >> 4;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-1 >> 4) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(-1) >> 31 = r11
	imm = 31;
	instr = constructInstr(imm, rs1, f3, rd, op);
	eRes = static_cast<uint32_t>(-1) >> 31;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-1 >> 31) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	return test_passed;
}

int aluSrai_t(void) {
	int test_passed = 0;
	uint32_t eRes;
	uint32_t res;
	uint32_t instr;
	ALUI alui;

	// construct r6(-32) >> 4 = r11
	uint16_t imm = 0x404; // need to set funct7 to 0x20
	uint8_t rs1 = 0x06;
	uint8_t f3 = SRL_A_I;
	uint8_t rd = 0x0B;
	uint8_t op = ALUIOP;

	instr = constructInstr(imm, rs1, f3, rd, op);

	regs->write(rs1, -32);
	eRes = static_cast<int32_t>(-32) >> 4;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("Arith(-32 >> 4) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(32) >> 4 = r11
	regs->write(rs1, 32);
	eRes = static_cast<int32_t>(32) >> 4;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("Arith(32 >> 4) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// shift all 1's
	imm = 0x41F; // need to set funct7 to 0x20
	instr = constructInstr(imm, rs1, f3, rd, op);
	regs->write(rs1, 0x80000000);
	eRes = static_cast<int32_t>(0x80000000) >> 31;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("Arith(0x80000000 >> 31) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// shift all 0's
	regs->write(rs1, 0x7FFFFFFF);
	eRes = static_cast<int32_t>(0x7FFFFFFF) >> 31;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("Arith(0x7FFFFFFF >> 31) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	return test_passed;
}

int aluOri_t(void) {
	int test_passed = 0;
	uint32_t eRes;
	uint32_t res;
	uint32_t instr;
	ALUI alui;

	// construct r6(5) | 3 = r11
	uint16_t imm = 0x03; 
	uint8_t rs1 = 0x06;
	uint8_t f3 = ORI;
	uint8_t rd = 0x0B;
	uint8_t op = ALUIOP;

	instr = constructInstr(imm, rs1, f3, rd, op);

	regs->write(rs1, 5);
	eRes = 0x05 | 0x03;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(5 OR 3) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(-16) | 3 = r11
	regs->write(rs1, -16);
	eRes = -16 | 0x03;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-16 OR 3) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(-16) | -1 = r11
	imm = -1;
	instr = constructInstr(imm, rs1, f3, rd, op);
	regs->write(rs1, -16);
	eRes = -16 | -1;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-16 OR -1) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(16) | 0 = r11
	imm = 0;
	instr = constructInstr(imm, rs1, f3, rd, op);
	regs->write(rs1, 16);
	eRes = 16 | 0;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(16 OR 0) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	return test_passed;
}

int aluAndi_t(void) {
	int test_passed = 0;
	uint32_t eRes;
	uint32_t res;
	uint32_t instr;
	ALUI alui;

	// construct r6(5) & 3 = r11
	uint16_t imm = 0x03; 
	uint8_t rs1 = 0x06;
	uint8_t f3 = ANDI;
	uint8_t rd = 0x0B;
	uint8_t op = ALUIOP;

	instr = constructInstr(imm, rs1, f3, rd, op);

	regs->write(rs1, 0x05);
	eRes = 5 & 3;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(5 AND 3) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	// construct r6(-2) & 3 = r11
	regs->write(rs1, -2);
	eRes = (-2) & 3;

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-2 AND 3) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}
	
	// construct r6(-2) & -4 = r11
	imm = -4;
	instr = constructInstr(imm, rs1, f3, rd, op);
	eRes = (-2) & (-4);

	alui.decode(instr);
	alui.execute();

	res = regs->read(rd);
	if (eRes != res) {
		printf("(-2 AND -4) failed: expected 0x%x, got 0x%x\n", eRes, res);
		test_passed = -1;
		regs->print();
	}

	return test_passed;
}

int alui_t(void) {
	int test_passed = 0;
	
	std::cout << "++++ Testing ALU ADDI ++++" << std::endl;
	test_passed |= aluAddi_t();

	std::cout << "++++ Testing ALU SLLI ++++" << std::endl;
	test_passed |= aluSlli_t();

	std::cout << "++++ Testing ALU SLTI ++++" << std::endl;
	test_passed |= aluSlti_t();

	std::cout << "++++ Testing ALU SLTIU ++++" << std::endl;
	test_passed |= aluSltiu_t();

	std::cout << "++++ Testing ALU XORI ++++" << std::endl;
	test_passed |= aluXori_t();

	std::cout << "++++ Testing ALU SRLI ++++" << std::endl;
	test_passed |= aluSrli_t();

	std::cout << "++++ Testing ALU SRAI ++++" << std::endl;
	test_passed |= aluSrai_t();

	std::cout << "++++ Testing ALU ORI ++++" << std::endl;
	test_passed |= aluOri_t();

	std::cout << "++++ Testing ALU ANDI ++++" << std::endl;
	test_passed |= aluAndi_t();	

	return test_passed;
}
