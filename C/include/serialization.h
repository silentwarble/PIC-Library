/**
 * Note:
 * These can all be adapted to work on another OS, but they have only been tested on Windows.
 * If you aren't linking stdlib you will need to resolve functions such as memcpy or VirtualAlloc.
 * Either write PIC versions or find a way to get a pointer to that function. (See Hannibal for a technique)
 * 
 * Sources:
 * https://github.com/MythicAgents/Hannibal/blob/main/Payload_Type/hannibal/hannibal/agent_code/Hannibal/src/utility_serialization.c
 * 
 */

#include <windows.h>
#include <stddef.h> 
#include <stdint.h>


void write_uint8(uint8_t **buffer, uint8_t value);
void write_uint32(uint8_t **buffer, uint32_t value);
void write_uint64(uint8_t **buffer, uint64_t value);
void write_string(uint8_t **buffer, const char *str, BOOL include_null);
void write_stringW(uint8_t **buffer, const wchar_t *str, BOOL include_null);
void write_bytes(uint8_t **buffer, const char *str, int size);

uint8_t read_uint8(uint8_t **buffer);
uint32_t read_uint32(uint8_t **buffer);
uint8_t* read_bytes(uint8_t **buffer, uint32_t length);
char* read_string(uint8_t **buffer, uint32_t length);
wchar_t* read_stringW(uint8_t **buffer, uint32_t length);

DWORD pic_htonl(DWORD hostlong);