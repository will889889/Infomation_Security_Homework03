#include"BlockCipher.h"
#include "aes.h"

void BC_ECB_encrypt(unsigned char *buffer, int length, unsigned char *key)
{
	struct AES_ctx ctx;
	//	set key
	AES_init_ctx(&ctx, key);

	unsigned char buf16[AES_BLOCKLEN];
	//	ignore the last block if the size isn't 16
	for (int i = 0; (i + AES_BLOCKLEN) < length; i+=16)
	{
		for (int b = 0; b < AES_BLOCKLEN; b++)
		{
			buf16[b] = buffer[i + b];
		}
		AES_ECB_encrypt(&ctx, buf16);
		for (int b = 0; b < AES_BLOCKLEN; b++)
		{
			buffer[i + b] = buf16[b];
		}
	}
	/*for (int i = 0; i < 16; i++)
	{
		printf("%02hhx ", buffer[i]);
	}*/
}

void BC_ECB_decrypt(unsigned char *buffer, int length, unsigned char *key)
{
	struct AES_ctx ctx;
	//	set key
	AES_init_ctx(&ctx, key);

	unsigned char buf16[AES_BLOCKLEN];
	//	ignore the last block if the size isn't 16
	for (int i = 0; (i + AES_BLOCKLEN) < length; i += 16)
	{
		for (int b = 0; b < AES_BLOCKLEN; b++)
		{
			buf16[b] = buffer[i + b];
		}
		AES_ECB_decrypt(&ctx, buf16);
		for (int b = 0; b < AES_BLOCKLEN; b++)
		{
			buffer[i + b] = buf16[b];
		}
	}
}

//aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa