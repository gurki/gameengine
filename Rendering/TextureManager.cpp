//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifdef TEXTURES

#include "TextureManager.h"

void CTextureManager::Initialize(void) {}

CTextureManager::CTextureManager(void)
{
	glEnable(GL_TEXTURE_2D);

	if(ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
	{
		exit(false);
	}

	ilInit();
	iluInit();
	ilutInit();

	ilEnable(IL_FILE_OVERWRITE);

	ilutRenderer(ILUT_OPENGL);
}

CTextureManager::~CTextureManager(void)
{
	for(unsigned int i = 0; i < Textures.size(); i++)
	{
		glDeleteTextures(1, &Textures[i].ID);
	}

	ilShutDown();

	glDisable(GL_TEXTURE_2D);
}

bool CTextureManager::LoadTexture(const char *filename)
{
	uint id = ilutGLLoadImage((char *)filename);

	if(id == 0)
	{
		return false;
	}

	Textures.push_back(Image());
	Textures.back().Name = filename;
	Textures.back().ID = id;

	UnbindTexture();

	return true;
}

bool CTextureManager::BindTexture(const char *filename) const
{
	for(uint i = 0; i < Textures.size(); i++) 
	{
		if(Textures[i].Name == filename) 
		{
			glBindTexture(GL_TEXTURE_2D, Textures.back().ID);

			return true;
		}
	}	

	return false;
}

bool CTextureManager::DeleteTexture(const char *filename)
{
	for(uint i = 0; i < Textures.size(); i++) 
	{
		if(Textures[i].Name == filename) 
		{
			glDeleteTextures(1, &Textures[i].ID);

			return true;
		}
	}	

	return false;
}

void CTextureManager::UnbindTexture(void) const
{
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void CTextureManager::SaveScreenshot(void) const
{
	// increase counter
	static uint counter = 0;
	counter++;

	// update filename
	char filename[32];
	sprintf_s(filename, 32, "Screenshot %04i.png", counter);

	// get windowdata
	uint width = glutGet(GLUT_WINDOW_WIDTH);
	uint height = glutGet(GLUT_WINDOW_HEIGHT);

	uchar* Data = new uchar[width * height * 3];

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid *)Data); 

	// create and save image
	uint imageHandle = NULL;

	ilGenImages(1, &imageHandle);
	ilBindImage(imageHandle);

	ilTexImage(width, height, 1, 3, IL_RGB, IL_UNSIGNED_BYTE, Data);
	
	if(ilSave(IL_PNG, filename) == false) 
	{
		counter--;	
	}

	// clean up
	ilDeleteImages(1, &imageHandle);

	delete[] Data;
}

#endif
