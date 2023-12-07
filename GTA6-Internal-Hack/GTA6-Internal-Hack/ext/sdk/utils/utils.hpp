#pragma once
#include<cstdint>
#include<string>
namespace Utils
{
	__inline std::string add_strings(std::string str, std::string str2) {
		return str + str2;
	}
	__inline int RandIntSimple(int min, int max);
	__inline float sqrtf_(float x);
	__inline double powf_(double x, int y);
}