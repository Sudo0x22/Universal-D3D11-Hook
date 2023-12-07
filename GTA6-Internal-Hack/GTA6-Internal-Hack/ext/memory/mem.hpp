#pragma once
#include"thread/thread.hpp"
#include <string>

class Mem {
public:
	template<typename type>
	__inline type ReadProcMem(type base, type offset) {
		return *(type*)(base + offset);
	}
	template<typename type>
	__inline type WriteProcMem(type base, type offset, type value) {
		return *(type*)(base + offset) = value;
	}
public:
	template<typename type>
	__inline type FindAddress(type offset, std::vector<type> bytes) {
		type addr = offset;
		for (uint i = 0; i < bytes.size(); ++i) {
			addr = *(type*)addr;
			addr += bytes[i];
		}
		return addr;
	}

	struct MyStr64 {
		char readstr[32];
	};

	template<typename type>
	__inline type Read(uint64_t addr) {
		type Buffer{};
		return *(type*)(addr);
	}
	__inline std::string ReadString(uint64_t addr) {
		std::string result = Read<MyStr64>(addr).readstr;
		return result;
	}
}; Mem* pMem = new Mem();