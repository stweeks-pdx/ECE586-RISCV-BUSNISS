#include "debug.hpp"
#include "memory.hpp"
#include "regfile.hpp"
#include <memory>
#include <iostream>

extern std::unique_ptr<RegFile> regs;
extern std::unique_ptr<Memory> mem;

void debugMode(void) {
	char input;
	bool run = true;
	const char step = 's';
	const char printRegs = 'r';
	const char printMem = 'm';
	const char printInst = 'i';
	const char help = 'h';

	while (run) {
            std::cout << "rdb> ";
	    std::cin >> input;
	    switch (input) {
		    case step:
			    run = false;
			    break;
		    case printRegs:
			    regs->print();
			    break;
		    case printMem:
			    mem->print('-');
			    break;
		    case printInst:
			    std::cout << "Instruction is: " << std::hex << mem->readWord((regs->readPC() - 4)) << std::endl;
			    break;
		    case help:
			    std::cout << "s -- step to next instruction" << std::endl;
			    std::cout << "r -- print register contents" << std::endl;
			    std::cout << "m -- print memory contents" << std::endl;
			    std::cout << "i -- print current instruction" << std::endl;
			    std::cout << "h -- help" << std::endl;
			    break;
		    default:
			    std::cout << "This is currently an unsupported instruction" << std::endl;
			    break;
	    }
	}
}
