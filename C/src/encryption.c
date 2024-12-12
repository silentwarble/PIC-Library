#include "include/encryption.h"


ULONG pic_rand_number_32(
    VOID
) {
    ULONG Seed = 0;

    Seed = GetTickCount();
    Seed = RtlRandomEx( &Seed );
    Seed = RtlRandomEx( &Seed );
    Seed = ( Seed % ( LONG_MAX - 2 + 1 ) ) + 2;

    return Seed % 2 == 0 ? Seed : Seed + 1;
}


ULONG gen_random_byte(ULONG *seed)
{
    return RtlRandomEx(seed) % 256;
}


/**
 * Using GetTickCount + RtlRandomEx shouldn't be considered
 * cryptographically secure. However, it should be adequate for
 * our purposes. 
 */
void generate_iv(char *iv)
{
    ULONG seed = GetTickCount();

    for(int i = 0; i < IV_SIZE; i++){
        iv[i] = gen_random_byte(&seed);
    }
}

void bcrypt_generate_iv(char *iv)
{
    NTSTATUS status;
    BCRYPT_ALG_HANDLE hAlgorithm;

    status = BCryptOpenAlgorithmProvider(&hAlgorithm, BCRYPT_RNG_ALGORITHM, NULL, 0);
    if (!BCRYPT_SUCCESS(status)) {
        return;
    }

    status = BCryptGenRandom(hAlgorithm, iv, IV_SIZE, 0);
    if (!BCRYPT_SUCCESS(status)) {
        return;
    }

    BCryptCloseAlgorithmProvider(hAlgorithm, 0);
}


int pkcs7_padding_pad_buffer( uint8_t *buffer,  size_t data_length, size_t buffer_size, uint8_t modulus )
{
  uint8_t pad_byte = modulus - ( data_length % modulus ) ;
  if( data_length + pad_byte > buffer_size ){
    return -pad_byte;
  }
  int i = 0;
  while( i <  pad_byte){
    buffer[data_length+i] = pad_byte;
    i++;
  }
  return pad_byte;
}

int pkcs7_padding_valid( uint8_t *buffer, size_t data_length, size_t buffer_size, uint8_t modulus )
{
  uint8_t expected_pad_byte = modulus - ( data_length % modulus ) ;
  if( data_length + expected_pad_byte > buffer_size ){
    return 0;
  }
  int i = 0;
  while( i < expected_pad_byte ){
    if( buffer[data_length + i] != expected_pad_byte){
      return 0;
    }
    i++;
  }
  return 1;
}

size_t pkcs7_padding_data_length( uint8_t * buffer, size_t buffer_size, uint8_t modulus )
{
  /* test for valid buffer size */
  if( buffer_size % modulus != 0 ||
    buffer_size < modulus ){
    return 0;
  }
  uint8_t padding_value;
  padding_value = buffer[buffer_size-1];
  /* test for valid padding value */
  if( padding_value < 1 || padding_value > modulus ){
    return 0;
  }
  /* buffer must be at least padding_value + 1 in size */
  if( buffer_size < padding_value + 1 ){
    return 0;
  }
  uint8_t count = 1;
  buffer_size --;
  for( ; count  < padding_value ; count++){
    buffer_size --;
    if( buffer[buffer_size] != padding_value ){
      return 0;
    }
  }
  return buffer_size;
}