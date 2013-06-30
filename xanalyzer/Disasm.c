#include "Disasm.h"
#include "Support.h"

__bool __INTERNAL_FUNC__ DisAsm(__memory pMem, __tchar *pResultFilePath, PDISASM_CONFIGURE pConfigure) {
	FILE *fp = NULL;
	__char buf[1024] = {0};
	__address addrImageBase = 0;
	PIMAGE_NT_HEADERS pNtHdr = NULL;
	PIMAGE_SECTION_HEADER pCodeSecHdr = NULL;

	UnicodeToAnsi(pResultFilePath, MAX_PATH, buf, 1024);
	fp = fopen(buf, "w");
	if (!fp) return FALSE;

	// 输出信息头
	fprintf(fp, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");

	if (pConfigure->bDisAsm) {
		ud_t ud_obj = {0};
		__memory pCode = NULL;
		__integer iCodeSize = 0;
		__offset ofOffset = 0;
		__offset ofEntryOffset = 0;
		__address addrAddress = 0;

		pNtHdr = GetNtHeader(pMem);
		pCodeSecHdr = GetEntryPointSection(pMem);
		addrImageBase = pNtHdr->OptionalHeader.ImageBase;
		pCode = pMem + pCodeSecHdr->PointerToRawData;
		iCodeSize = pCodeSecHdr->SizeOfRawData;
		ofEntryOffset = Rva2Raw(pMem, pNtHdr->OptionalHeader.AddressOfEntryPoint);
		addrAddress = addrImageBase + pCodeSecHdr->VirtualAddress;

		fprintf(fp, "<Disasm Size=\"0x%X\">\n", iCodeSize);

		/* initialize */
		ud_init(&ud_obj);
		ud_set_mode(&ud_obj, 32);
		ud_set_input_buffer(&ud_obj, pCode, iCodeSize);
		if (pConfigure->bATT)
			ud_set_syntax(&ud_obj, UD_SYN_ATT);
		else
			ud_set_syntax(&ud_obj, UD_SYN_INTEL);

		/* disassembly loop */
		while (ud_disassemble(&ud_obj)) {
			__char* hex1 = NULL;
			hex1 = (__char *)ud_insn_hex(&ud_obj);
			if (ofEntryOffset == ofOffset)
				fprintf(fp, "<x%X EntryPoint=\"TRUE\" HexCode=\"%s\">%s</x%X>\n", addrAddress, hex1, ud_insn_asm(&ud_obj), addrAddress);
			else
				fprintf(fp, "<x%X HexCode=\"%s\">%s</x%X>\n", addrAddress, hex1, ud_insn_asm(&ud_obj), addrAddress);

			ofOffset += ud_insn_len(&ud_obj);
			addrAddress += ud_insn_len(&ud_obj);
		}
	}

	fprintf(fp, "</Disasm>\n");
	fclose(fp);
	return TRUE;
}

