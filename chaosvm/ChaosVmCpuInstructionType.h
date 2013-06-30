#if !defined(__CHAOSVM_CPU_INSTRUCTION_TYPE__H__)
#define __CHAOSVM_CPU_INSTRUCTION_TYPE__H__

/*
 * 保存指令名称
 */
#if 0
#define __INSTRUCTION_NAME_NONE__                       0
#define __INSTRUCTION_NAME_CALL__                       1
#define __INSTRUCTION_NAME_STRING__                     2
#define __INSTRUCTION_NAME_INTN__                       3
#define __INSTRUCTION_NAME_RETN__                       4
#define __INSTRUCTION_NAME_JMP__                        4
#define __INSTRUCTION_NAME_JCC__                        4
#define __CPU_INSTRUCTION_NAME_SET__(pCPU, Name)        ((pCPU)->InstructionName = INSTRUCTION_NAME_##Name)
#endif

/*
 * 保存指令类型
 */
#define __INSTRUCTION_TYPE_NONE__						0
#define __INSTRUCTION_TYPE_STRING__						2
#define __INSTRUCTION_TYPE_INT__                        3
#define __INSTRUCTION_TYPE_FLOW_CONTROL__               4

#define __INSTR_SUB_TYPE_FLOW_CONTROL_CALL_NEAR__       1
#define __INSTR_SUB_TYPE_FLOW_CONTROL_CALL_FAR__        2
#define __INSTR_SUB_TYPE_FLOW_CONTROL_JMP_NEAR__        3
#define __INSTR_SUB_TYPE_FLOW_CONTROL_JMP_FAR__         4
#define __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_NEAR__        5
#define __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_FAR__         6
#define __INSTR_SUB_TYPE_FLOW_CONTROL_RET_NEAR__        7

#define __CPU_INSTRUCTION_TYPE_SET__(pCPU, Type)        ((pCPU)->InstructionTypeInfo.wInstructionType = Type)


#define __CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, SubType, Seg, Offset) \
	((pCPU)->InstructionTypeInfo.Context.FlowControl.bSubType = (__byte)(SubType), \
	(pCPU)->InstructionTypeInfo.Context.FlowControl.PrevAddress.wSeg = (__word)(Seg), \
	(pCPU)->InstructionTypeInfo.Context.FlowControl.PrevAddress.ofOffset = (__offset)(Offset))

#endif