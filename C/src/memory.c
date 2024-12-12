#include "include/memory.h"


void *pic_memcpy(void* dest, const void* src, size_t n) 
{
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    
    while (n--) {
        *d++ = *s++;
    }
    
    return dest;
}

INT MemCompare( PVOID s1, PVOID s2, INT len)
{
    PUCHAR p = s1;
    PUCHAR q = s2;
    INT charCompareStatus = 0;

    if ( s1 == s2 ) {
        return charCompareStatus;
    }

    while (len > 0)
    {
        if (*p != *q)
        {
            charCompareStatus = (*p >*q)?1:-1;
            break;
        }
        len--;
        p++;
        q++;
    }
    return charCompareStatus;
}

/*!
 * @brief
 *  add module + function to CFG exception list.
 *
 * @param ImageBase
 * @param Function
 * Also refer to:
 * https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-setprocessvalidcalltargets
 * https://conference.hitb.org/hitbsecconf2023ams/materials/D1T2%20-%20Windows%20Syscalls%20in%20Shellcode%20-%20Advanced%20Techniques%20for%20Malicious%20Functionality%20-%20Bramwell%20Brizendine.pdf
 * https://www.fortinet.com/blog/threat-research/documenting-the-undocumented-adding-cfg-exceptions
 * 
 */
VOID CfgAddressAdd(
    IN PVOID ImageBase,
    IN PVOID Function
) {

    CFG_CALL_TARGET_INFO Cfg      = { 0 };
    MEMORY_RANGE_ENTRY   MemRange = { 0 };
    VM_INFORMATION       VmInfo   = { 0 };
    PIMAGE_NT_HEADERS    NtHeader = { 0 };
    ULONG                Output   = 0;
    NTSTATUS             NtStatus = STATUS_SUCCESS;

    NtHeader                = (LPVOID)( ImageBase + ( ( PIMAGE_DOS_HEADER ) ImageBase )->e_lfanew );
    MemRange.NumberOfBytes  = (UINT_PTR)( NtHeader->OptionalHeader.SizeOfImage + 0x1000 - 1 ) &~( 0x1000 - 1 );
    MemRange.VirtualAddress = ImageBase;

    /* set cfg target call info */
    Cfg.Flags  = CFG_CALL_TARGET_VALID;
    Cfg.Offset = (char*)Function - (char*)ImageBase;

    VmInfo.dwNumberOfOffsets = 1;
    VmInfo.plOutput          = &Output;
    VmInfo.ptOffsets         = &Cfg;
    VmInfo.pMustBeZero       = FALSE;
    VmInfo.pMoarZero         = FALSE;

    // Possible the call is failing because the loader is not compiled with CFG
    if ( ! NT_SUCCESS( NtStatus = NtSetInformationVirtualMemory( NtCurrentProcess(), VmCfgCallTargetInformation, 1, &MemRange, &VmInfo, sizeof( VmInfo ) ) ) ) {
        // __debugbreak();
    }
}