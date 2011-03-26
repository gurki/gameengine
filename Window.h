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

		void Initialize(void);

		void SetPosition(const vec2& position);
		void SetPosition(real x, real y);

		void SetDimensions(const vec2& dimensions);
		void SetDimensions(real width, real height);

		void SetTitle(const char* title);

		void SetFullScreen(void);
		
		void Reset(void);
		void Center(void);

		const char* GetTitle(void) const;

	private:

		string title;
		
		static void Reshape(int width, int height);

	public:

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