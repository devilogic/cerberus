#if !defined(__ANALYZE_H__)
#define __ANALYZE_H__

#include "Common.h"
#include "AnalyzeBin.h"
#include "Support.h"
#include "Setting.h"

extern __bool g_bGenProcedureFlowChart;

__bool __INTERNAL_FUNC__ Analyze(PXFILE_ATTACH_INFO pTarget, __tchar *pResultDir, __tchar *pResultFilePath, PANALYZE_CONFIGURE pConfigure);

#endif