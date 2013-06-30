/*
 * 2012.2.8 将段寄存器的统一函数 FuncOne_Prefix_SegOverride 换成 FuncOne_FuncOne_Prefix_Segment_XX独立的处理模式 
 */

///* 已完成函数:  224 */
ONE_OPCODE_TABLE_ENTRY g_ChaosVmCpuDefOneByteOpcodeTable[0x100] = {
	/*0x00*/  FuncOne_ADD_00                  ,  /*ADD      */
	/*0x01*/  FuncOne_ADD_01                  ,  /*ADD      */
	/*0x02*/  FuncOne_ADD_02                  ,  /*ADD      */
	/*0x03*/  FuncOne_ADD_03                  ,  /*ADD      */
	/*0x04*/  FuncOne_ADD_04                  ,  /*ADD      */
	/*0x05*/  FuncOne_ADD_05                  ,  /*ADD      */
	/*0x06*/  FuncOne_PUSH_ES                 ,  /*PUSH     */
	/*0x07*/  FuncOne_POP_ES                  ,  /*POP      */
	/*0x08*/  FuncOne_OR_08                   ,  /*0R       */
	/*0x09*/  FuncOne_OR_09                   ,  /*0R       */
	/*0x0A*/  FuncOne_OR_0A                   ,  /*0R       */
	/*0x0B*/  FuncOne_OR_0B                   ,  /*0R       */
	/*0x0C*/  FuncOne_OR_0C                   ,  /*0R       */
	/*0x0D*/  FuncOne_OR_0D                   ,  /*0R       */
	/*0x0E*/  FuncOne_PUSH_CS                 ,  /*PUSH     */
	/*0x0F*/  FuncOne_Two_MainDispatch        ,  /*_ESCAPE  _ESCAPE*/
	/*0x10*/  FuncOne_ADC_10                  ,  /*ADC      */
	/*0x11*/  FuncOne_ADC_11                  ,  /*ADC      */
	/*0x12*/  FuncOne_ADC_12                  ,  /*ADC      */
	/*0x13*/  FuncOne_ADC_13                  ,  /*ADC      */
	/*0x14*/  FuncOne_ADC_14                  ,  /*ADC      */
	/*0x15*/  FuncOne_ADC_15                  ,  /*ADC      */
	/*0x16*/  FuncOne_PUSH_SS                 ,  /*PUSH     */
	/*0x17*/  FuncOne_POP_SS                  ,  /*POP      */
	/*0x18*/  FuncOne_SBB_18                  ,  /*SBB      */
	/*0x19*/  FuncOne_SBB_19                  ,  /*SBB      */
	/*0x1A*/  FuncOne_SBB_1A                  ,  /*SBB      */
	/*0x1B*/  FuncOne_SBB_1B                  ,  /*SBB      */
	/*0x1C*/  FuncOne_SBB_1C                  ,  /*SBB      */
	/*0x1D*/  FuncOne_SBB_1D                  ,  /*SBB      */
	/*0x1E*/  FuncOne_PUSH_DS                 ,  /*PUSH     */
	/*0x1F*/  FuncOne_POP_DS                  ,  /*POP      */
	/*0x20*/  FuncOne_AND_20                  ,  /*AND      */
	/*0x21*/  FuncOne_AND_21                  ,  /*AND      */
	/*0x22*/  FuncOne_AND_22                  ,  /*AND      */
	/*0x23*/  FuncOne_AND_23                  ,  /*AND      */
	/*0x24*/  FuncOne_AND_24                  ,  /*AND      */
	/*0x25*/  FuncOne_AND_25                  ,  /*AND      */
	/*0x26  FuncOne_Prefix_SegOverride      ,  /*SEG=ES   Prefix*/
	/*0x26*/  FuncOne_FuncOne_Prefix_Segment_ES      ,  /*SEG=ES   Prefix*/
	/*0x27*/  FuncOne_DAA_27                  ,  /*DAA      */
	/*0x28*/  FuncOne_SUB_28                  ,  /*SUB      */
	/*0x29*/  FuncOne_SUB_29                  ,  /*SUB      */
	/*0x2A*/  FuncOne_SUB_2A                  ,  /*SUB      */
	/*0x2B*/  FuncOne_SUB_2B                  ,  /*SUB      */
	/*0x2C*/  FuncOne_SUB_2C                  ,  /*SUB      */
	/*0x2D*/  FuncOne_SUB_2D                  ,  /*SUB      */
	/*0x2E  FuncOne_Prefix_SegOverride      ,  /*SEG=CS   Prefix*/
	/*0x2E*/  FuncOne_FuncOne_Prefix_Segment_CS      ,  /*SEG=CS   Prefix*/
	/*0x2F*/  FuncOne_DAS_2F                  ,  /*DAS      */
	/*0x30*/  FuncOne_XOR_30                  ,  /*XOR      */
	/*0x31*/  FuncOne_XOR_31                  ,  /*XOR      */
	/*0x32*/  FuncOne_XOR_32                  ,  /*XOR      */
	/*0x33*/  FuncOne_XOR_33                  ,  /*XOR      */
	/*0x34*/  FuncOne_XOR_34                  ,  /*XOR      */
	/*0x35*/  FuncOne_XOR_35                  ,  /*XOR      */
	/*0x36  FuncOne_Prefix_SegOverride      ,  /*SEG=SS   Prefix*/
	/*0x36*/  FuncOne_FuncOne_Prefix_Segment_SS      ,  /*SEG=SS   Prefix*/
	/*0x37*/  FuncOne_AAA_37                  ,  /*AAA      */
	/*0x38*/  FuncOne_CMP_38                  ,  /*CMP      */
	/*0x39*/  FuncOne_CMP_39                  ,  /*CMP      */
	/*0x3A*/  FuncOne_CMP_3A                  ,  /*CMP      */
	/*0x3B*/  FuncOne_CMP_3B                  ,  /*CMP      */
	/*0x3C*/  FuncOne_CMP_3C                  ,  /*CMP      */
	/*0x3D*/  FuncOne_CMP_3D                  ,  /*CMP      */
	/*0x3E  FuncOne_Prefix_SegOverride      ,  /*SEG=DS   Prefix*/
	/*0x3E*/  FuncOne_FuncOne_Prefix_Segment_DS      ,  /*SEG=DS   Prefix*/
	/*0x3F*/  FuncOne_AAS_3F                  ,  /*AAS      */
	/*0x40*/  FuncOne_INC_40                  ,  /*INC      */
	/*0x41*/  FuncOne_INC_41                  ,  /*INC      */
	/*0x42*/  FuncOne_INC_42                  ,  /*INC      */
	/*0x43*/  FuncOne_INC_43                  ,  /*INC      */
	/*0x44*/  FuncOne_INC_44                  ,  /*INC      */
	/*0x45*/  FuncOne_INC_45                  ,  /*INC      */
	/*0x46*/  FuncOne_INC_46                  ,  /*INC      */
	/*0x47*/  FuncOne_INC_47                  ,  /*INC      */
	/*0x48*/  FuncOne_DEC_48				  ,  /*DEC      */
	/*0x49*/  FuncOne_DEC_49				  ,  /*DEC      */
	/*0x4A*/  FuncOne_DEC_4A				  ,  /*DEC      */
	/*0x4B*/  FuncOne_DEC_4B				  ,  /*DEC      */
	/*0x4C*/  FuncOne_DEC_4C				  ,  /*DEC      */
	/*0x4D*/  FuncOne_DEC_4D				  ,  /*DEC      */
	/*0x4E*/  FuncOne_DEC_4E				  ,  /*DEC      */
	/*0x4F*/  FuncOne_DEC_4F				  ,  /*DEC      */
	/*0x50*/  FuncOne_PUSH_50                 ,  /*PUSH     */
	/*0x51*/  FuncOne_PUSH_51                 ,  /*PUSH     */
	/*0x52*/  FuncOne_PUSH_52                 ,  /*PUSH     */
	/*0x53*/  FuncOne_PUSH_53                 ,  /*PUSH     */
	/*0x54*/  FuncOne_PUSH_54                 ,  /*PUSH     */
	/*0x55*/  FuncOne_PUSH_55                 ,  /*PUSH     */
	/*0x56*/  FuncOne_PUSH_56                 ,  /*PUSH     */
	/*0x57*/  FuncOne_PUSH_57                 ,  /*PUSH     */
	/*0x58*/  FuncOne_POP_58                  ,  /*POP      */
	/*0x59*/  FuncOne_POP_59                  ,  /*POP      */
	/*0x5A*/  FuncOne_POP_5A                  ,  /*POP      */
	/*0x5B*/  FuncOne_POP_5B                  ,  /*POP      */
	/*0x5C*/  FuncOne_POP_5C                  ,  /*POP      */
	/*0x5D*/  FuncOne_POP_5D                  ,  /*POP      */
	/*0x5E*/  FuncOne_POP_5E                  ,  /*POP      */
	/*0x5F*/  FuncOne_POP_5F                  ,  /*POP      */
	/*0x60*/  FuncOne_PUSHAD_60               ,  /*PUSHAD   */
	/*0x61*/  FuncOne_POPAD_61                ,  /*POPAD    */
	/*0x62*/  FuncOne_UnImplement             ,  /*BOUND    */
	/*0x63*/  FuncOne_UnImplement             ,  /*ARPL     */
	/*0x64  FuncOne_Prefix_SegOverride      ,  /*SEG=FS   Prefix*/
	/*0x64*/  FuncOne_FuncOne_Prefix_Segment_FS      ,  /*SEG=FS   Prefix*/
	/*0x65  FuncOne_Prefix_SegOverride      ,  /*SEG=GS   Prefix*/
	/*0x65*/  FuncOne_FuncOne_Prefix_Segment_GS      ,  /*SEG=GS   Prefix*/
	/*0x66*/  FuncOne_Prefix_66               ,  /*OperandSize Prefix*/
	/*0x67*/  FuncOne_Prefix_67               ,  /*AddressSize Prefix*/
	/*0x68*/  FuncOne_PUSH_68                 ,  /*PUSH     */
	/*0x69*/  FuncOne_IMUL_69                 ,  /*IMUL     */
	/*0x6A*/  FuncOne_PUSH_6A                 ,  /*PUSH     */
	/*0x6B*/  FuncOne_IMUL_6B                 ,  /*IMUL     */
	/*0x6C*/  FuncOne_UnImplement             ,  /*INSB     Input byte from I/O port specified in DX into memory location specified in ES:(E)DI*/
	/*0x6D*/  FuncOne_UnImplement             ,  /*INSD     Input doubleword from I/O port specified in DX into memory location specified in ES:(E)DI*/
	/*0x6E*/  FuncOne_UnImplement             ,  /*OUTSB    Output byte from memory location specified in DS:(E)SI or RSI to I/O port specified in DX*/
	/*0x6F*/  FuncOne_UnImplement             ,  /*OUTSD    Output doubleword from memory location specified in DS:(E)SI or RSI to I/O port specified in DX*/
	/*0x70*/  FuncOne_Jcc_70                  ,  /*Jcc      O*/
	/*0x71*/  FuncOne_Jcc_71                  ,  /*Jcc      NO*/
	/*0x72*/  FuncOne_Jcc_72                  ,  /*Jcc      B/NAE/C*/
	/*0x73*/  FuncOne_Jcc_73                  ,  /*Jcc      NB/AE/NC*/
	/*0x74*/  FuncOne_Jcc_74                  ,  /*Jcc      Z/E*/
	/*0x75*/  FuncOne_Jcc_75                  ,  /*Jcc      NZ/NE*/
	/*0x76*/  FuncOne_Jcc_76                  ,  /*Jcc      BE/NA*/
	/*0x77*/  FuncOne_Jcc_77                  ,  /*Jcc      NBE/A*/
	/*0x78*/  FuncOne_Jcc_78                  ,  /*Jcc      S*/
	/*0x79*/  FuncOne_Jcc_79                  ,  /*Jcc      NS*/
	/*0x7A*/  FuncOne_Jcc_7A                  ,  /*Jcc      P/PE*/
	/*0x7B*/  FuncOne_Jcc_7B                  ,  /*Jcc      NP/PO*/
	/*0x7C*/  FuncOne_Jcc_7C                  ,  /*Jcc      L/NGE*/
	/*0x7D*/  FuncOne_Jcc_7D                  ,  /*Jcc      NL/GE*/
	/*0x7E*/  FuncOne_Jcc_7E                  ,  /*Jcc      LE/NG*/
	/*0x7F*/  FuncOne_Jcc_7F                  ,  /*Jcc      NLE/G*/
	/*0x80*/  FuncOne_OpcodeExtDispatch_80    ,  /*Group1   */
	/*0x81*/  FuncOne_OpcodeExtDispatch_81    ,  /*Group1   */
	/*0x82*/  FuncOne_UnImplement             ,  /*Group1   */
	/*0x83*/  FuncOne_OpcodeExtDispatch_83    ,  /*Group1   */
	/*0x84*/  FuncOne_TEST_84                 ,  /*TEST     */
	/*0x85*/  FuncOne_TEST_85                 ,  /*TEST     */
	/*0x86*/  FuncOne_XCHG_86                 ,  /*XCHG     */
	/*0x87*/  FuncOne_XCHG_87                 ,  /*XCHG     */
	/*0x88*/  FuncOne_MOV_88                  ,  /*MOV      */
	/*0x89*/  FuncOne_MOV_89                  ,  /*MOV      */
	/*0x8A*/  FuncOne_MOV_8A                  ,  /*MOV      */
	/*0x8B*/  FuncOne_MOV_8B                  ,  /*MOV      */
	/*0x8C*/  FuncOne_MOV_8C                  ,  /*MOV      */
	/*0x8D*/  FuncOne_LEA_8D                  ,  /*LEA      */
	/*0x8E*/  FuncOne_MOV_8E                  ,  /*MOV      */
	/*0x8F*/  FuncOne_OpcodeExtDispatch_8F    ,  /*Group1A  */
	/*0x90*/  FuncOne_NOP_90                  ,  /*NOP      */
	/*0x91*/  FuncOne_XCHG_RAX_RCX_91         ,  /*XCHG     */
	/*0x92*/  FuncOne_XCHG_RAX_RDX_92         ,  /*XCHG     */
	/*0x93*/  FuncOne_XCHG_RAX_RBX_93         ,  /*XCHG     */
	/*0x94*/  FuncOne_XCHG_RAX_RSP_94         ,  /*XCHG     */
	/*0x95*/  FuncOne_XCHG_RAX_RBP_95         ,  /*XCHG     */
	/*0x96*/  FuncOne_XCHG_RAX_RSI_96         ,  /*XCHG     */
	/*0x97*/  FuncOne_XCHG_RAX_RDI_97         ,  /*XCHG     */
	/*0x98*/  FuncOne_CWDE_98                 ,  /*CWDE     EAX ← sign-extend of AX*/
	/*0x99*/  FuncOne_CDQ_99                  ,  /*CDQ      EDX:EAX ← sign-extend of EAX*/
	/*0x9A*/  FuncOne_UnImplement             ,  /*CALLF    9A 8075120F B741              call    far 41B7:0F127580*/
	/*0x9B*/  FuncOne_UnImplement             ,  /*WAIT     WAIT*/
	/*0x9C*/  FuncOne_PUSHFD_9C               ,  /*PUSHF    */
	/*0x9D*/  FuncOne_POPFD_9D                ,  /*POPF     */
	/*0x9E*/  FuncOne_SAHF_9E                 ,  /*SAHF     Load: AH ← EFLAGS(SF:ZF:0:AF:0:PF:1:CF)*/
	/*0x9F*/  FuncOne_LAHF_9F                 ,  /*LAHF     Loads SF, ZF, AF, PF, and CF from AH into EFLAGS register.*/
	/*0xA0*/  FuncOne_MOV_A0                  ,  /*MOV      */
	/*0xA1*/  FuncOne_MOV_A1                  ,  /*MOV      */
	/*0xA2*/  FuncOne_MOV_A2                  ,  /*MOV      */
	/*0xA3*/  FuncOne_MOV_A3                  ,  /*MOV      */
	/*0xA4*/  FuncOne_MOVSB_A4                ,  /*MOVSB    */
	/*0xA5*/  FuncOne_MOVSD_A5                ,  /*MOVSD    */
	/*0xA6*/  FuncOne_CMPSB_A6                ,  /*CMPSB    */
	/*0xA7*/  FuncOne_CMPSD_A7                ,  /*CMPSD    */
	/*0xA8*/  FuncOne_TEST_A8                 ,  /*TEST     */
	/*0xA9*/  FuncOne_TEST_A9                 ,  /*TEST     */
	/*0xAA*/  FuncOne_STOSB_AA                ,  /*STOSB    For legacy mode, store AL at address ES:(E)DI, For 64-bit mode store AL at address RDI or EDI*/
	/*0xAB*/  FuncOne_STOS_AB                 ,  /*STOSD    For legacy mode, store EAX at address ES:(E)DI,For 64-bit mode store EAX at address RDI or EDI*/
	/*0xAC*/  FuncOne_LODSB_AC                ,  /*LODSB    */
	/*0xAD*/  FuncOne_LODS_AD                 ,  /*LODSD    */
	/*0xAE*/  FuncOne_SCASB_AE                ,  /*SCASB    */
	/*0xAF*/  FuncOne_SCASD_AF                ,  /*SCASD    */
	/*0xB0*/  FuncOne_MOV_B0                  ,  /*MOV      MOV immediate byte into byte register*/
	/*0xB1*/  FuncOne_MOV_B1                  ,  /*MOV      MOV immediate byte into byte register*/
	/*0xB2*/  FuncOne_MOV_B2                  ,  /*MOV      MOV immediate byte into byte register*/
	/*0xB3*/  FuncOne_MOV_B3                  ,  /*MOV      MOV immediate byte into byte register*/
	/*0xB4*/  FuncOne_MOV_B4                  ,  /*MOV      MOV immediate byte into byte register*/
	/*0xB5*/  FuncOne_MOV_B5                  ,  /*MOV      MOV immediate byte into byte register*/
	/*0xB6*/  FuncOne_MOV_B6                  ,  /*MOV      MOV immediate byte into byte register*/
	/*0xB7*/  FuncOne_MOV_B7                  ,  /*MOV      MOV immediate byte into byte register*/
	/*0xB8*/  FuncOne_MOV_B8                  ,  /*MOV      MOV immediate data (depending on operand-size attribute) into register*/
	/*0xB9*/  FuncOne_MOV_B9				  ,  /*MOV      MOV immediate data (depending on operand-size attribute) into register*/
	/*0xBA*/  FuncOne_MOV_BA                  ,  /*MOV      MOV immediate data (depending on operand-size attribute) into register*/
	/*0xBB*/  FuncOne_MOV_BB                  ,  /*MOV      MOV immediate data (depending on operand-size attribute) into register*/
	/*0xBC*/  FuncOne_MOV_BC                  ,  /*MOV      MOV immediate data (depending on operand-size attribute) into register*/
	/*0xBD*/  FuncOne_MOV_BD                  ,  /*MOV      MOV immediate data (depending on operand-size attribute) into register*/
	/*0xBE*/  FuncOne_MOV_BE                  ,  /*MOV      MOV immediate data (depending on operand-size attribute) into register*/
	/*0xBF*/  FuncOne_MOV_BF                  ,  /*MOV      MOV immediate data (depending on operand-size attribute) into register*/
	/*0xC0*/  FuncOne_OpcodeExtDispatch_C0    ,  /*Group2   Shift Group2*/
	/*0xC1*/  FuncOne_OpcodeExtDispatch_C1    ,  /*Group2   Shift Group2 */
	/*0xC2*/  FuncOne_RETN_C2                 ,  /*RETN     */
	/*0xC3*/  FuncOne_RET_C3                  ,  /*RETN     */
	/*0xC4*/  FuncOne_UnImplement             ,  /*LES      */
	/*0xC5*/  FuncOne_UnImplement             ,  /*LDS      */
	/*0xC6*/  FuncOne_OpcodeExtDispatch_C6    ,  /*Group11  Group11 Mov*/
	/*0xC7*/  FuncOne_OpcodeExtDispatch_C7    ,  /*Group11  Group11 Mov*/
	/*0xC8*/  FuncOne_ENTER_C8                ,  /*ENTER    Make Stack Frame for Procedure Parameters*/
	/*0xC9*/  FuncOne_LEAVE_C9                ,  /*LEAVE    Releases the stack frame set up by an earlier ENTER instruction*/
	/*0xCA*/  FuncOne_UnImplement             ,  /*RETF     */
	/*0xCB*/  FuncOne_UnImplement             ,  /*RETF     */
	/*0xCC*/  FuncOne_INT3_CC                 ,  /*INT3     */
	/*0xCD*/  FuncOne_INT_CD                  ,  /*INT      */
	/*0xCE*/  FuncOne_INTO_CE                 ,  /*INTO     Interrupt 4—if overflow flag is 1*/
	/*0xCF*/  FuncOne_UnImplement             ,  /*IRETD    */
	/*0xD0*/  FuncOne_OpcodeExtDispatch_D0    ,  /*Group2   Shift Group2*/
	/*0xD1*/  FuncOne_OpcodeExtDispatch_D1    ,  /*Group2   Shift Group2*/
	/*0xD2*/  FuncOne_OpcodeExtDispatch_D2    ,  /*Group2   Shift Group2*/
	/*0xD3*/  FuncOne_OpcodeExtDispatch_D3    ,  /*Group2   Shift Group2*/
	/*0xD4*/  FuncOne_AAM_D4                  ,  /*AAM      加法调整指令，调整加法结果为Ib进制*/
	/*0xD5*/  FuncOne_AAD_D5                  ,  /*AAD      除法调整指令，在除法前调整AX中的BCD码*/
	/*0xD6*/  FuncOne_SALC_D6                 ,  /*OP_R     Reserve*/
	/*0xD7*/  FuncOne_XLAT_D7                 ,  /*XLAT     */
	/*0xD8*/  FuncOne_UnImplement             ,  /*ESC      Escape to coprocessor instruction set*/
	/*0xD9*/  FuncOne_UnImplement             ,  /*ESC      Escape to coprocessor instruction set*/
	/*0xDA*/  FuncOne_UnImplement             ,  /*ESC      Escape to coprocessor instruction set*/
	/*0xDB*/  FuncOne_UnImplement             ,  /*ESC      Escape to coprocessor instruction set*/
	/*0xDC*/  FuncOne_UnImplement             ,  /*ESC      Escape to coprocessor instruction set*/
	/*0xDD*/  FuncOne_UnImplement             ,  /*ESC      Escape to coprocessor instruction set*/
	/*0xDE*/  FuncOne_UnImplement             ,  /*ESC      Escape to coprocessor instruction set*/
	/*0xDF*/  FuncOne_UnImplement             ,  /*ESC      Escape to coprocessor instruction set*/
	/*0xE0*/  FuncOne_LOOPE_E0                ,  /*LOOPNE   LOOPNZ*/
	/*0xE1*/  FuncOne_LOOPNE_E1               ,  /*LOOPE    LOOPZ*/
	/*0xE2*/  FuncOne_LOOP_E2                 ,  /*LOOP     LOOP*/
	/*0xE3*/  FuncOne_JRCXZ_E3                ,  /*JrCXZ    Jump short if RCX register is 0.JECXZ rel8 Valid Valid Jump short if ECX register is 0.*/
	/*0xE4*/  FuncOne_UnImplement             ,  /*IN       */
	/*0xE5*/  FuncOne_UnImplement             ,  /*IN       */
	/*0xE6*/  FuncOne_UnImplement             ,  /*OUT      */
	/*0xE7*/  FuncOne_UnImplement             ,  /*OUT      */
	/*0xE8*/  FuncOne_CALL_E8                 ,  /*CALL     */
	/*0xE9*/  FuncOne_JMP_E9                  ,  /*JMP      */
	/*0xEA*/  FuncOne_UnImplement             ,  /*JMP      Jump far, absolute, address given in operand*/
	/*0xEB*/  FuncOne_JMP_EB                  ,  /*JMP      */
	/*0xEC*/  FuncOne_UnImplement             ,  /*IN       */
	/*0xED*/  FuncOne_UnImplement             ,  /*IN       */
	/*0xEE*/  FuncOne_UnImplement             ,  /*OUT      */
	/*0xEF*/  FuncOne_UnImplement             ,  /*OUT      */
	/*0xF0*/  FuncOne_Prefix_F0               ,  /*LOCK     */
	/*0xF1*/  FuncOne_InvalidOpcode           ,  /*OP_R     Reserve*/
	/*0xF2*/  FuncOne_Prefix_F2               ,  /*REPNE    Prefix*/
	/*0xF3*/  FuncOne_Prefix_F3               ,  /*REP/REPE Prefix*/
	/*0xF4*/  FuncOne_UnImplement             ,  /*HLT      */
	/*0xF5*/  FuncOne_CMC_F5                  ,  /*CMC      */
	/*0xF6*/  FuncOne_OpcodeExtDispatch_F6    ,  /*Group3   Group3*/
	/*0xF7*/  FuncOne_OpcodeExtDispatch_F7    ,  /*Group3   Group3*/
	/*0xF8*/  FuncOne_CLC_F8                  ,  /*CLC      */
	/*0xF9*/  FuncOne_STC_F9                  ,  /*STC      */
	/*0xFA*/  FuncOne_CLI_FA                  ,  /*CLI      */
	/*0xFB*/  FuncOne_STI_FB                  ,  /*STI      */
	/*0xFC*/  FuncOne_CLD_FC                  ,  /*CLD      */
	/*0xFD*/  FuncOne_STD_FD                  ,  /*STD      */
	/*0xFE*/  FuncOne_OpcodeExtDispatch_FE    ,  /*Group4   */
	/*0xFF*/  FuncOne_OpcodeExtDispatch_FF       /*Group5   */
};
