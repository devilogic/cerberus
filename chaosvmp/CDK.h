#if !defined(__CDK_H__)
#define __CDK_H__

#if defined(__cplusplus)
extern "C"
{
#endif

//////////////////////////////////////////////////////////////////////////
// 虚拟机保护
//////////////////////////////////////////////////////////////////////////

#define __VMP_PROTECT__(FUNCNAME) {\
	__asm{_emit 0xe9}\
	__asm{_emit 0x09}\
	__asm{_emit 0x00}\
	__asm{_emit 0x00}\
	__asm{_emit 0x00}\
	__asm{_emit 0x19}\
	__asm{_emit 0x83}\
	__asm{_emit 0x12}\
	__asm{_emit 0x10}\
	__asm{call vmp_start_##FUNCNAME}\
}

#define __VMP_START__(FUNCNAME) \
	void vmp_end_##FUNCNAME();\
	__declspec(naked) void vmp_start_##FUNCNAME() {\
	__asm{push eax}\
	__asm{add eax,5}\
	__asm{lea eax,[eax-5]}\
	__asm{pop eax}\
	__asm{add edx,edx}\
	__asm{sub edx,edx}\
	__asm{_emit 0x19}\
	__asm{_emit 0x83}\
	__asm{_emit 0x12}\
	__asm{_emit 0x10}\
	__asm{call vmp_end_##FUNCNAME}\
}

#define __VMP_END__(FUNCNAME) \
	__declspec(naked) void vmp_end_##FUNCNAME() {\
	__asm{_emit 0x60}\
	__asm{_emit 0x9c}\
	__asm{push edx}\
	__asm{add eax,5}\
	__asm{lea eax,[eax-5]}\
	__asm{pop edx}\
	__asm{_emit 0x9d}\
	__asm{_emit 0x61}\
	__asm{_emit 0xc3}\
	__asm{_emit 0x19}\
	__asm{_emit 0x83}\
	__asm{_emit 0x12}\
	__asm{_emit 0x10}\
}

//////////////////////////////////////////////////////////////////////////
// 力量保护
//////////////////////////////////////////////////////////////////////////

#define __POWER_PROTECT__(FUNCNAME) {\
	__asm{_emit 0xe9}\
	__asm{_emit 0x09}\
	__asm{_emit 0x00}\
	__asm{_emit 0x00}\
	__asm{_emit 0x00}\
	__asm{_emit 0x10}\
	__asm{_emit 0x12}\
	__asm{_emit 0x83}\
	__asm{_emit 0x19}\
	__asm{call power_start_##FUNCNAME}\
}

#define __POWER_START__(FUNCNAME) \
	void power_end_##FUNCNAME();\
	__declspec(naked) void power_start_##FUNCNAME() {\
	__asm{push eax}\
	__asm{add eax,5}\
	__asm{lea eax,[eax-5]}\
	__asm{pop eax}\
	__asm{add edx,edx}\
	__asm{sub edx,edx}\
	__asm{_emit 0x10}\
	__asm{_emit 0x12}\
	__asm{_emit 0x83}\
	__asm{_emit 0x19}\
	__asm{call power_end_##FUNCNAME}\
}

#define __POWER_END__(FUNCNAME) \
	__declspec(naked) void power_end_##FUNCNAME() {\
	__asm{_emit 0x60}\
	__asm{_emit 0x9c}\
	__asm{push edx}\
	__asm{add eax,5}\
	__asm{lea eax,[eax-5]}\
	__asm{pop edx}\
	__asm{_emit 0x9d}\
	__asm{_emit 0x61}\
	__asm{_emit 0xc3}\
	__asm{_emit 0x10}\
	__asm{_emit 0x12}\
	__asm{_emit 0x83}\
	__asm{_emit 0x19}\
}

#if defined(__cplusplus)
}
#endif

#endif