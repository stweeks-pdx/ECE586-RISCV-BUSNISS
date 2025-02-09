#ifndef _REGFILE_HPP_
#define _REGFILE_HPP_
#include <cstdint>
#include <array>

constexpr uint8_t PC = 32;
constexpr uint8_t zero = 0;
constexpr uint8_t ra = 1;
constexpr uint8_t sp = 2;
constexpr uint8_t gp = 3;
constexpr uint8_t tp = 4;
constexpr uint8_t fp = 8;
constexpr uint8_t REGWIDTH = 32;

class RegFile
{
	private:
		std::array<uint32_t, 33> registers;
	
	public:
		RegFile(uint32_t PCLoc, uint32_t SPLoc);
		uint32_t read(uint8_t val);
		void write(uint8_t idx, uint32_t val);
		void updatePC(uint32_t val);
		uint32_t readPC(void);
		void print(void);
};

#endif // _REGFILE_HPP_
