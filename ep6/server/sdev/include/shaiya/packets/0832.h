#pragma once
#include <shaiya/common.h>

namespace shaiya
{
#pragma pack(push, 1)
	struct ResultPacket {
		WORD opcode; // 0x0832
		BYTE result = 0x01;
	};
#pragma pack(pop)
}
