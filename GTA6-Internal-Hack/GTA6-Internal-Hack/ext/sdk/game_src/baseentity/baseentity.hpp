#pragma once
#include"../offsets/offsets.hpp"

class BaseEntity {
public:
	__inline int m_iHealth() {
		return *(int*)(this + 0x100);
	}
	__inline int m_iArmor() {
		return *(int*)(this + 0x100);
	}
public:
	__inline std::string m_sName() {
		uintptr_t nameIndex = *(uintptr_t*)(this + 0x00);
		uintptr_t nameOffset = *(uintptr_t*)(pOffsets.module_base + 0x100 + ((nameIndex - 1) << 4));
		std::string entityName = pMem->ReadString(nameOffset);
		return entityName;
	}
};

BaseEntity* GetLocalPlayer() {
	return *(BaseEntity**)(pOffsets.module_base + 0x200);
}
BaseEntity* GetEntityList(uintptr_t index) {
	return *(BaseEntity**)(pOffsets.module_base + 0x300 + (index << 5));
}