//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Texture.h"

#ifdef TEXTURES

// constructors
Texture::Texture(void)
{
	width = 0;
	height = 0;
	size = 0;

	channels = 4;
	format = IL_RGBA;

	dataSize = 0;
	data = 0;
}

Texture::~Texture(void)
{
	if(data != 0)
	{
		delete[] data;

		data = 0;
	}
	
	width = 0;
	height = 0;
	size = 0;

	channels = 4;
	format = IL_RGBA;

	dataSize = 0;
}

// methods
void Texture::Save(const char* filename)
{
	uint handle = 0;

	ilGenImages(1, &handle);
	ilBindImage(handle);

	ilTexImage(width, height, 0, channels, format, IL_FLOAT, data);
	ilConvertImage(format, IL_UNSIGNED_BYTE);
	ilSaveImage(filename);

	ilDeleteImage(handle);
	ilBindImage(0);
}

bool Texture::Load(const char* filename)
{
	uint handle = 0;

	ilGenImages(1, &handle);
	ilBindImage(handle);

	if(ilLoadImage(filename))
	{
		this->~Texture();
				
		width = ilGetInteger(IL_IMAGE_WIDTH);
		height = ilGetInteger(IL_IMAGE_HEIGHT);
		size = width * height;
		
		channels = ilGetInteger(IL_IMAGE_BPP);
		format = ilGetInteger(IL_IMAGE_FORMAT);

		ilConvertImage(format, IL_FLOAT);
	
		dataSize = ilGetInteger(IL_IMAGE_SIZE_OF_DATA);

		data = new float[dataSize];
		memcpy(data, (float*)ilGetData(), dataSize);

		ilDeleteImage(handle);
		ilBindImage(0);

		return true;
	}

	ilDeleteImage(handle);
	ilBindImage(0);

	return false;
}

void Texture::GenerateTexture(uint width, uint height, uint channels)
{
	this->~Texture();

	this->width = width;
	this->height = height;
	size = width * height;

	this->channels = channels;

	switch(channels)
	{
		case 1:
			format = IL_LUMINANCE;
			break;

		case 2:
			format = IL_LUMINANCE_ALPHA;
			break;

		case 3:
			format = IL_RGB;
			break;

		default:
			this->channels = 4;
			format = IL_RGBA;
			break;
	}
		
	dataSize = size * channels * sizeof(float);

	data = new float[size * channels];
	memset(data, 0, dataSize);
}

// getter
uint Texture::GetWidth(void) const
{
	return width;
}

uint Texture::GetHeight(void) const
{
	return height;
}

uint Texture::GetSize(void) const
{
	return size;
}

float* Texture::GetData(void) const
{
	return data;
}

#endif