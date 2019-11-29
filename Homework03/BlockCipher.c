#include"BlockCipher.h"
#include "aes.h"

void BC_ECB_encrypt(unsigned char *buffer, int length, unsigned char *key)
{
	//AES_BLOCKLEN
	struct AES_ctx ctx;
	AES_init_ctx(&ctx, key);

	for (int i = 0; i < 16; i++)
	{
		printf("%02hhx ", buffer[i]);
	}
	printf("\n");
	AES_ECB_encrypt(&ctx, buffer);

	for (int i = 0; i < 16; i++)
	{
		printf("%02hhx ", buffer[i]);
	}
}

void BC_ECB_decrypt(unsigned char *buffer, int length, unsigned char *key)
{
	struct AES_ctx ctx;
	AES_init_ctx(&ctx, key);

	for (int i = 0; i < 16; i++)
	{
		printf("%02hhx ", buffer[i]);
	}
	printf("\n");
	AES_ECB_decrypt(&ctx, buffer);
	for (int i = 0; i < 16; i++)
	{
		printf("%02hhx ", buffer[i]);
	}
}

//aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa