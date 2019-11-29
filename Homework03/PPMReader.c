#include"PPMReader.h"

PPMImage *readPPM(const char *filename)
{
	char buff[16];
	PPMImage *img;
	FILE *fp = NULL;
	int c, rgb_comp_color;
	//open PPM file for reading
	fopen_s(&fp, filename, "rb");
	if (!fp) {
		fprintf(stderr, "Unable to open file '%s'\n", filename);
		exit(1);
	}

	//read image format
	if (!fgets(buff, sizeof(buff), fp)) {
		perror(filename);
		exit(1);
	}

	//check the image format
	if (buff[0] != 'P' || buff[1] != '6') {
		fprintf(stderr, "Invalid image format (must be 'P6')\n");
		exit(1);
	}

	//alloc memory form image
	img = (PPMImage *)malloc(sizeof(PPMImage));
	if (!img) {
		fprintf(stderr, "Unable to allocate memory\n");
		exit(1);
	}

	//check for comments
	c = getc(fp);
	while (c == '#') {
		while (getc(fp) != '\n');
		c = getc(fp);
	}

	ungetc(c, fp);
	//read image size information
	if (fscanf_s(fp, "%d %d", &img->x, &img->y) == 0) {
		fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
		exit(1);
	}

	//read rgb component
	if (fscanf_s(fp, "%d", &rgb_comp_color) == 0) {
		fprintf(stderr, "Invalid rgb component (error loading '%s')\n", filename);
		exit(1);
	}

	//check rgb component depth
	if (rgb_comp_color != RGB_COMPONENT_COLOR) {
		fprintf(stderr, "'%s' does not have 8-bits components\n", filename);
		exit(1);
	}

	while (fgetc(fp) != '\n');
	//memory allocation for pixel data
	img->data = (PPMPixel*)malloc(img->x * img->y * sizeof(PPMPixel));

	if (!img) {
		fprintf(stderr, "Unable to allocate memory\n");
		exit(1);
	}

	//read pixel data from file
	if (fread(img->data, 3 * img->x, img->y, fp) != img->y) {
		fprintf(stderr, "Error loading image '%s'\n", filename);
		exit(1);
	}

	fclose(fp);
	return img;
}
void writePPM(const char *filename, PPMImage *img)
{
	FILE *fp;
	//open file for output
	fopen_s(&fp, filename, "wb");
	if (!fp) {
		fprintf(stderr, "Unable to open file '%s'\n", filename);
		exit(1);
	}

	//write the header file
	//image format
	fprintf(fp, "P6\n");

	//comments
	fprintf(fp, "# Created by %s\n", CREATOR);

	//image size
	fprintf(fp, "%d %d\n", img->x, img->y);

	// rgb component depth
	fprintf(fp, "%d\n", RGB_COMPONENT_COLOR);

	// pixel data
	fwrite(img->data, 3 * img->x, img->y, fp);
	fclose(fp);
}

unsigned char *PixelData(const PPMImage *input)
{
	int lenthOfPixel = input->x * input->y;
	char *output = malloc(sizeof(unsigned char) * lenthOfPixel * 3);

	for (int i = 0; i < lenthOfPixel; i++)
	{
		output[i * 3] = input->data[i].red;
		output[i * 3 + 1] = input->data[i].green;
		output[i * 3 + 2] = input->data[i].blue;
	}

	return output;
}

void ToPPMImage(const unsigned char *input, PPMImage *output)
{
	int lenthOfPixel = output->x * output->y;
	for (int i = 0; i < lenthOfPixel; i++)
	{
		output->data[i].red = input[i * 3];
		output->data[i].green = input[i * 3 + 1];
		output->data[i].blue = input[i * 3 + 2];
	}
}