#include <stdio.h>
#include <string.h>
#include "aes.h"


int main(void)
{
	/*unsigned char key[] = {
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	};
	unsigned char buf[] = {
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	};*/

	unsigned char key[] = {
	0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef,
	0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef,
	0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef,
	0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef,
	};
	unsigned char iv[] = {
	0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef,
	0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef,
	};
	unsigned char buf[1024*128];
	FILE *fp, *fp2;
	int i, ret, c;
	unsigned char empty[16];

#ifndef AES256
    #error "Need to use AES256"
#endif
	{ // Do encryption 
    	struct AES_ctx ctx;
		fp=fopen("aes.c", "r");
		ret = fread(buf, 1, sizeof(buf), fp);
		fclose(fp);
		fprintf(stderr, "Raw File len=%d, will gen aes.c.enc\n", ret);
		
    	AES_init_ctx_iv(&ctx, key, iv);
		//openssl aes-256-cbc -e -nosalt -v -nopad -K  1234567890abcdef1234567890abcdef1234567890abcdef1234567890abcdef -iv 1234567890abcdef1234567890abcdef -in aes.c -out aes.c.openssl_enc
    	//AES_CBC_encrypt_buffer(&ctx, buf, ret);

		//openssl aes-256-ctr -e -nosalt -v -nopad -K  1234567890abcdef1234567890abcdef1234567890abcdef1234567890abcdef -iv 1234567890abcdef1234567890abcdef -in aes.c -out aes.c.openssl_enc

		AES_CTR_xcrypt_buffer(&ctx, buf, ret);
		fp2=fopen("aes.c.enc", "wb");
		for(i=0;i<ret;i++) {
			c=  buf[i];
			fputc(c, fp2);
		}
		fclose(fp2);
	}
	{ //Do decryption 
		struct AES_ctx ctx;
		fp=fopen("aes.c.enc", "r");
		ret = fread(buf, 1, sizeof(buf), fp);
		fclose(fp);
		fprintf(stderr, "Encrypted len=%d, will gen aes.c.dec\n", ret);

		AES_init_ctx_iv(&ctx, key, iv);
		//AES_CBC_decrypt_buffer(&ctx, buf, ret);
		//AES_CTR_xcrypt_buffer(&ctx, buf, ret);
		for(i=0;i<ret/16;i++) {
			if(i == -1) { 
				fprintf(stderr, "Insert a packet loss simulation in this test.\n");
				//simulate packet loss. kick the counter
				AES_CTR_xcrypt_buffer(&ctx, empty, 16);
				continue;
			}	
			AES_CTR_xcrypt_buffer(&ctx, buf+i*16, 16);
		}
		fp2=fopen("aes.c.dec", "wb");
		for(i=0;i<ret;i++) {
			c=  buf[i];
			fputc(c, fp2);
		}
		fclose(fp2);
	}//
	
	return 0;

}





