#pragma once
#include<cstdint>
namespace decrypt
{
	using Fn = void(__fastcall*)(void*, void*);
	void __fastcall decrypt_offsets(void* rbx, void* rcx);
}