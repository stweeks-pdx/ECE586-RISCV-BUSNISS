#include "memory.hpp"
#include <cstdio>
#include <iostream>
#include <fstream>

/* Memory Constructor
 *
 * Constructor for Memory 
 * Opens fileName and iterates through lines to populate memory
 *
 * Inputs:
 * string fileName - Name of the fileName to be loaded into memory
 */
Memory::Memory(std::string fileName) {
    std::ifstream f;
    std::string line, address, data;
    int i, j, k;
    f.open(fileName);
    if(!f.is_open()) {
        printf("Could not open file %s\n", fileName.c_str());
        abort();
    }
    while (std::getline(f, line)) {
        i = line.find(':');
        address = line.substr(0,i);
        j = line.find_first_of("0123456789abcdefABCDEF", i);
        k = line.find_last_of("0123456789abcdefABCDEF");
        data = line.substr(j, k-j+1);
    printf("Writing %s at %s\n", data.c_str(), address.c_str());    
        switch(data.size()){
            case(2):
        writeByte(std::stoul(address,0,16), std::stoul(data,0,16));
                break;
            case(NUMBYTESHWORD*2):
                writeHWord(std::stoul(address,0,16), std::stoul(data,0,16));
                break;               
            case(NUMBYTESWORD*2):
                writeWord(std::stoul(address,0,16), std::stoul(data,0,16));
                break;  
            default:
                printf("WARNING: Memory(): Invalid data length, %s not written to\n", address.c_str());
                break;
        }
    }
    f.close();
}

/* readByte
 *
 * Reads the byte at an address specified by a parameter
 *
 * Inputs:
 * uint32_t address - memory address to read from
 *
 * Outputs:
 * uint8_t of the value present at that address
 */
uint8_t Memory::readByte(uint32_t address) {
    return byteAtMemLoc[address];
}

/* readHword
 *
 * Reads the half-word at an address specified by a parameter
 *
 * Inputs:
 * uint32_t address - memory address to read from
 *
 * Outputs:
 * uint16_t of the value present at that address
 */
uint16_t Memory::readHWord(uint32_t address) {
    uint16_t halfword = 0;

    for (int i = NUMBYTESHWORD-1; i >= 0; i--)
        halfword |= (byteAtMemLoc[address+i] << (i*8));

    return halfword;
}

/* readWord
 *
 * Reads the word at an address specified by a parameter
 *
 * Inputs:
 * uint32_t address - memory address to read from
 *
 * Outputs:
 * uint32_t of the value present at that address
 */
uint32_t Memory::readWord(uint32_t address) {
    uint32_t word = 0;

    for (int i = NUMBYTESWORD-1; i >= 0; i--)
        word |= (byteAtMemLoc[address+i] << (i*8));

    return word;
}

/* writeByte
 *
 * Writes a byte to the intended memory address
 *
 * Inputs:
 * uint32_t address - memory location to write to
 * uint8_t val - value to write in memory location
 */
void Memory::writeByte(uint32_t address, uint8_t val) {
    byteAtMemLoc[address] = val;
}

/* writeHWord
 *
 * Writes a half-word to the intended memory address
 *
 * Inputs:
 * uint32_t address - memory location to write to
 * uint16_t val - value to write in memory location
 */
void Memory::writeHWord(uint32_t address, uint16_t val) {
    for (int i = 0; i < NUMBYTESHWORD; i++) {
        byteAtMemLoc[address+i] = (val >> i*8) & BYTEMASK;
    }
}

/* writeWord
 *
 * Writes a word to the intended memory address
 *
 * Inputs:
 * uint32_t address - memory location to write to
 * uint32_t val - value to write in memory location
 */
void Memory::writeWord(uint32_t address, uint32_t val) {
    for (int i = 0; i < NUMBYTESWORD; i++) {
        byteAtMemLoc[address+i] = (val >> i*8) & BYTEMASK;
    }
}

/* print(void)
 *
 * Prints the contents of all valid Memory addresses in bytes
 *
 */
void Memory::print(void) {
    for (uint32_t i = 0; i < STACKADDRESS; i++) {
        if (byteAtMemLoc.count(i)) printf("%08X: %02X\n", i, byteAtMemLoc[i]);
    }
}

/* print(char filler)
 *
 * Prints the contents of all word aligned memory addresses
 * Invalid locations are replaced with copies of filler char
 *
 * Inputs:
 * char filler - Character to use in place of invalid bytes 
 */
void Memory::print(char filler) {
    std::string output;
    bool partValid;
    std::string hex = "0123456789ABCDEF";
    uint8_t byte;
    for (uint32_t i = 0; i < STACKADDRESS; i+=4) {
	partValid = false;
	output.clear();
        for (int j = NUMBYTESWORD-1; j >= 0; j--){ 
            if (byteAtMemLoc.count(i+j)){
                byte = byteAtMemLoc[i+j];            
                output.append(1,hex[byte/0x10]);
                output.append(1,hex[byte%0x10]);
                partValid = true;
            } else {
                output.append(2,filler);
            }
	}
        if (partValid) printf("%08X: %s\n", i, output.c_str()); 
    }
}    
/* print(uint32_t start, uint32_t stop)
 *
 * Prints the contents of valid Memory addresses
 * between specified bounds from start to end-1
 *
 * Inputs:
 * uint32_t start - first address to print
 * uint32_t stop - stop address
 */
void Memory::print(uint32_t start, uint32_t stop) {
    for (uint32_t i = start; i < stop; i++) {
        if (byteAtMemLoc.count(i)) printf("%08X: %02X\n", i, byteAtMemLoc[i]);
    }
}
