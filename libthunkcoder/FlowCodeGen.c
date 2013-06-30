#define __HasInsideFlow__()				(RandRoll(pThunkCoderConfigure->FlowCoderRollArray))
PFLOWCODER CHARM_INTERNAL_FUNC GenerateFlowCoder(PTHUNKCODER_CONFIGURE pThunkCoderConfigure);



#define __HasContinueIf__()				(RandRoll(pThunkCoderConfigure->FlowCoderRollArray))
#define __HasEndElse__()				(RandRoll(pThunkCoderConfigure->FlowCoderRollArray))
PFLOW_IF CHARM_INTERNAL_FUNC GenerateFlowIf(PTHUNKCODER_CONFIGURE pThunkCoderConfigure, FLOW_IF_TYPE Type)
{
	PFLOW_IF pIf = __new__(FLOW_IF, 1);
	memset(pIf, 0, sizeof(FLOW_IF));

	pIf->Type = Type;
	pIf->pDummyCode = GenerateDummyCode(pThunkCoderConfigure);//产生傀儡代码

	if (Type == FIT_IF)
	{
		if (__HasContinueIf__() == TRUE)
		{
			pIf->pNext = GenerateFlowIf(pThunkCoderConfigure, FIT_ELSE_IF);
		}
		else if (__HasEndElse__() == TRUE)
		{
			pIf->pNext = GenerateFlowIf(pThunkCoderConfigure, FIT_ELSE);
		}
	}
	else if (Type == FIT_ELSE_IF)
	{
		if (__HasContinueIf__() == TRUE)
		{
			pIf->pNext = GenerateFlowIf(pThunkCoderConfigure, FIT_ELSE_IF);
		}
		else if (__HasEndElse__() == TRUE)
		{
			pIf->pNext = GenerateFlowIf(pThunkCoderConfigure, FIT_ELSE);
		}
	}
	else//FIT_ELSE
	{
		pIf->pNext = NULL;
	}

	// 是否有内嵌流程
	if (__HasInsideFlow__() == TRUE)
	{
		pIf->pInside = GenerateFlowCoder(pThunkCoderConfigure);
	}

	return pIf;
}

PFLOW_WHILE CHARM_INTERNAL_FUNC GenerateFlowWhile(PTHUNKCODER_CONFIGURE pThunkCoderConfigure)
{
	PFLOW_WHILE pWhile = __new__(FLOW_WHILE, 1);
	memset(pWhile, 0, sizeof(FLOW_WHILE));

	pWhile->pDummyCode = GenerateDummyCode(pThunkCoderConfigure);
	if (__HasInsideFlow__() == TRUE)
	{
		pWhile->pInside = GenerateFlowCoder(pThunkCoderConfigure);
	}
}

#define __HasCase__()					(RandRoll(pThunkCoderConfigure->FlowCoderRollArray))
#define __HasDefaultCase__()			(RandRoll(pThunkCoderConfigure->FlowCoderRollArray))
PFLOW_SWITCH CHARM_INTERNAL_FUNC GenerateFlowSwitch(PTHUNKCODER_CONFIGURE pThunkCoderConfigure, FLOW_SWITCH_TYPE Type)
{
	PFLOW_SWITCH pSwitch = __new__(FLOW_SWITCH, 1);
	memset(pSwitch, 0, sizeof(FLOW_SWITCH));

	pSwitch->Type = Type;
	pSwitch->pDummyCode = GenerateDummyCode(pThunkCoderConfigure);

	switch (Type)
	{
	case FST_SWITCH:
		{
			// 至少有一个CASE
			pSwitch->pNext = GenerateFlowSwitch(pThunkCoderConfigure, FST_CASE);
		}break;
	case FST_CASE:
		{
			if (__HasCase__() == TRUE)
			{
				pSwitch->pNext = GenerateFlowSwitch(pThunkCoderConfigure, FST_CASE);
			}
			else if (__HasDefaultCase__() == TRUE)
			{
				pSwitch->pNext = GenerateFlowSwitch(pThunkCoderConfigure, FST_DEF);
			}
		}break;
	case FST_DEF:
		{
			pSwitch->pNext = NULL;
		}break;
	}

	// 是否有内嵌流行
	if (__HasInsideFlow__() == TRUE)
	{
		pSwitch->pInside = GenerateFlowCoder(pThunkCoderConfigure);
	}

	return pSwitch;
}

#define __GenerateFlowType__()			((FLOW_TYPE)(GenerateRandomNumber() % 3))
#define __HasNextFlow__()				(RandRoll(pThunkCoderConfigure->FlowCoderRollArray))
PFLOWCODER CHARM_INTERNAL_FUNC GenerateFlowCoder(PTHUNKCODER_CONFIGURE pThunkCoderConfigure)
{
	PFLOWCODER pFlowCoder = __new__(FLOWCODER, 1);
	memset(pFlowCoder, 0, sizeof(FLOWCODER));
	// 产生一个流程结构
	pFlowCoder->Type = __GenerateFlowType__();
	switch (pFlowCoder->Type)
	{
	case FT_IF:
		{
			pFlowCoder->pIf = GenerateFlowIf(pThunkCoderConfigure, FIT_IF);
		}break;
	case FT_WHILE:
		{
			pFlowCoder->pWhile = GenerateFlowWhile(pThunkCoderConfigure);
		}break;
	case FT_SWITCH:
		{
			pFlowCoder->pSwitch = GenerateFlowSwitch(pThunkCoderConfigure, FST_SWITCH);
		}break;
	}

	// 是否有下一个流程
	if (__HasNextFlow__() == TRUE)
	{
		pFlowCoder->pNext = GenerateFlowCoder(pThunkCoderConfigure);
	}
	return pFlowCoder;
}

LPBYTE CHARM_INTERNAL_FUNC AssemblerFlowCoder(PFLOWCODER pFlowCoder, PTHUNKCODER_CONFIGURE pThunkCoderConfigure)
{
	return NULL;
}
