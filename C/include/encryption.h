/**
 * Sources:
 * https://github.com/silentwarble/Hannibal/blob/main/Payload_Type/hannibal/hannibal/agent_code/Hannibal/src/utility_encryption_helpers.c
 * https://github.com/silentwarble/Hannibal/blob/main/Payload_Type/hannibal/hannibal/agent_code/Hannibal/src/utility_encryption_pkcs7_padding.c
 */

#include <windows.h>
#include <stddef.h> 
#include <stdint.h>



ULONG pic_rand_number_32(VOID);
ULONG gen_random_byte(ULONG *seed);
void generate_iv(char *iv);
void bcrypt_generate_iv(char *iv);
int pkcs7_padding_pad_buffer( uint8_t *buffer,  size_t data_length, size_t buffer_size, uint8_t modulus );
int pkcs7_padding_valid( uint8_t *buffer, size_t data_length, size_t buffer_size, uint8_t modulus );
size_t pkcs7_padding_data_length( uint8_t * buffer, size_t buffer_size, uint8_t modulus );

