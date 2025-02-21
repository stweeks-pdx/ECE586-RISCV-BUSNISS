#ifndef _PROCESSOR_HPP_
#define _PROCESSOR_HPP_
#include <cstdio>
#include <cstdint>
//Masks for bit field
constexpr uint32_t OPCODEMASK = 0x0000007F;
//Instruction types
constexpr uint8_t ALUOP    = 0x33;
constexpr uint8_t ALUIOP   = 0x13;
constexpr uint8_t STOREOP  = 0x23;
constexpr uint8_t LOADOP   = 0x03;
constexpr uint8_t BRANCHOP = 0x63;
constexpr uint8_t LUIOP    = 0x37;
constexpr uint8_t AUIPCOP  = 0x17;
constexpr uint8_t JALOP    = 0x6F;
constexpr uint8_t JALROP   = 0x67;
//Funct3 codes
//Funct7 codes

void fetch(bool verboseMode);
void constructMap(void);

#endif //_PROCESSOR_HPP_
