#include "CodeAnalyser6502.h"
#include "../CodeAnalyser.h"

bool CheckPointerIndirectionInstruction6502(ICPUInterface* pCPUInterface, uint16_t pc, uint16_t* out_addr)
{
	const uint8_t instrByte = pCPUInterface->ReadByte(pc);

	switch (instrByte)
	{
	case 0x61:	// ADC (zp addr,X)
	case 0x71:	// ADC (zp addr),Y

	case 0xa1:	// LDA (zp addr,X)
	case 0xb1:	// LDA (zp addr),Y
	case 0x81:	// STA (zp addr,X)
	case 0x91:	// STA (zp addr),Y
		*out_addr = pCPUInterface->ReadByte(pc + 1);
	}
	return false;
}



bool CheckPointerRefInstruction6502(ICPUInterface* pCPUInterface, uint16_t pc, uint16_t* out_addr)
{
	const uint8_t instrByte = pCPUInterface->ReadByte(pc);

	switch (instrByte)
	{
		// full address
	case 0x6d:	// ADC <addr>
	case 0x7d:	// ADC <addr>,X
	case 0x79:	// ADC <addr>,Y
	case 0x2d:	// AND <addr>
	case 0x3d:	// AND <addr>,X
	case 0x39:	// AND <addr>,Y

	case 0xad:	// LDA <addr>
	case 0xbd:	// LDA <addr>,X
	case 0xb9:	// LDA <addr>,Y
	case 0xae:	// LDX <addr>
	case 0xbe:	// LDX <addr>,Y
	case 0xac:	// LDY <addr>
	case 0xbc:	// LDY <addr>,X

	case 0x8d:	// STA <addr>
	case 0x9d:	// STA <addr>,X
	case 0x99:	// STA <addr>,Y
	case 0x8e:	// STX <addr>
	case 0x8c:	// STY <addr>
		*out_addr = pCPUInterface->ReadWord(pc + 1);
		return true;

		// zero page
	case 0x65:	// ADC <zp addr>
	case 0x75:	// ADC <zp addr>,X
	case 0x25:	// AND <zp addr>
	case 0x35:	// AND <zp addr>,X
	
	case 0xa5:	// LDA <zp addr>
	case 0xb5:	// LDA <zp addr>,X
	case 0xa6:	// LDX <zp addr>
	case 0xb6:	// LDX <zp addr>,Y
	case 0xa4:	// LDY <zp addr>
	case 0xb4:	// LDY <zp addr>,X

	case 0x85:	// STA <zp addr>
	case 0x95:	// STA <zp addr>,X
	case 0x86:	// STX <zp addr>
	case 0x96:	// STX <zp addr>,Y
	case 0x84:	// STY <zp addr>
	case 0x94:	// STY <zp addr>,X
		*out_addr = pCPUInterface->ReadByte(pc + 1);
		return true;
	}
	return false;
}

bool CheckJumpInstruction6502(ICPUInterface* pCPUInterface, uint16_t pc, uint16_t* out_addr)
{
	const uint8_t instrByte = pCPUInterface->ReadByte(pc);

	switch (instrByte)
	{
		// to relative address
		case 0x10:	// BPL
		case 0x30:	// BMI
		case 0x50:	// BVC
		case 0x70:	// BVS
		case 0x90:	// BCC
		case 0x80:	// BCS
		case 0xD0:	// BNE
		case 0xF0:	// BEQ
		{
			const int8_t relJump = (int8_t)pCPUInterface->ReadByte(pc + 1);
			*out_addr = pc + 2 + relJump;	// +2 because it's relative to the next instruction
			return true;
		}
			
		// to absolute 16 address
		case 0x20:	// JSR
		case 0x4C:	// JMP abs
		case 0x6C:	// JMP indirect
			*out_addr = pCPUInterface->ReadWord(pc + 1);
			return true;
		//case 0x6C:	// JMP indirect
		//	*out_addr = pCPUInterface->ReadWord(pCPUInterface->ReadWord(pc + 1));
	//	return true;
	}
	return false;
}

bool CheckCallInstruction6502(ICPUInterface* pCPUInterface, uint16_t pc)
{
	const uint8_t instrByte = pCPUInterface->ReadByte(pc);

	switch (instrByte)
	{
	case 0x20:	// JSR
		return true;
	}
	return false;
}

bool CheckStopInstruction6502(ICPUInterface* pCPUInterface, uint16_t pc)
{
	const uint8_t instrByte = pCPUInterface->ReadByte(pc);

	switch (instrByte)
	{
	case 0x00:	// BRK
	case 0x20:	// JSR
	case 0x40:	// RTI
	case 0x60:	// RTS
		return true;
	}
	return false;
}