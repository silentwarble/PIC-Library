#include "include/serialization.h"


void write_uint8(uint8_t **buffer, uint8_t value) 
{
    **buffer = value;
    (*buffer)++;
}

void write_uint32(uint8_t **buffer, uint32_t value) 
{ 
    // Little-endian encoding
    for (int i = 0; i < 4; i++) {
        **buffer = (uint8_t)(value & 0xFF); // Write the least significant byte first
        (*buffer)++;
        value >>= 8; // Shift right to get the next byte
    }
}

void write_uint64(uint8_t **buffer, uint64_t value) 
{
    for (size_t i = 0; i < sizeof(uint64_t); i++) {
        **buffer = (uint8_t)(value & 0xFF); 
        (*buffer)++;
        value >>= 8; 
    }
}

void write_string(uint8_t **buffer, const char *str, BOOL include_null)
{
    while (*str) {
        **buffer = *str;
        (*buffer)++;
        str++;
    }
    if (include_null){
        **buffer = 0;
        (*buffer)++;
    }
}

void write_stringW(uint8_t **buffer, const wchar_t *str, BOOL include_null)
{
    while (*str) {
        // Write each wide character (2 bytes)
        **buffer = (uint8_t)(*str & 0xFF);         // Lower byte
        (*buffer)++;
        **buffer = (uint8_t)((*str >> 8) & 0xFF); // Upper byte
        (*buffer)++;
        str++;
    }
    if (include_null) {
        // Write the null terminator (0x0000) as 2 bytes
        **buffer = 0x00;
        (*buffer)++;
        **buffer = 0x00;
        (*buffer)++;
    }
}

void write_bytes(uint8_t **buffer, const char *str, int size)
{
    for (int i = 0; i < size; i++){
        **buffer = *str;
        (*buffer)++;
        str++;
    }
}

uint8_t read_uint8(uint8_t **buffer) 
{
    uint8_t value = **buffer;
    (*buffer)++;
    return value;
}

uint32_t read_uint32(uint8_t **buffer) 
{
    uint32_t value = 0;
    for (int i = 0; i < 4; i++) {
        value |= ((uint32_t)**buffer) << (8 * i);
        (*buffer)++;
    }
    return value;
}

/**
 * You may not need to allocate on the heap. However,
 * unless you've accounted for stack size limitations
 * you may clobber the stack when reading large buffers.
 * It is advised you use HeapAlloc instead of VirtualAlloc. VirtuallAlloc allocates
 * at least 4kb (page). HeapAlloc will alloc just the bytes needed. This is important
 * in something as performance sensitive as serialization. You will need to track
 * the process heap pointer though.
 */
uint8_t* read_bytes(uint8_t **buffer, uint32_t length) 
{
    uint8_t* bytes = (uint8_t*)VirtualAlloc(NULL, length, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!bytes) return NULL;

    memcpy(bytes, *buffer, length);

    *buffer += length;

    return bytes;
}

/**
 * Expects that the string is null terminated. If not, you can use
 * the length param.
 * It is advised you use HeapAlloc instead of VirtualAlloc. VirtuallAlloc allocates
 * at least 4kb (page). HeapAlloc will alloc just the bytes needed. This is important
 * in something as performance sensitive as serialization. You will need to track
 * the process heap pointer though.
 */
char* read_string(uint8_t **buffer, uint32_t length) 
{
    
    uint32_t str_len = 0;
    
    while ((*buffer)[str_len] != '\0'){
        str_len++;
    }
    
    char* str = (char *)VirtualAlloc(NULL, str_len + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!str) return NULL;
    memcpy(str, *buffer, str_len + 1);
    *buffer += str_len + 1;
    return str;
}

/**
 * Expects that the string is null terminated. If not, you can use
 * the length param.
 * It is advised you use HeapAlloc instead of VirtualAlloc. VirtuallAlloc allocates
 * at least 4kb (page). HeapAlloc will alloc just the bytes needed. This is important
 * in something as performance sensitive as serialization. You will need to track
 * the process heap pointer though.
 */
wchar_t* read_stringW(uint8_t **buffer, uint32_t length)
{
    uint32_t str_len = 0;
    
    while (((wchar_t*)(*buffer))[str_len] != L'\0'){
        str_len++;
    }
    
    wchar_t* str = (wchar_t*)VirtualAlloc(NULL, (str_len + 1) * sizeof(wchar_t), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!str) return NULL;
    memcpy(str, *buffer, (str_len + 1) * sizeof(wchar_t));
    *buffer += (str_len + 1) * sizeof(wchar_t);
    return str;
}

/**
 * Our own version of https://learn.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-htonl
 */
DWORD pic_htonl(DWORD hostlong) 
{
    return ((hostlong & 0xFF000000) >> 24) | // Move byte 3 to byte 0
           ((hostlong & 0x00FF0000) >> 8)  | // Move byte 2 to byte 1
           ((hostlong & 0x0000FF00) << 8)  | // Move byte 1 to byte 2
           ((hostlong & 0x000000FF) << 24);   // Move byte 0 to byte 3
}
