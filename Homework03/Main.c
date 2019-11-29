#include "BlockCipher.h"
#include "PPMReader.h"

int main(void)
{
	unsigned char key[] = {
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	};
	unsigned char IV[] = {
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	};
	PPMImage *image;
	unsigned char *buffer;

#pragma region ECB
	//	Encrypt
	image = readPPM("gunter.ppm");

	buffer = PixelData(image);
	BC_ECB_encrypt(buffer, image->x * image->y * 3, key);
	ToPPMImage(buffer, image);

	writePPM("EncryptrdGunter_ECB.ppm", image);

	//	Decrypt
	image = readPPM("EncryptrdGunter_ECB.ppm");

	buffer = PixelData(image);
	BC_ECB_decrypt(buffer, image->x * image->y * 3, key);
	ToPPMImage(buffer, image);

	writePPM("DecryptrdGunter_ECB.ppm", image);
	printf("ECB done\n");
#pragma endregion

#pragma region CBC
	//	Encrypt
	image = readPPM("gunter.ppm");

	buffer = PixelData(image);
	BC_CBC_encrypt(buffer, image->x * image->y * 3, key, IV);
	ToPPMImage(buffer, image);

	writePPM("EncryptrdGunter_CBC.ppm", image);

	//	Decrypt
	image = readPPM("EncryptrdGunter_CBC.ppm");

	buffer = PixelData(image);
	BC_CBC_decrypt(buffer, image->x * image->y * 3, key, IV);
	ToPPMImage(buffer, image);

	writePPM("DecryptrdGunter_CBC.ppm", image);
	printf("CBC done\n");
#pragma endregion
	
#pragma region PPM
	PPMImage *keyImage;
	unsigned char *keyBuffer;

	//	Encrypt
	image = readPPM("gunter.ppm");
	keyImage = readPPM("PPMkey.ppm");

	buffer = PixelData(image);
	keyBuffer = PixelData(keyImage);
	BC_PPM_encrypt(buffer, image->x * image->y * 3, keyBuffer, keyImage->x * keyImage->y * 3);
	ToPPMImage(buffer, image);

	writePPM("EncryptrdGunter_PPM.ppm", image);

	//	Decrypt
	image = readPPM("EncryptrdGunter_PPM.ppm");

	buffer = PixelData(image);
	BC_PPM_decrypt(buffer, image->x * image->y * 3, keyBuffer, keyImage->x * keyImage->y * 3);
	ToPPMImage(buffer, image);

	writePPM("DecryptrdGunter_PPM.ppm", image);
	printf("PPM done\n");
#pragma endregion

	
	system("pause");
	return 0;
}