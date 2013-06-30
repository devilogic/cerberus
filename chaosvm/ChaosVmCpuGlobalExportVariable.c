EFLAG_CONDITION_TABLE_ENTRY g_ChaosVmCpuDefEFlagContionTable[0x10] = {
	/*0x0*/  { Test_00			},
	/*0x1*/	 { Test_01			},

	/*0x2*/  { Test_02			},
	/*0x3*/  { Test_03			},

	/*0x4*/  { Test_04			},
	/*0x5*/  { Test_05			},

	/*0x6*/  { Test_06			},
	/*0x7*/  { Test_07			},

	/*0x8*/  { Test_08			},
	/*0x9*/  { Test_09			},

	/*0xA*/  { Test_0A			},
	/*0xB*/  { Test_0B			},

	/*0xC*/  { Test_0C			},
	/*0xD*/  { Test_0D			},

	/*0xE*/  { Test_0E			},
	/*0xF*/  { Test_0F			}
};

MODRM_BYTE_ANALYSE_ROUTINE_TABLE_ENTRY g_ChaosVmCpuDefModRMAnalyseRoutineTable[0x02] = {
	{ GetInstructionArgs32			},
	{ GetInstructionArgs16			}
};

PARGS_DISPATCH_TABLE_ENTRY g_ChaosVmCpuDefOpcodeExtensionTableForOne_FF[0x08] = {
	/* 0 */  { FuncExtForOne_INC_FF_0          },
	/* 1 */  { FuncExtForOne_DEC_FF_1          },
	/* 2 */  { FuncExtForOne_CALL_FF_2         },
	/* 3 */  { FuncExtForOne_UnImplement_FF    },
	/* 4 */  { FuncExtForOne_JMP_FF_4          },
	/* 5 */  { FuncExtForOne_UnImplement_FF    },
	/* 6 */  { FuncExtForOne_PUSH_FF_6         },
	/* 7 */  { FuncExtForOne_UnImplement_FF    }
};

PARGS_DISPATCH_TABLE_ENTRY g_ChaosVmCpuDefOpcodeExtensionTableForOne_FE[0x08] = {
	/* 0 */  { FuncExtForOne_INC_FE_0 },
	/* 1 */  { FuncExtForOne_DEC_FE_1 },
	/* 2 */  { FuncExtForOne_InvalidOpcode_FE },
	/* 3 */  { FuncExtForOne_InvalidOpcode_FE },
	/* 4 */  { FuncExtForOne_InvalidOpcode_FE },
	/* 5 */  { FuncExtForOne_InvalidOpcode_FE },
	/* 6 */  { FuncExtForOne_InvalidOpcode_FE },
	/* 7 */  { FuncExtForOne_InvalidOpcode_FE }
};

PARGS_DISPATCH_TABLE_ENTRY g_ChaosVmCpuDefOpcodeExtensionTableForOne_C6[0x08] = {
	/* 0 */  { FuncExtForOne_MOV_C6_0         },
	/* 1 */  { FuncExtForOne_InvalidOpcode_C6 },
	/* 2 */  { FuncExtForOne_InvalidOpcode_C6 },
	/* 3 */  { FuncExtForOne_InvalidOpcode_C6 },
	/* 4 */  { FuncExtForOne_InvalidOpcode_C6 },
	/* 5 */  { FuncExtForOne_InvalidOpcode_C6 },
	/* 6 */  { FuncExtForOne_InvalidOpcode_C6 },
	/* 7 */  { FuncExtForOne_InvalidOpcode_C6 }
};

PARGS_DISPATCH_TABLE_ENTRY g_ChaosVmCpuDefOpcodeExtensionTableForOne_C7[0x02][0x08] = {
	{
		/* 0 */  { FuncExtForOne_MOV_C7_0         },
		/* 1 */  { FuncExtForOne_InvalidOpcode_C7 },
		/* 2 */  { FuncExtForOne_InvalidOpcode_C7 },
		/* 3 */  { FuncExtForOne_InvalidOpcode_C7 },
		/* 4 */  { FuncExtForOne_InvalidOpcode_C7 },
		/* 5 */  { FuncExtForOne_InvalidOpcode_C7 },
		/* 6 */  { FuncExtForOne_InvalidOpcode_C7 },
		/* 7 */  { FuncExtForOne_InvalidOpcode_C7 }
	},
	{
		/* 0 */  { FuncExtForOne_MOV_C7_0         },
		/* 1 */  { FuncExtForOne_InvalidOpcode_C7 },
		/* 2 */  { FuncExtForOne_InvalidOpcode_C7 },
		/* 3 */  { FuncExtForOne_InvalidOpcode_C7 },
		/* 4 */  { FuncExtForOne_InvalidOpcode_C7 },
		/* 5 */  { FuncExtForOne_InvalidOpcode_C7 },
		/* 6 */  { FuncExtForOne_InvalidOpcode_C7 },
		/* 7 */  { FuncExtForOne_InvalidOpcode_C7 }
	}
};

