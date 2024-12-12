#include "include/strings.h"

/*!
 * @brief
 *  Hashing data
 *
 * @param String
 *  Data/String to hash
 *
 * @param Length
 *  size of data/string to hash.
 *  if 0 then hash data til null terminator is found.
 *
 * @return
 *  hash of specified data/string
 */
ULONG HashString(
    _In_ PVOID  String,
    _In_ SIZE_T Length
) {
    ULONG  Hash = { 0 };
    PUCHAR Ptr  = { 0 };
    UCHAR  Char = { 0 };

    if ( ! String ) {
        return 0;
    }

    Hash = H_MAGIC_KEY;
    Ptr  = ( ( PUCHAR ) String );

    do {
        Char = *Ptr;

        if ( ! Length ) {
            if ( ! *Ptr ) break;
        } else {
            if ( (UINT_PTR)( Ptr - (UINT_PTR)( String ) ) >= Length ) break;
            if ( !*Ptr ) ++Ptr;
        }

        if ( Char >= 'a' ) {
            Char -= 0x20;
        }

        Hash = ( ( Hash << 5 ) + Hash ) + Char;

        ++Ptr;
    } while ( TRUE );

    return Hash;
}



char* pic_strcpy(char* dest, const char* src) 
{
    char* d = dest;
    const char* s = src;
    
    // Copy characters one by one until the null terminator is found
    while ((*d++ = *s++)) {
        // Loop continues until null terminator is copied
    }
    
    return dest;
}

size_t pic_strlen(const char *str) 
{ // Len not including null terminator
    const char *s = str;
    while (*s != '\0') {
        s++;
    }
    return (size_t)(s - str);
}

size_t pic_strlenW(const wchar_t *wstr) 
{
    const wchar_t *s = wstr;
    while (*s != L'\0') {
        s++;
    }
    return (size_t)(s - wstr);
}

