//////////////////////////////////////////////////////////////////////////////
//
//	Module:		detours.lib
//  File:		disasm.cpp
//
//	Detours for binary functions.  Version 1.5 (Build 46)
//  Includes support for all x86 chips prior to the Pentium III.
//
//	Copyright 1999-2001, Microsoft Corporation
//

#include <ole2.h>
#include <imagehlp.h>
#include "detours.h"
#include "disasm.h"

#undef ASSERT
#define ASSERT(x)

//////////////////////////////////////////////////////////////////////////////
//
//  Function:
//      DetourCopyInstruction(PBYTE pbDst, PBYTE pbSrc, PBYTE *ppbTarget)
//  Purpose:
//      Copy a single instruction from pbSrc to pbDst.
//  Arguments:
//      pbDst:
//          Destination address for the instruction.  May be NULL in which
//          case DetourCopyInstruction is used to measure an instruction.
//          If not NULL then the source instruction is copied to the
//          destination instruction and any relative arguments are adjusted.
//      pbSrc:
//          Source address of the instruction.
//      ppbTarget:
//          Out parameter for any target instruction address pointed to by
//          the instruction.  For example, a branch or a jump insruction has
//          a target, but a load or store instruction doesn't.  A target is
//          another instruction that may be executed as a result of this
//          instruction.  ppbTarget may be NULL.
//		plExtra:
//			Out parameter for the number of extra bytes needed by the
//			instruction to reach the target.  For example, lExtra = 3 if the
//			instruction had an 8-bit relative offset, but needs a 32-bit
//			relative offset.
//  Returns:
//      Returns the address of the next instruction (following in the source)
//      instruction.  By subtracting pbSrc from the return value, the caller
//      can determinte the size of the instruction copied.
//  Comments:
//      By following the pbTarget, the caller can follow alternate
//      instruction streams.  However, it is not always possible to determine
//      the target based on static analysis.  For example, the destination of
//      a jump relative to a register cannot be determined from just the
//      instruction stream.  The output value, pbTarget, can have any of the
//      following outputs:
//			DETOUR_INSTRUCTION_TARGET_NONE:
//          	The instruction has no targets.
//			DETOUR_INSTRUCTION_TARGET_DYNAMIC:
//          	The instruction has a non-deterministic (dynamic) target.
//				(i.e. the jump is to an address held in a register.)
//          Address:   The instruction has the specified target.
//
//      When copying instructions, DetourCopyInstruction insures that any
//      targets remain constant.  It does so by adjusting any IP relative
//      offsets.
//

PBYTE WINAPI DetourCopyInstructionEx(PBYTE pbDst,
	PBYTE pbSrc,
	PBYTE* ppbTarget,
	LONG* plExtra)
{
	CDetourDis oDetourDisasm(ppbTarget, plExtra);
	return oDetourDisasm.CopyInstruction(pbDst, pbSrc);
}
extern "C"
PBYTE WINAPI DetourCopyInstruction(PBYTE pbDst, PBYTE pbSrc, PBYTE * ppbTarget)
{
	CDetourDis oDetourDisasm(ppbTarget, NULL);
	return oDetourDisasm.CopyInstruction(pbDst, pbSrc);
}

/////////////////////////////////////////////////////////// Disassembler Code.
//
CDetourDis::CDetourDis(PBYTE* ppbTarget, LONG* plExtra)
{
	Set32BitOperand();
	Set32BitAddress();

	m_ppbTarget = ppbTarget ? ppbTarget : &m_pbScratchTarget;
	m_plExtra = plExtra ? plExtra : &m_lScratchExtra;

	*m_ppbTarget = DETOUR_INSTRUCTION_TARGET_NONE;
	*m_plExtra = 0;
}

VOID CDetourDis::Set16BitOperand()
{
	m_b16BitOperand = TRUE;
}

VOID CDetourDis::Set32BitOperand()
{
	m_b16BitOperand = FALSE;
}

VOID CDetourDis::Set16BitAddress()
{
	m_b16BitAddress = TRUE;
}

VOID CDetourDis::Set32BitAddress()
{
	m_b16BitAddress = FALSE;
}