PARGS_DISPATCH_TABLE_ENTRY g_ChaosVmCpuDefOpcodeExtensionTableForOne_F6[0x08] = {
	/* 0 */  { FuncExtForOne_TEST_F6_0        },
	/* 1 */  { FuncExtForOne_InvalidOpcode_F6 },
	/* 2 */  { FuncExtForOne_NOT_F6_2         },
	/* 3 */  { FuncExtForOne_NEG_F6_3         },
	/* 4 */  { FuncExtForOne_MUL_F6_4         },
	/* 5 */  { FuncExtForOne_IMUL_F6_5        },
	/* 6 */  { FuncExtForOne_DIV_F6_6         },
	/* 7 */  { FuncExtForOne_IDIV_F6_7        }
};

PARGS_DISPATCH_TABLE_ENTRY g_ChaosVmCpuDefOpcodeExtensionTableForOne_F7[0x08] = {
	/* 0 */  { FuncExtForOne_TEST_F7_0        },
	/* 1 */  { FuncExtForOne_InvalidOpcode_F7 },
	/* 2 */  { FuncExtForOne_NOT_F7_2         },
	/* 3 */  { FuncExtForOne_NEG_F7_3         },
	/* 4 */  { FuncExtForOne_MUL_F7_4         },
	/* 5 */  { FuncExtForOne_IMUL_F7_5        },
	/* 6 */  { FuncExtForOne_DIV_F7_6         },
	/* 7 */  { FuncExtForOne_IDIV_F7_7        }
};

PARGS_DISPATCH_TABLE_ENTRY g_ChaosVmCpuDefOpcodeExtensionTableForOne_80[0x08] = {
	/* 0 */  { FuncExtForOne_ADD_80_0  },
	/* 1 */  { FuncExtForOne_OR_80_1   },
	/* 2 */  { FuncExtForOne_ADC_80_2  },
	/* 3 */  { FuncExtForOne_SBB_80_3  },
	/* 4 */  { FuncExtForOne_AND_80_4  },
	/* 5 */  { FuncExtForOne_SUB_80_5  },
	/* 6 */  { FuncExtForOne_XOR_80_6  },
	/* 7 */  { FuncExtForOne_CMP_80_7  }
};

PARGS_DISPATCH_TABLE_ENTRY g_ChaosVmCpuDefOpcodeExtensionTableForOne_81[0x08] = {
	/* 0 */  { FuncExtForOne_ADD_81_0 },
	/* 1 */  { FuncExtForOne_OR_81_1  },
	/* 2 */  { FuncExtForOne_ADC_81_2 },
	/* 3 */  { FuncExtForOne_SBB_81_3 },
	/* 4 */  { FuncExtForOne_AND_81_4 },
	/* 5 */  { FuncExtForOne_SUB_81_5 },
	/* 6 */  { FuncExtForOne_XOR_81_6 },
	/* 7 */  { FuncExtForOne_CMP_81_7 }
};

PARGS_DISPATCH_TABLE_ENTRY g_ChaosVmCpuDefOpcodeExtensionTableForOne_83[0x08] = {
	/* 0 */  { FuncExtForOne_ADD_83_0 },
	/* 1 */  { FuncExtForOne_OR_83_1  },
	/* 2 */  { FuncExtForOne_ADC_83_2 },
	/* 3 */  { FuncExtForOne_SBB_83_3 },
	/* 4 */  { FuncExtForOne_AND_83_4 },
	/* 5 */  { FuncExtForOne_SUB_83_5 },
	/* 6 */  { FuncExtForOne_XOR_83_6 },
	/* 7 */  { FuncExtForOne_CMP_83_7 }
};

PARGS_DISPATCH_TABLE_ENTRY g_ChaosVmCpuDefOpcodeExtensionTableForOne_8F[0x08] = {
	/* 0 */  { FuncExtForOne_POP_8F_0         },
	/* 1 */  { FuncExtForOne_InvalidOpcode_8F },
	/* 2 */  { FuncExtForOne_InvalidOpcode_8F },
	/* 3 */  { FuncExtForOne_InvalidOpcode_8F },
	/* 4 */  { FuncExtForOne_InvalidOpcode_8F },
	/* 5 */  { FuncExtForOne_InvalidOpcode_8F },
	/* 6 */  { FuncExtForOne_InvalidOpcode_8F },
	/* 7 */  { FuncExtForOne_InvalidOpcode_8F }
};

PARGS_DISPATCH_TABLE_ENTRY g_ChaosVmCpuDefOpcodeExtensionTableForOne_C0[0x08] = {
	/* 0 */  { FuncExtForOne_ROL_C0_0				},
	/* 1 */  { FuncExtForOne_ROR_C0_1				},
	/* 2 */  { FuncExtForOne_RCL_C0_2				},
	/* 3 */  { FuncExtForOne_RCR_C0_3				},
	/* 4 */  { FuncExtForOne_SHL_C0_4				},
	/* 5 */  { FuncExtForOne_SHR_C0_5				},
	/* 6 */  { FuncExtForOne_IncorrectOpcode_C0		},
	/* 7 */  { FuncExtForOne_SAR_C0_7				}
};