/*
    0: If the strings are identical up to the end of the shortest string (i.e., they are equal).
    Positive Value: If the first differing character in str1 is greater than the corresponding character in str2.
    Negative Value: If the first differing character in str1 is less than the corresponding character in str2.
*/
int pic_strcmp(const char *str1, const char *str2)
{
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

int pic_strcmpW(const wchar_t *wstr1, const wchar_t *wstr2) 
{
    while (*wstr1 && (*wstr1 == *wstr2)) {
        wstr1++;
        wstr2++;
    }
    return (int)(*wstr1 - *wstr2);
}

int pic_strncmp(const char *s1, const char *s2, size_t n) 
{
    // Compare up to `n` characters or until a null terminator is encountered
    while (n > 0 && *s1 && *s2) {
        if (*s1 != *s2) {
            return (unsigned char)*s1 - (unsigned char)*s2;
        }
        s1++;
        s2++;
        n--;
    }
    
    // If we've exhausted the `n` characters, or one string ended
    if (n == 0) {
        return 0;
    }
    
    // If any of the strings are terminated, return the difference of the characters
    if (*s1 != *s2) {
        return (unsigned char)*s1 - (unsigned char)*s2;
    }
    
    return 0;
}

char *pic_strncpy(char *dest, const char *src, size_t n)
{
    char *d = dest;
    const char *s = src;
    
    while (n > 0) {
        if (*s == '\0') {
            // If the source string ends, fill the rest with null bytes
            *d = '\0';
            while (--n > 0) {
                *(++d) = '\0';
            }
            break;
        }
        // Copy the character from source to destination
        *d++ = *s++;
        --n;
    }
    
    // If n reaches 0, ensure null-termination
    if (n == 0) {
        *d = '\0';
    }
    
    return dest;
}

void pic_strcat(char *str1, char *str2)
{
    int i, j=0;

    //Copying string 2 to the end of string 1
    for( i=pic_strlen(str1); str2[j]!='\0'; i++ ) {
        str1[i]=str2[j];
        j++;
    }

    str1[i]='\0';
}

void pic_strcatW(wchar_t *wstr1, wchar_t *wstr2)
{
    // Find the end of the first wide string
    wchar_t *end = wstr1;
    while (*end != L'\0') {
        end++;
    }

    // Append the second wide string to the end of the first one
    while (*wstr2 != L'\0') {
        *end = *wstr2;
        end++;
        wstr2++;
    }
    // Null-terminate the concatenated string
    *end = L'\0';
}

// Helper function to convert DWORD to WCHAR string
void dword_to_wchar(DWORD value, WCHAR* buffer, int base) 
{
    WCHAR* ptr = buffer;
    WCHAR* ptr1 = buffer;
    WCHAR tmp_char;
    DWORD quotient = value;

    // Handle 0 explicitly
    if (value == 0) {
        *ptr++ = L'0';
        *ptr = L'\0';
        return;
    }

    // Convert to string
    while (quotient != 0) {
        DWORD digit = quotient % base;
        *ptr++ = (WCHAR)(digit < 10 ? L'0' + digit : L'A' + digit - 10);
        quotient /= base;
    }
    *ptr-- = L'\0';

    // Reverse the string
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
}


void ulong_to_wchar(ULONG64 value, WCHAR *buffer) 
{
    WCHAR* ptr = buffer;
    WCHAR* ptr1 = buffer;
    WCHAR tmp_char;
    ULONG64 quotient = value;

    // Handle 0 explicitly
    if (value == 0) {
        *ptr++ = L'0';
        *ptr = L'\0';
        return;
    }

    // Convert to string
    while (quotient != 0) {
        ULONG64 digit = quotient % 10;
        *ptr++ = (WCHAR)(digit < 10 ? L'0' + digit : L'A' + digit - 10);
        quotient /= 10;
    }
    *ptr-- = L'\0';

    // Reverse the string
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
}



char * sitoa(char * buf, unsigned int num, int width, enum flag_itoa flags)
{
    unsigned int base;
    if (flags & BASE_2)
        base = 2;
    else if (flags & BASE_10)
        base = 10;
    else
        base = 16;

    char tmp[32];
    char *p = tmp;
    do {
        int rem = num % base;
        *p++ = (rem <= 9) ? (rem + '0') : (rem + 'a' - 0xA);
    } while ((num /= base));
    width -= p - tmp;
    char fill = (flags & FILL_ZERO)? '0' : ' ';
    while (0 <= --width) {
        *(buf++) = fill;
    }
    if (flags & PUT_MINUS)
        *(buf++) = '-';
    else if (flags & PUT_PLUS)
        *(buf++) = '+';
    do
        *(buf++) = *(--p);
    while (tmp < p);
    return buf;
}

int vsprintf(char * buf, const char * fmt, va_list va)
{
    char c;
    const char *save = buf;

    while ((c  = *fmt++)) {
        int width = 0;
        enum flag_itoa flags = 0;
        if (c != '%') {
            *(buf++) = c;
            continue;
        }
    redo_spec:
        c  = *fmt++;
        switch (c) {
        case '%':
            *(buf++) = c;
            break;
        case 'c':;
            *(buf++) = va_arg(va, int);
            break;
        case 'd':;
            int num = va_arg(va, int);
            if (num < 0) {
                num = -num;
                flags |= PUT_MINUS;
            }
            buf = sitoa(buf, num, width, flags | BASE_10);
            break;
        case 'u':
            buf = sitoa(buf, va_arg(va, unsigned int), width, flags | BASE_10);
            break;
        case 'x':
            buf = sitoa(buf, va_arg(va, unsigned int), width, flags);
            break;
        case 'b':
            buf = sitoa(buf, va_arg(va, unsigned int), width, flags | BASE_2);
            break;
        case 's':;
            const char *p  = va_arg(va, const char *);
            if (p) {
                while (*p)
                    *(buf++) = *(p++);
            }
            break;
        case 'm':;
            const uint8_t *m  = va_arg(va, const uint8_t *);
            width = min(width, 64); // buffer limited to 256!
            if (m)
                for (;;) {
                    buf = sitoa(buf, *(m++), 2, FILL_ZERO);
                    if (--width <= 0)
                        break;
                    *(buf++) = ':';
                }
            break;
        case '0':
            if (!width)
                flags |= FILL_ZERO;
            // fall through
        case '1'...'9':
            width = width * 10 + c - '0';
            goto redo_spec;
        case '*':
            width = va_arg(va, unsigned int);
            goto redo_spec;
        case '+':
            flags |= PUT_PLUS;
            goto redo_spec;
        case '\0':
        default:
            *(buf++) = '?';
        }
        width = 0;
    }
    *buf = '\0';
    return buf - save;
}

int sprintf(char * buf, const char * fmt, ...)
{
    va_list va;
    va_start(va,fmt);
    int ret = vsprintf(buf, fmt, va);
    va_end(va);
    return ret;
}






// https://github.com/HavocFramework/Havoc/blob/main/payloads/Demon/src/core/MiniStd.c

WCHAR ToLowerCaseW( WCHAR C )
{
    return C > 0x40 && C < 0x5b ? C | 0x60 : C;
}


PCHAR StringCopyA(PCHAR String1, PCHAR String2)
{
    PCHAR p = String1;

    while ((*p++ = *String2++) != 0);

    return String1;
}

PWCHAR StringCopyW(PWCHAR String1, PWCHAR String2)
{
    PWCHAR p = String1;

    while ((*p++ = *String2++) != 0);

    return String1;
}

SIZE_T StringLengthA(LPCSTR String)
{
    LPCSTR String2;

    if ( String == NULL )
        return 0;

    for (String2 = String; *String2; ++String2);

    return (String2 - String);
}

SIZE_T StringLengthW(LPCWSTR String)
{
    LPCWSTR String2;

    for (String2 = String; *String2; ++String2);

    return (String2 - String);
}

PCHAR StringConcatA(PCHAR String, PCHAR String2)
{
    StringCopyA( &String[ StringLengthA( String ) ], String2 );

    return String;
}

PWCHAR StringConcatW(PWCHAR String, PWCHAR String2)
{
    StringCopyW( &String[ StringLengthW( String ) ], String2 );

    return String;
}

LPWSTR WcsStr( PWCHAR String, PWCHAR String2 )
{
    if ( ! String || ! String2 )
        return NULL;

    UINT32 Size1 = StringLengthW( String );
    UINT32 Size2 = StringLengthW( String2 );

    if ( Size2 > Size1 )
        return NULL;

    for ( UINT32 i = 0; i < Size1 - Size2 + 1; i++ )
    {
        if ( StringNCompareW( String + i, String2, Size2 ) == 0 )
            return String + i;
    }

    return NULL;
}

LPWSTR WcsIStr( PWCHAR String, PWCHAR String2 )
{
    if ( ! String || ! String2 )
        return NULL;

    UINT32 Size1 = StringLengthW( String );
    UINT32 Size2 = StringLengthW( String2 );

    if ( Size2 > Size1 )
        return NULL;

    for ( UINT32 i = 0; i < Size1 - Size2 + 1; i++ )
    {
        if ( StringNCompareIW( String + i, String2, Size2 ) == 0 )
            return String + i;
    }

    return NULL;
}

SIZE_T WCharStringToCharString(PCHAR Destination, PWCHAR Source, SIZE_T MaximumAllowed)
{
    INT Length = MaximumAllowed;

    while (--Length >= 0)
    {
        if (!(*Destination++ = *Source++))
            return MaximumAllowed - Length - 1;
    }

    return MaximumAllowed - Length;
}

SIZE_T CharStringToWCharString( PWCHAR Destination, PCHAR Source, SIZE_T MaximumAllowed )
{
    INT Length = (INT)MaximumAllowed;

    while (--Length >= 0)
    {
        if ( ! ( *Destination++ = *Source++ ) )
            return MaximumAllowed - Length - 1;
    }

    return MaximumAllowed - Length;
}