PBYTE CDetourDis::CopyInstruction(PBYTE pbDst, PBYTE pbSrc)
{
	// Configure scratch areas if real areas are not available.
	if (NULL == pbDst) {
		pbDst = m_rbScratchDst;
	}
	if (NULL == pbSrc) {
		// We can't copy a non-existent instruction.
		SetLastError(ERROR_INVALID_DATA);
		return NULL;
	}

	// Figure out how big the instruction is, do the appropriate copy,
	// and figure out what the target of the instruction is if any.
	//
	REFCOPYENTRY pEntry = &s_rceCopyTable[pbSrc[0]];
	return (this->*pEntry->pfCopy)(pEntry, pbDst, pbSrc);
}

PBYTE CDetourDis::CopyBytes(REFCOPYENTRY pEntry, PBYTE pbDst, PBYTE pbSrc)
{
	LONG nBytesFixed = (pEntry->nFlagBits & ADDRESS)
		? (m_b16BitAddress ? pEntry->nFixedSize16 : pEntry->nFixedSize)
		: (m_b16BitOperand ? pEntry->nFixedSize16 : pEntry->nFixedSize);
	LONG nBytes = nBytesFixed;
	if (pEntry->nModOffset > 0) {
		BYTE bModRm = pbSrc[pEntry->nModOffset];
		BYTE bFlags = s_rbModRm[bModRm];

		if (bFlags & SIB) {
			BYTE bSib = pbSrc[pEntry->nModOffset + 1];

			if ((bSib & 0x07) == 0x05) {
				if ((bModRm & 0xc0) == 0x00) {
					nBytes += 4;
				}
				else if ((bModRm & 0xc0) == 0x40) {
					nBytes += 1;
				}
				else if ((bModRm & 0xc0) == 0x80) {
					nBytes += 4;
				}
			}
		}
		nBytes += bFlags & NOTSIB;
	}
	CopyMemory(pbDst, pbSrc, nBytes);

	if (pEntry->nRelOffset) {
		*m_ppbTarget = AdjustTarget(pbDst, pbSrc, nBytesFixed, pEntry->nRelOffset);
	}
	if (pEntry->nFlagBits & NOENLARGE) {
		*m_plExtra = -*m_plExtra;
	}
	if (pEntry->nFlagBits & DYNAMIC) {
		*m_ppbTarget = DETOUR_INSTRUCTION_TARGET_DYNAMIC;
	}
	return pbSrc + nBytes;
}

PBYTE CDetourDis::CopyBytesPrefix(REFCOPYENTRY pEntry, PBYTE pbDst, PBYTE pbSrc)
{
	CopyBytes(pEntry, pbDst, pbSrc);

	pEntry = &s_rceCopyTable[pbSrc[1]];
	return (this->*pEntry->pfCopy)(pEntry, pbDst + 1, pbSrc + 1);
}

PBYTE CDetourDis::AdjustTarget(PBYTE pbDst, PBYTE pbSrc, LONG cbOp, LONG cbTargetOffset)
{
	LONG cbTargetSize = cbOp - cbTargetOffset;
	PBYTE pbTarget = NULL;
	PVOID pvTargetAddr = &pbDst[cbTargetOffset];
	LONG nOldOffset = 0;

	switch (cbTargetSize) {
	case 1:
		nOldOffset = (LONG) * (PCHAR&)pvTargetAddr;
		*m_plExtra = 3;
		break;
	case 2:
		nOldOffset = (LONG) * (PSHORT&)pvTargetAddr;
		*m_plExtra = 2;
		break;
	case 4:
		nOldOffset = (LONG) * (PLONG&)pvTargetAddr;
		*m_plExtra = 0;
		break;
	default:
		ASSERT(!"cbTargetSize is invalid.");
		break;
	}

	pbTarget = pbSrc + cbOp + nOldOffset;
	LONG nNewOffset = nOldOffset - (pbDst - pbSrc);

	switch (cbTargetSize) {
	case 1:
		*(PCHAR&)pvTargetAddr = (CHAR)nNewOffset;
		break;
	case 2:
		*(PSHORT&)pvTargetAddr = (SHORT)nNewOffset;
		break;
	case 4:
		*(PLONG&)pvTargetAddr = (LONG)nNewOffset;
		break;
	}
	ASSERT(pbDst + cbOp + nNewOffset == pbTarget);
	return pbTarget;
}

