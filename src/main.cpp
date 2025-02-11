#include "regfile.hpp"
#include "memory.hpp"
#include "processor.hpp"
#include <cstdio>
#include <getopt.h>
#include <string>
#include <memory>

bool verboseMode = false;
uint32_t PROGRAMSTART = 0;
uint32_t STACKADDRESS = 65536;
std::string fileName = ".//images//program.mem";

std::unique_ptr<RegFile> regs;
std::unique_ptr<Memory> mem;

int main(int argc, char *argv[]) {
    // read and interprete CLI
    int c;
    // Parse arguments
    while((c = getopt(argc, argv, "vf:p:s:h")) != -1){
        switch(c){
            case 'v':
                verboseMode = true;
                break;
            case 'f':
                fileName = optarg;
                break;
            case 'p':
                PROGRAMSTART = std::stoul(optarg, 0, 16);
                break;
            case 's': 
                STACKADDRESS = std::stoul(optarg, 0, 16);
                break;
            case 'h':
                printf("Options for the program are:\n");
                printf("v -- Verbose mode\n");
                printf("p -- Program starting address\n");
                printf("s -- Starting stack address\n");
                printf("f -- program.mem to be run by the simulator\n");
                printf("Example: ./bin/rvsim -f <filename> -s 2048 -p 1024\n");
                return 0;
            case '?':
                if(isprint(optopt))
                    printf ("Unknown option `-%c'.\n", optopt);
                else
                    printf ("Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                abort();
        }
    }

    // initialize register singleton
    regs = std::make_unique<RegFile>(PROGRAMSTART, STACKADDRESS);
    
    // initialize memory singleton
    mem = std::make_unique<Memory>(fileName);

#ifdef DEBUG    
    printf("Verbose mode = %b\tFileName = %s\tProg = 0x%x\tStack = 0x%x\n", verboseMode, fileName.c_str(), PROGRAMSTART, STACKADDRESS);
#endif

    while(1){
    fetch();
    }

    // program exit point
    return 0;
}
