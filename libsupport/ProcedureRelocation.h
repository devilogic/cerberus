__address __API__ CalcTargetAddress(__byte bSize, __address addrNowAddress, __offset ofOffset, __integer iInstLen, __bool bUp);
__offset __API__ CalcCurrOffsetFromAddress(__byte bSize, __address addrTargetAddress, __address addrNowAddress, __integer iInstLen);
__integer __API__ SimpleCalcThisProcedureLength(__memory pProcedure);
__memory __API__ RelocationThisProcedure(__memory pProcedure, __memory pOrigProcedureAddress, __integer iProcedureSize);