PBYTE CDetourDis::Invalid(REFCOPYENTRY pEntry, PBYTE pbDst, PBYTE pbSrc)
{
	(void)pbDst;
	(void)pEntry;
	ASSERT(!"Invalid Instruction");
	return pbSrc + 1;
}

////////////////////////////////////////////////////// Individual Bytes Codes.
//
PBYTE CDetourDis::Copy0F(REFCOPYENTRY pEntry, PBYTE pbDst, PBYTE pbSrc)
{
	CopyBytes(pEntry, pbDst, pbSrc);

	pEntry = &s_rceCopyTable0F[pbSrc[1]];
	return (this->*pEntry->pfCopy)(pEntry, pbDst + 1, pbSrc + 1);
}

PBYTE CDetourDis::Copy66(REFCOPYENTRY pEntry, PBYTE pbDst, PBYTE pbSrc)
{	// Operand-size override prefix
	Set16BitOperand();
	return CopyBytesPrefix(pEntry, pbDst, pbSrc);
}

PBYTE CDetourDis::Copy67(REFCOPYENTRY pEntry, PBYTE pbDst, PBYTE pbSrc)
{	// Address size override prefix
	Set16BitAddress();
	return CopyBytesPrefix(pEntry, pbDst, pbSrc);
}

PBYTE CDetourDis::CopyF6(REFCOPYENTRY pEntry, PBYTE pbDst, PBYTE pbSrc)
{
	(void)pEntry;

	// TEST BYTE /0
	if (0x00 == (0x38 & pbSrc[1])) {	// reg(bits 543) of ModR/M == 0
		const COPYENTRY ce = { 0xf6, 3, 3, 1, 0, 0, &CDetourDis::CopyBytes };
		return (this->*ce.pfCopy)(&ce, pbDst, pbSrc);
	}


	const COPYENTRY ce = { 0xf6, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes };
	return (this->*ce.pfCopy)(&ce, pbDst, pbSrc);
}

PBYTE CDetourDis::CopyF7(REFCOPYENTRY pEntry, PBYTE pbDst, PBYTE pbSrc)
{
	(void)pEntry;

	// TEST WORD /0
	if (0x00 == (0x38 & pbSrc[1])) {	// reg(bits 543) of ModR/M == 0
		const COPYENTRY ce = { 0xf7, 6, 4, 1, 0, 0, &CDetourDis::CopyBytes };
		return (this->*ce.pfCopy)(&ce, pbDst, pbSrc);
	}

	// DIV /6
	// IDIV /7
	// IMUL /5
	// MUL /4
	// NEG /3
	// NOT /2
	const COPYENTRY ce = { 0xf7, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes };
	return (this->*ce.pfCopy)(&ce, pbDst, pbSrc);
}

PBYTE CDetourDis::CopyFF(REFCOPYENTRY pEntry, PBYTE pbDst, PBYTE pbSrc)
{	// CALL /2
	// CALL /3
	// INC /0
	// JMP /4
	// JMP /5
	// PUSH /6
	(void)pEntry;

	if (0x15 == pbSrc[1] || 0x25 == pbSrc[1]) {			// CALL [], JMP []
		PBYTE* ppbTarget = *(PBYTE**)&pbSrc[2];
		*m_ppbTarget = *ppbTarget;
	}
	else if (0x10 == (0x38 & pbSrc[1]) || // CALL /2 --> reg(bits 543) of ModR/M == 010
		0x18 == (0x38 & pbSrc[1]) || // CALL /3 --> reg(bits 543) of ModR/M == 011
		0x20 == (0x38 & pbSrc[1]) || // JMP /4 --> reg(bits 543) of ModR/M == 100
		0x28 == (0x38 & pbSrc[1])    // JMP /5 --> reg(bits 543) of ModR/M == 101
		) {
		*m_ppbTarget = DETOUR_INSTRUCTION_TARGET_DYNAMIC;
	}
	const COPYENTRY ce = { 0xff, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes };
	return (this->*ce.pfCopy)(&ce, pbDst, pbSrc);
}

///////////////////////////////////////////////////////// Disassembler Tables.
//
const BYTE CDetourDis::s_rbModRm[256] = {
	0,0,0,0, SIB | 1,4,0,0, 0,0,0,0, SIB | 1,4,0,0,					// 0x
	0,0,0,0, SIB | 1,4,0,0, 0,0,0,0, SIB | 1,4,0,0,					// 1x
	0,0,0,0, SIB | 1,4,0,0, 0,0,0,0, SIB | 1,4,0,0,					// 2x
	0,0,0,0, SIB | 1,4,0,0, 0,0,0,0, SIB | 1,4,0,0,					// 3x
	1,1,1,1, 2,1,1,1, 1,1,1,1, 2,1,1,1,					// 4x
	1,1,1,1, 2,1,1,1, 1,1,1,1, 2,1,1,1,					// 5x
	1,1,1,1, 2,1,1,1, 1,1,1,1, 2,1,1,1,					// 6x
	1,1,1,1, 2,1,1,1, 1,1,1,1, 2,1,1,1,					// 7x
	4,4,4,4, 5,4,4,4, 4,4,4,4, 5,4,4,4,					// 8x
	4,4,4,4, 5,4,4,4, 4,4,4,4, 5,4,4,4,					// 9x
	4,4,4,4, 5,4,4,4, 4,4,4,4, 5,4,4,4,					// Ax
	4,4,4,4, 5,4,4,4, 4,4,4,4, 5,4,4,4,					// Bx
	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,					// Cx
	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,					// Dx
	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,					// Ex
	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0					// Fx
};

