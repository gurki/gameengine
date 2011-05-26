//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifdef TEXTURES

#pragma once

#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H

#define TextureManager CTextureManager::GetInstance()

#include "OpenGL.h"
#include "Texture.h"

#include <vector>

using namespace std;

struct Image
{
	uint ID;
	const char* Name;
};

class CTextureManager
{
	public:

		void Initialize(void);

		bool LoadTexture(const char* filename);
		bool DeleteTexture(const char* filename);

		bool BindTexture(const char* filename) const;
		void UnbindTexture(void) const;

		void SaveScreenshot(void) const;

	private:

		vector<Image> Textures;

//***************************************************************************//
//                       The TextureManager Singleton                        //
//***************************************************************************//

	public:

		static CTextureManager& GetInstance(void)
		{
			static CTextureManager Singleton;
			return Singleton;
		}

	private:

		CTextureManager(void);
		CTextureManager(CTextureManager const&) {};
        CTextureManager& operator =(CTextureManager const&) { return *this; };
		~CTextureManager(void);		
};

#endif

#endif