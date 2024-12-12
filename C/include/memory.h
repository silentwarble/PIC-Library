/**
 * Sources:
 * https://github.com/silentwarble/Hannibal/blob/main/Payload_Type/hannibal/hannibal/agent_code/Hannibal/src/utility_memory.c
 */


#include <windows.h>
#include <stddef.h> 
#include <stdint.h>


void *pic_memcpy(void* dest, const void* src, size_t n);

INT MemCompare( PVOID s1, PVOID s2, INT len);

VOID CfgAddressAdd(
    IN PVOID ImageBase,
    IN PVOID Function
);

