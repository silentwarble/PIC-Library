/**
 * Note:
 * These can all be adapted to work on another OS, but they have only been tested on Windows.
 * If you aren't linking stdlib you will need to resolve functions such as memcpy or VirtualAlloc.
 * Either write PIC versions or find a way to get a pointer to that function. (See Hannibal for a technique)
 * 
 * Sources:
 * https://github.com/silentwarble/Hannibal/blob/main/Payload_Type/hannibal/hannibal/agent_code/Hannibal/src/utility_strings.c
 * https://github.com/jonatanSh/shelf/blob/master/osals/sprintf.c
 * https://github.com/HavocFramework/Havoc/blob/main/payloads/Demon/src/core/MiniStd.c
 * 
 */

#include <windows.h>
#include <stddef.h> 
#include <stdint.h>

#define min(a,b) __extension__\
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
       _a < _b ? _a : _b; })

enum flag_itoa {
    FILL_ZERO = 1,
    PUT_PLUS = 2,
    PUT_MINUS = 4,
    BASE_2 = 8,
    BASE_10 = 16,
};


ULONG HashString(
    _In_ PVOID  String,
    _In_ SIZE_T Length
);

char* pic_strcpy(char* dest, const char* src);
size_t pic_strlen(const char *str);
size_t pic_strlenW(const wchar_t *wstr);
int pic_strcmp(const char *str1, const char *str2);
int pic_strcmpW(const wchar_t *wstr1, const wchar_t *wstr2);
int pic_strncmp(const char *s1, const char *s2, size_t n);
char* pic_strncpy(char *dest, const char *src, size_t n);
void pic_strcat(char *str1, char *str2);
void pic_strcatW(wchar_t *wstr1, wchar_t *wstr2);

void dword_to_wchar(DWORD value, WCHAR* buffer, int base);
void ulong_to_wchar(ULONG64 value, WCHAR *buffer);

char* sitoa(char * buf, unsigned int num, int width, enum flag_itoa flags);
int vsprintf(char * buf, const char * fmt, va_list va);
int sprintf(char * buf, const char * fmt, ...);

WCHAR ToLowerCaseW( WCHAR C );
PCHAR StringCopyA(PCHAR String1, PCHAR String2);
PWCHAR StringCopyW(PWCHAR String1, PWCHAR String2);
SIZE_T StringLengthA(LPCSTR String);
SIZE_T StringLengthW(LPCWSTR String);
PCHAR StringConcatA(PCHAR String, PCHAR String2);
PWCHAR StringConcatW(PWCHAR String, PWCHAR String2);
LPWSTR WcsStr( PWCHAR String, PWCHAR String2 );
LPWSTR WcsIStr( PWCHAR String, PWCHAR String2 );
SIZE_T WCharStringToCharString(PCHAR Destination, PWCHAR Source, SIZE_T MaximumAllowed);
SIZE_T CharStringToWCharString( PWCHAR Destination, PCHAR Source, SIZE_T MaximumAllowed );