const CDetourDis::COPYENTRY CDetourDis::s_rceCopyTable[257] =
{
	{ 0x00, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x01, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x02, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x03, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x04, 2, 2, 0, 0, 0,&CDetourDis::CopyBytes },
	{ 0x05, 5, 3, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x06, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x07, 1, 1, 0, 0, 0,&CDetourDis::CopyBytes },
	{ 0x08, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x09, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x0A, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x0B, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x0C, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x0D, 5, 3, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x0E, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x0F, 1, 1, 0, 0, 0, &CDetourDis::Copy0F },
	{ 0x10, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x11, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x12, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x13, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x14, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x15, 5, 3, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x16, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x17, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x18, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x19, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x1A, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x1B, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x1C, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x1D, 5, 3, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x1E, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x1F, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x20, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x21, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x22, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x23, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x24, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x25, 5, 3, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x26, 1, 1, 0, 0, 0, &CDetourDis::CopyBytesPrefix },
	{ 0x27, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x28, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x29, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x2A, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x2B, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x2C, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x2D, 5, 3, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x2E, 1, 1, 0, 0, 0, &CDetourDis::CopyBytesPrefix },
	{ 0x2F, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x30, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x31, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x32, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x33, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x34, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x35, 5, 3, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x36, 1, 1, 0, 0, 0, &CDetourDis::CopyBytesPrefix },
	{ 0x37, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x38, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x39, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x3A, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x3B, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x3C, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x3D, 5, 3, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x3E, 1, 1, 0, 0, 0, &CDetourDis::CopyBytesPrefix },
	{ 0x3F, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x40, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x41, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x42, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x43, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x44, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x45, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x46, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x47, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x48, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x49, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x4A, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x4B, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x4C, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x4D, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x4E, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x4F, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x50, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x51, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x52, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x53, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x54, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x55, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x56, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x57, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x58, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x59, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x5A, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x5B, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x5C, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x5D, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x5E, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x5F, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x60, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x61, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x62, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x63, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x64, 1, 1, 0, 0, 0, &CDetourDis::CopyBytesPrefix },
	{ 0x65, 1, 1, 0, 0, 0, &CDetourDis::CopyBytesPrefix },
	{ 0x66, 1, 1, 0, 0, 0, &CDetourDis::Copy66 },
	{ 0x67, 1, 1, 0, 0, 0, &CDetourDis::Copy67 },
	{ 0x68, 5, 3, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x69, 6, 4, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x6A, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x6B, 3, 3, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x6C, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x6D, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x6E, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x6F, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x70, 2, 2, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x71, 2, 2, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x72, 2, 2, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x73, 2, 2, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x74, 2, 2, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x75, 2, 2, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x76, 2, 2, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x77, 2, 2, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x78, 2, 2, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x79, 2, 2, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x7A, 2, 2, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x7B, 2, 2, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x7C, 2, 2, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x7D, 2, 2, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x7E, 2, 2, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x7F, 2, 2, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x80, 3, 3, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x81, 6, 4, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x82, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x83, 3, 3, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x84, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x85, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x86, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x87, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x88, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x89, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x8A, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x8B, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x8C, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x8D, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x8E, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x8F, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x90, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x91, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x92, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x93, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x94, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x95, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x96, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x97, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x98, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x99, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x9A, 7, 5, 0, 0, DYNAMIC, &CDetourDis::CopyBytes },
	{ 0x9B, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x9C, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x9D, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x9E, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x9F, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xA0, 5, 3, 0, 0, ADDRESS, &CDetourDis::CopyBytes },
	{ 0xA1, 5, 3, 0, 0, ADDRESS, &CDetourDis::CopyBytes },
	{ 0xA2, 5, 3, 0, 0, ADDRESS, &CDetourDis::CopyBytes },
	{ 0xA3, 5, 3, 0, 0, ADDRESS, &CDetourDis::CopyBytes },
	{ 0xA4, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xA5, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xA6, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xA7, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xA8, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xA9, 5, 3, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xAA, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xAB, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xAC, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xAD, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xAE, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xAF, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xB0, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xB1, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xB2, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xB3, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xB4, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xB5, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xB6, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xB7, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xB8, 5, 3, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xB9, 5, 3, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xBA, 5, 3, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xBB, 5, 3, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xBC, 5, 3, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xBD, 5, 3, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xBE, 5, 3, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xBF, 5, 3, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xC0, 3, 3, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xC1, 3, 3, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xC2, 3, 3, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xC3, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xC4, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xC5, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xC6, 3, 3, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xC7, 6, 4, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xC8, 4, 4, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xC9, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xCA, 3, 3, 0, 0, DYNAMIC, &CDetourDis::CopyBytes },
	{ 0xCB, 1, 1, 0, 0, DYNAMIC, &CDetourDis::CopyBytes },
	{ 0xCC, 1, 1, 0, 0, DYNAMIC, &CDetourDis::CopyBytes },
	{ 0xCD, 2, 2, 0, 0, DYNAMIC, &CDetourDis::CopyBytes },
	{ 0xCE, 1, 1, 0, 0, DYNAMIC, &CDetourDis::CopyBytes },
	{ 0xCF, 1, 1, 0, 0, DYNAMIC, &CDetourDis::CopyBytes },
	{ 0xD0, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xD1, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xD2, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xD3, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xD4, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xD5, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xD6, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xD7, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xD8, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xD9, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xDA, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xDB, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xDC, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xDD, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xDE, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xDF, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xE0, 2, 2, 0, 1, NOENLARGE, &CDetourDis::CopyBytes },
	{ 0xE1, 2, 2, 0, 1, NOENLARGE, &CDetourDis::CopyBytes },
	{ 0xE2, 2, 2, 0, 1, NOENLARGE, &CDetourDis::CopyBytes },
	{ 0xE3, 2, 2, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0xE4, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xE5, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xE6, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xE7, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xE8, 5, 3, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0xE9, 5, 3, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0xEA, 7, 5, 0, 0, DYNAMIC, &CDetourDis::CopyBytes },
	{ 0xEB, 2, 2, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0xEC, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xED, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xEE, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xEF, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xF0, 1, 1, 0, 0, 0, &CDetourDis::CopyBytesPrefix },
	{ 0xF1, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xF2, 1, 1, 0, 0, 0, &CDetourDis::CopyBytesPrefix },
	{ 0xF3, 1, 1, 0, 0, 0, &CDetourDis::CopyBytesPrefix },
	{ 0xF4, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xF5, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xF6, 0, 0, 0, 0, 0, &CDetourDis::CopyF6 },
	{ 0xF7, 0, 0, 0, 0, 0, &CDetourDis::CopyF7 },
	{ 0xF8, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xF9, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xFA, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xFB, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xFC, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xFD, 1, 1, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xFE, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xFF, 0, 0, 0, 0, 0, &CDetourDis::CopyFF },
	{ 0, 0, 0, 0, 0, 0, 0 },
};

