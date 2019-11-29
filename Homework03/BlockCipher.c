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

void BC_CBC_encrypt(unsigned char *buffer, int length, unsigned char *key, unsigned char *IV)
{
	struct AES_ctx ctx;
	//	set key
	AES_init_ctx(&ctx, key);

	//	Chaining Vector
	unsigned char chainingVector[AES_BLOCKLEN];
	for (int v = 0; v < AES_BLOCKLEN; v++)
	{
		chainingVector[v] = IV[v];
	}
	unsigned char buf16[AES_BLOCKLEN];
	//	ignore the last block if the size isn't 16
	for (int i = 0; (i + AES_BLOCKLEN) < length; i += 16)
	{
		//	get plaintext
		for (int b = 0; b < AES_BLOCKLEN; b++)
		{
			buf16[b] = buffer[i + b];
		}
		//	xor chainingVector with plaintext
		for (int v = 0; v < AES_BLOCKLEN; v++)
		{
			buf16[v] = chainingVector[v] ^ buf16[v];
		}
		//	encrypt
		AES_ECB_encrypt(&ctx, buf16);
		//	writeback ciphertext, update chainingVector
		for (int b = 0; b < AES_BLOCKLEN; b++)
		{
			buffer[i + b] = buf16[b];
			chainingVector[b] = buf16[b];
		}
	}
}

void BC_CBC_decrypt(unsigned char *buffer, int length, unsigned char *key, unsigned char *IV)
{
	struct AES_ctx ctx;
	//	set key
	AES_init_ctx(&ctx, key);

	//	Chaining Vector
	unsigned char chainingVector[AES_BLOCKLEN];
	for (int v = 0; v < AES_BLOCKLEN; v++)
	{
		chainingVector[v] = IV[v];
	}
	unsigned char buf16[AES_BLOCKLEN];
	//	ignore the last block if the size isn't 16
	for (int i = 0; (i + AES_BLOCKLEN) < length; i += 16)
	{
		//	get plaintext
		for (int b = 0; b < AES_BLOCKLEN; b++)
		{
			buf16[b] = buffer[i + b];
		}
		//	decrypt
		AES_ECB_decrypt(&ctx, buf16);
		//	xor chainingVector with plaintext
		for (int v = 0; v < AES_BLOCKLEN; v++)
		{
			buf16[v] = chainingVector[v] ^ buf16[v];
		}

		//	writeback ciphertext, update chainingVector
		for (int b = 0; b < AES_BLOCKLEN; b++)
		{
			chainingVector[b] = buffer[i + b];
			buffer[i + b] = buf16[b];
		}
	}
}

void BC_PPM_encrypt(unsigned char *buffer, int length, unsigned char *key, int keyLength)
{
	struct AES_ctx ctx;
	unsigned char buf16[AES_BLOCKLEN];
	unsigned char key16[AES_BLOCKLEN];
	int k = 0;

	//	ignore the last block if the size isn't 16
	for (int i = 0; (i + AES_BLOCKLEN) < length; i += AES_BLOCKLEN)
	{
		for (int b = 0; b < AES_BLOCKLEN; b++)
		{
			buf16[b] = buffer[i + b];
			key16[b] = key[k + b];
		}
		AES_init_ctx(&ctx, key16);
		AES_ECB_encrypt(&ctx, buf16);
		for (int b = 0; b < AES_BLOCKLEN; b++)
		{
			buffer[i + b] = buf16[b];
		}
		
		k+= AES_BLOCKLEN;
		if (k + AES_BLOCKLEN >= keyLength)
			k = 0;
	}
}

void BC_PPM_decrypt(unsigned char *buffer, int length, unsigned char *key, int keyLength)
{
	struct AES_ctx ctx;
	unsigned char buf16[AES_BLOCKLEN];
	unsigned char key16[AES_BLOCKLEN];
	int k = 0;

	//	ignore the last block if the size isn't 16
	for (int i = 0; (i + AES_BLOCKLEN) < length; i += AES_BLOCKLEN)
	{
		for (int b = 0; b < AES_BLOCKLEN; b++)
		{
			buf16[b] = buffer[i + b];
			key16[b] = key[k + b];
		}
		AES_init_ctx(&ctx, key16);
		AES_ECB_decrypt(&ctx, buf16);
		for (int b = 0; b < AES_BLOCKLEN; b++)
		{
			buffer[i + b] = buf16[b];
		}

		k += AES_BLOCKLEN;
		if (k + AES_BLOCKLEN >= keyLength)
			k = 0;
	}
}