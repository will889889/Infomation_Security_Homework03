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

	printf("Please enter the key (16 bytes as hex):\n");
	for (int i = 0; i < 16; i++)
	{
		unsigned int temp;
		scanf_s("%x", &temp);
		key[i] = temp;
	}
	printf("Please enter the Initial Vector (16 bytes as hex):\n");
	for (int i = 0; i < 16; i++)
	{
		unsigned int temp;
		scanf_s("%x", &temp);
		IV[i] = temp;
	}
	/*for (int i = 0; i < 16; i++)
	{
		printf("%02hhx ", key[i]);
	}*/

#pragma region ECB
	//	Encrypt
	image = readPPM("PlainImage.ppm");

	buffer = PixelData(image);
	BC_ECB_encrypt(buffer, image->x * image->y * 3, key);
	ToPPMImage(buffer, image);

	writePPM("EncryptedImage_ECB.ppm", image);

	//	Decrypt
	image = readPPM("EncryptedImage_ECB.ppm");

	buffer = PixelData(image);
	BC_ECB_decrypt(buffer, image->x * image->y * 3, key);
	ToPPMImage(buffer, image);

	writePPM("DecryptedImage_ECB.ppm", image);
	printf("ECB done\n");
#pragma endregion

#pragma region CBC
	//	Encrypt
	image = readPPM("PlainImage.ppm");

	buffer = PixelData(image);
	BC_CBC_encrypt(buffer, image->x * image->y * 3, key, IV);
	ToPPMImage(buffer, image);

	writePPM("EncryptedImage_CBC.ppm", image);

	//	Decrypt
	image = readPPM("EncryptedImage_CBC.ppm");

	buffer = PixelData(image);
	BC_CBC_decrypt(buffer, image->x * image->y * 3, key, IV);
	ToPPMImage(buffer, image);

	writePPM("DecryptedImage_CBC.ppm", image);
	printf("CBC done\n");
#pragma endregion
	
#pragma region PPM
	PPMImage *keyImage;
	unsigned char *keyBuffer;

	//	Encrypt
	image = readPPM("PlainImage.ppm");
	keyImage = readPPM("PPMkey.ppm");

	buffer = PixelData(image);
	keyBuffer = PixelData(keyImage);
	BC_PPM_encrypt(buffer, image->x * image->y * 3, keyBuffer, keyImage->x * keyImage->y * 3);
	ToPPMImage(buffer, image);

	writePPM("EncryptedImage_PPM.ppm", image);

	//	Decrypt
	image = readPPM("EncryptedImage_PPM.ppm");

	buffer = PixelData(image);
	BC_PPM_decrypt(buffer, image->x * image->y * 3, keyBuffer, keyImage->x * keyImage->y * 3);
	ToPPMImage(buffer, image);

	writePPM("DecryptedImage_PPM.ppm", image);
	printf("PPM done\n");
#pragma endregion

	system("pause");
	return 0;
}