PARGS_DISPATCH_TABLE_ENTRY g_ChaosVmCpuDefOpcodeExtensionTableForOne_C1[0x08] = {
	/* 0 */  { FuncExtForOne_ROL_C1_0				},
	/* 1 */  { FuncExtForOne_ROR_C1_1				},
	/* 2 */  { FuncExtForOne_RCL_C1_2				},
	/* 3 */  { FuncExtForOne_RCR_C1_3				},
	/* 4 */  { FuncExtForOne_SHL_C1_4				},
	/* 5 */  { FuncExtForOne_SHR_C1_5				},
	/* 6 */  { FuncExtForOne_IncorrectOpcode_C1		},
	/* 7 */  { FuncExtForOne_SAR_C1_7				}
};

PARGS_DISPATCH_TABLE_ENTRY g_ChaosVmCpuDefOpcodeExtensionTableForOne_D0[0x08] = {
	/* 0 */  { FuncExtForOne_ROL_D0_0				},
	/* 1 */  { FuncExtForOne_ROR_D0_1				},
	/* 2 */  { FuncExtForOne_RCL_D0_2				},
	/* 3 */  { FuncExtForOne_RCR_D0_3				},
	/* 4 */  { FuncExtForOne_SHL_D0_4				},
	/* 5 */  { FuncExtForOne_SHR_D0_5				},
	/* 6 */  { FuncExtForOne_IncorrectOpcode_D0		},
	/* 7 */  { FuncExtForOne_SAR_D0_7				}
};

PARGS_DISPATCH_TABLE_ENTRY g_ChaosVmCpuDefOpcodeExtensionTableForOne_D1[0x08] = {
	/* 0 */  { FuncExtForOne_ROL_D1_0				},
	/* 1 */  { FuncExtForOne_ROR_D1_1				},
	/* 2 */  { FuncExtForOne_RCL_D1_2				},
	/* 3 */  { FuncExtForOne_RCR_D1_3				},
	/* 4 */  { FuncExtForOne_SHL_D1_4				},
	/* 5 */  { FuncExtForOne_SHR_D1_5				},
	/* 6 */  { FuncExtForOne_IncorrectOpcode_D1		},
	/* 7 */  { FuncExtForOne_SAR_D1_7				}
};

PARGS_DISPATCH_TABLE_ENTRY g_ChaosVmCpuDefOpcodeExtensionTableForOne_D2[0x08] = {
	/* 0 */  { FuncExtForOne_ROL_D2_0				},
	/* 1 */  { FuncExtForOne_ROR_D2_1				},
	/* 2 */  { FuncExtForOne_RCL_D2_2				},
	/* 3 */  { FuncExtForOne_RCR_D2_3				},
	/* 4 */  { FuncExtForOne_SHL_D2_4				},
	/* 5 */  { FuncExtForOne_SHR_D2_5				},
	/* 6 */  { FuncExtForOne_IncorrectOpcode_D2		},
	/* 7 */  { FuncExtForOne_SAR_D2_7				}
};

PARGS_DISPATCH_TABLE_ENTRY g_ChaosVmCpuDefOpcodeExtensionTableForOne_D3[0x08] = {
	/* 0 */  { FuncExtForOne_ROL_D3_0				},
	/* 1 */  { FuncExtForOne_ROR_D3_1				},
	/* 2 */  { FuncExtForOne_RCL_D3_2				},
	/* 3 */  { FuncExtForOne_RCR_D3_3				},
	/* 4 */  { FuncExtForOne_SHL_D3_4				},
	/* 5 */  { FuncExtForOne_SHR_D3_5				},
	/* 6 */  { FuncExtForOne_IncorrectOpcode_D3		},
	/* 7 */  { FuncExtForOne_SAR_D3_7				}
};

PARGS_DISPATCH_TABLE_ENTRY g_ChaosVmCpuDefOpcodeExtensionTableForTwo_0FBA[0x08] = {
	/* 0 */  { FuncExtForTwo_IncorrectOpcode_0FBA },
	/* 1 */  { FuncExtForTwo_IncorrectOpcode_0FBA },
	/* 2 */  { FuncExtForTwo_IncorrectOpcode_0FBA },
	/* 3 */  { FuncExtForTwo_IncorrectOpcode_0FBA },
	/* 4 */  { FuncExtForTwo_BT_0FBA_4            },
	/* 5 */  { FuncExtForTwo_BTS_0FBA_5           },
	/* 6 */  { FuncExtForTwo_BTR_0FBA_6           },
	/* 7 */  { FuncExtForTwo_BTC_0FBA_7           }
};

// 第一张OPCODE表
#include "ChaosVmCpuOneByteOpcodeTable.c"
// 第二张OPCODE表
#include "ChaosVmCpuTwoByteOpcodeTable.c"