const CDetourDis::COPYENTRY CDetourDis::s_rceCopyTable0F[257] =
{
	{ 0x00, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x01, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x02, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x03, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x04, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x05, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x06, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x07, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x08, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x09, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x0A, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x0B, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x0C, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x0D, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x0E, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x0F, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x10, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x11, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x12, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x13, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x14, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x15, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x16, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x17, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x18, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x19, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x1A, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x1B, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x1C, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x1D, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x1E, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x1F, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x20, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x21, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x22, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x23, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x24, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x25, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x26, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x27, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x28, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x29, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x2A, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x2B, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x2C, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x2D, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x2E, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x2F, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x30, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x31, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x32, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x33, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x34, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x35, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x36, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x37, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x38, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x39, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x3A, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x3B, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x3C, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x3D, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x3E, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x3F, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x40, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x41, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x42, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x43, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x44, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x45, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x46, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x47, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x48, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x49, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x4A, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x4B, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x4C, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x4D, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x4E, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x4F, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x50, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x51, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x52, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x53, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x54, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x55, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x56, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x57, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x58, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x59, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x5A, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x5B, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x5C, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x5D, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x5E, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x5F, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x60, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x61, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x62, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x63, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x64, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x65, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x66, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x67, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x68, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x69, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x6A, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x6B, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x6C, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x6D, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x6E, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x6F, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x70, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x71, 3, 3, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x72, 3, 3, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x73, 3, 3, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x74, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x75, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x76, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x77, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0x78, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x79, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x7A, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x7B, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x7C, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x7D, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0x7E, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x7F, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x80, 5, 3, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x81, 5, 3, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x82, 5, 3, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x83, 5, 3, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x84, 5, 3, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x85, 5, 3, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x86, 5, 3, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x87, 5, 3, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x88, 5, 3, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x89, 5, 3, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x8A, 5, 3, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x8B, 5, 3, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x8C, 5, 3, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x8D, 5, 3, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x8E, 5, 3, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x8F, 5, 3, 0, 1, 0, &CDetourDis::CopyBytes },
	{ 0x90, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x91, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x92, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x93, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x94, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x95, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x96, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x97, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x98, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x99, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x9A, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x9B, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x9C, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x9D, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x9E, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0x9F, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xA0, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xA1, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xA2, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xA3, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xA4, 3, 3, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xA5, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xA6, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xA7, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xA8, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xA9, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xAA, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xAB, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xAC, 3, 3, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xAD, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xAE, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xAF, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xB0, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xB1, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xB2, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xB3, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xB4, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xB5, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xB6, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xB7, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xB8, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xB9, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xBA, 3, 3, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xBB, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xBC, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xBD, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xBE, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xBF, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xC0, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xC1, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xC2, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xC3, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xC4, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xC5, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xC6, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xC7, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xC8, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xC9, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xCA, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xCB, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xCC, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xCD, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xCE, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xCF, 2, 2, 0, 0, 0, &CDetourDis::CopyBytes },
	{ 0xD0, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xD1, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xD2, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xD3, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xD4, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xD5, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xD6, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xD7, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xD8, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xD9, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xDA, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xDB, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xDC, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xDD, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xDE, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xDF, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xE0, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xE1, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xE2, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xE3, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xE4, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xE5, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xE6, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xE7, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xE8, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xE9, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xEA, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xEB, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xEC, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xED, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xEE, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xEF, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xF0, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xF1, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xF2, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xF3, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xF4, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xF5, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xF6, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xF7, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xF8, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xF9, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xFA, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xFB, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0xFC, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xFD, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xFE, 2, 2, 1, 0, 0, &CDetourDis::CopyBytes },
	{ 0xFF, 1, 1, 0, 0, 0, &CDetourDis::Invalid },
	{ 0, 0, 0, 0, 0, 0, 0 },
};
BOOL CDetourDis::SanityCheckSystem()
{
	ULONG n = 0;
	for (n = 0; n < 256; n++) {
		REFCOPYENTRY pEntry = &s_rceCopyTable[n];

		if (n != pEntry->nOpcode) {
			ASSERT(n == pEntry->nOpcode);
			return FALSE;
		}
	}
	if (s_rceCopyTable[256].pfCopy != NULL) {
		ASSERT(!"Missing end marker.");
		return FALSE;
	}

	for (n = 0; n < 256; n++) {
		REFCOPYENTRY pEntry = &s_rceCopyTable0F[n];

		if (n != pEntry->nOpcode) {
			ASSERT(n == pEntry->nOpcode);
			return FALSE;
		}
	}
	if (s_rceCopyTable0F[256].pfCopy != NULL) {
		ASSERT(!"Missing end marker.");
		return FALSE;
	}

	return TRUE;
}
//
///////////////////////////////////////////////////////////////// End of File.
