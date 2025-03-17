#include "debug.hpp"
#include "memory.hpp"
#include "regfile.hpp"
#include <memory>
#include <iostream>

extern std::unique_ptr<RegFile> regs;
extern std::unique_ptr<Memory> mem;
extern bool breakpoints;

void debugMode(void) {
	char input;
	bool run = true;
	const char step = 's';
	const char next = 'n';
	const char pc = 'p';
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
            		    breakpoints = false;
			    break;
            	    case next:
                    	    run = false;
           		    breakpoints = true;
	                    break;
	    	    case pc:
		  	    std::cout << "PC is " << std::hex << regs->readPC() << std::endl;
			    break;
		    case printRegs:
			    regs->print();
			    break;
		    case printMem:
			    mem->print('-');
			    break;
		    case printInst:
			    std::cout << "Instruction is: " << std::hex << mem->readWord((regs->readPC())) << std::endl;
			    break;
		    case help:
			    std::cout << "s -- step to next instruction" << std::endl;
                	    std::cout << "n -- skip to the next breakpoint" << std::endl;
		  	    std::cout << "p -- print PC reg contents" << std::endl;
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
