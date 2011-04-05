//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Rectangle.h"
#include "OpenGL.h"
#include "Screen.h"

#include <string>

using namespace std;

#define Window CWindow::GetInstance()

class CWindow : public Rectangle
{
	public:

		// methods
		void Center(void);
		void Initialize(void);
		void ToggleFullScreen(void);

		// setter
		void SetPosition(const vec2& position);
		void SetPosition(real x, real y);

		void SetDimensions(const vec2& dimensions);
		void SetDimensions(real width, real height);

		void SetTitle(const char* title);

		// getter
		const char* GetTitle(void) const;

	private:

		// variables
		string title;
		bool fullscreen;
		
		// private methods
		static void Reshape(int width, int height);

	public:

		// singleton
		static CWindow& GetInstance(void)
		{
			static CWindow Singleton;
			return Singleton;
		};

	private:	

		CWindow(void);
		CWindow(CWindow const&) {};
		CWindow& operator = (CWindow const&) { return *this; };
		~CWindow(void) {};
};