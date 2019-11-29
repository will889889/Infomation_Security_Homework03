#include <stdio.h>
#include <string.h>
#include "BlockCipher.h"
#include "PPMReader.h"

int main(void)
{
	unsigned char key[] = {
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	};
	unsigned char buf[] = {
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	};

	PPMImage *image;
	image = readPPM("gunter.ppm");
	printf("read ppm done");
	writePPM("EncryptrdGunter.ppm", image);

#ifndef AES256
#error "Need to use AES256"
#endif
	//{ // Do encryption 
	//	struct AES_ctx ctx;
	//	fp = NULL;
	//	fopen_s(fp, "aes.c", "r");
	//	ret = fread(buf, 1, sizeof(buf), fp);
	//	fclose(fp);
	//	fprintf(stderr, "Raw File len=%d, will gen aes.c.enc\n", ret);

	printf("\n\n");

	BC_ECB_decrypt(buf, key);
	
	system("pause");
	return 0;

}