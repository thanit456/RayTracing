/*
#include <iostream>

#define stb_image_implementation
#include "stb_image.h"
#define stb_image_write_implementation
#include "stb_image_write.h"

#define CHANNEL_NUM 3

int main()
{



	const int width = 200;
	const int height = 100;

	uint8_t *pixels = new uint8_t[width * height * CHANNEL_NUM];

	int index = 0;

	for (int j = height - 1; j >= 0; j--)
	{
		for (int i = 0; i < width; i++)
		{
			float r = float(i) / float(width);
			float g = float(j) / float(height);
			float b = 0.2;
			int ir = int(255.99*r);
			int ig = int(255.99*g);
			int ib = int(255.99*b);


			pixels[index++] = ir;
			pixels[index++] = ig;
			pixels[index++] = ib;

		}
	}

	stbi_write_png("stbpng.png", width, height, CHANNEL_NUM, pixels, width*CHANNEL_NUM);

	delete[] pixels;

	return 0;
}
*/