#include "regfile.hpp"
#include <string>
#include <cstdio>

static std::array<std::string, REGWIDTH> regAlias = {"zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
	"s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
	"s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};

/* RegFile Constructor
 *
 * Constructor for the register file that must take
 * a PC location and an stack pointer location
 *
 * Inputs:
 * uint32_t PCLoc - adds the PC location
 * uint32_t SPLoc - adds the stack pointer location
 *
 * Initializes the register array to 0 other than PC
 * and SP
 */
RegFile::RegFile(uint32_t PCLoc, uint32_t SPLoc) {
	registers.fill(0);
	registers[sp] = SPLoc;
	registers[PC] = PCLoc;
}

/* read
 *
 * Reads the register provided as a parameter
 *
 * Inputs:
 * uint8_t val - register to read from
 *
 * Outputs:
 * uint32_t of the value held in the register
 */
uint32_t RegFile::read(uint8_t val) {
	if (val > (REGWIDTH - 1)) return 0;
	else return registers[val];
}

/* write
 *
 * Writes to the intended register
 *
 * Inputs:
 * uint8_t idx - register to write to
 * uint32_t val - value to write in the register
 */
void RegFile::write(uint8_t idx, uint32_t val) {
	if ((idx == zero) || (idx > (REGWIDTH - 1))) return;
	registers[idx] = val;
}

/* updatePC
 *
 * Updates the Program Counter
 *
 * Inputs:
 * uint32_t val - value to update the PC with
 */
void RegFile::updatePC(uint32_t val) {
	registers[PC] = val;
}

/*readPC
 *
 * Reads the Program Counter
 *
 * Outputs:
 * uint32_t of the value stored in the PC
 */
uint32_t RegFile::readPC(void) {
	return registers[PC];
}

/* print
 *
 * Prints the contet of the register file
 *
 */
void RegFile::print(void) {
	printf("+++++ REGISTER FILE +++++\n");
	for (int i = 0; i < REGWIDTH; i++) {
		printf("%s \t(R%d): \t0x%x\n", regAlias[i].c_str(), i, registers[i]);
	}

	printf("==== PC is 0x%x ==== \n", registers[PC]);
}
