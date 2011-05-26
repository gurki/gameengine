//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Types.h"
#include <iostream>

using namespace std;

/* TODO 

- damn error RGB->HSV algorithm!!

- mix colors (RYB!)

- RYB
- YIQ
- XYZ
- CIELAB

*/

class Color
{
	public:

		// constructors
		Color(void);
		Color(float R, float G, float B, float A = 1.0f);

		// functionality
		void Bind(void) const;

		// 
		Color& ShiftCW(float value);
		Color& ShiftCCW(float value);

		Color& Darken(float value);
		Color& Lighten(float value);

		Color& Saturate(float value);
		Color& Desaturate(float value);

		Color& SetAlpha(float Alpha);

		// static getter
		static Color WithLuminance(float L, float A = 1.0f);
		static Color WithHLS(float H, float L, float S, float A = 1.0f);
		static Color WithHSV(float H, float S, float V, float A = 1.0f);
		static Color WithRGB(float R, float G, float B, float A = 1.0f);
		static Color WithUnsignedRGB(uint R, uint G, uint B, float A = 1.0f);
		static Color WithCMY(float C, float M, float Y, float A = 1.0f);
		static Color WithCMYK(float C, float M, float Y, float K, float A = 1.0f);

		static Color WithBlack(void);
		static Color WithGray(void);
		static Color WithSilver(void);
		static Color WithWhite(void);

		static Color WithRed(void);
		static Color WithRedOrange(void); // vermillion
		static Color WithOrange(void);
		static Color WithYellowOrange(void); // amber
		static Color WithYellow(void);
		static Color WithYellowGreen(void); // chartreuse
		static Color WithGreen(void);
		static Color WithBlueGreen(void); // aquamarine
		static Color WithBlue(void);
		static Color WithBluePurple(void); // indigo
		static Color WithPurple(void);
		static Color WithRedPurple(void);  // magenta

		// getter
		float* GetHLS(void);
		float* GetHSV(void);
		float* GetRGB(void);
		float* GetCMY(void);
		float* GetCMYK(void);

		float GetAlpha(void);
		
		friend ostream& operator << (ostream& out, const Color& c);
		friend istream& operator >> (istream& in, Color& c);

		// variables
		float v[4];

	private:

		void CMYKtoRGB(void);

		void RGBtoHLS(void);
		void RGBtoHSV(void);
		void RGBtoCMY(void);
		void RGBtoCMYK(void);

		static float conv[5];
};