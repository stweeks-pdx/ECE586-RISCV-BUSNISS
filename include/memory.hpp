#ifndef _MEMFILE_HPP_
#define _MEMFILE_HPP_
#include <cstdint>
#include <unordered_map>
#include <string>

constexpr uint8_t NUMBYTESWORD = 4; 
constexpr uint8_t NUMBYTESHWORD = 2;
constexpr uint8_t BYTEMASK = 0xFF;
extern uint32_t STACKADDRESS;

class Memory
{
    private:
        std::unordered_map<uint32_t, uint8_t> byteAtMemLoc;
    
    public:
        Memory(std::string fileName);
        uint8_t readByte(uint32_t address);
        uint16_t readHWord(uint32_t address);
        uint32_t readWord(uint32_t address);
        void writeByte(uint32_t address, uint8_t val);
        void writeHWord(uint32_t address, uint16_t val);
        void writeWord(uint32_t address, uint32_t val);
        void print(void);
        void print(uint32_t start, uint32_t stop);
};

#endif // _MEMFILE_HPP_
