//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _COLOR_H
#define _COLOR_H

/* TODO 

- damn error RGB->HSV algorithm!!

- mix colors (RYB!)

- RYB
- YIQ
- XYZ
- CIELAB

*/

enum COLORS
{
	BLACK,
	GRAY,
	SILVER,
	WHITE,
	RED,
	VERMILLION,
	ORANGE,
	AMBER,
	YELLOW,
	CHARTREUSE,
	GREEN,
	AQUAMARINE,
	BLUE,
	INDIGO,
	PURPLE,
	MAGENTA
};

class Color
{
	public:

		Color(void);

		Color(unsigned int R, unsigned int G, unsigned int B, float Alpha = 1.0f);

		void Bind(void);

		void ShiftCW(float value);
		void ShiftCCW(float value);

		void Darken(float value);
		void Lighten(float value);

		void Saturate(float value);
		void Desaturate(float value);

		void SetAlpha(float Alpha);
		void SetGray(float Gray, float Alpha = 1.0f);
		void SetHLS(float H, float L, float S, float Alpha = 1.0f);
		void SetHSV(float H, float S, float V, float Alpha = 1.0f);
		void SetRGB(float R, float G, float B, float Alpha = 1.0f);
		void SetCMY(float C, float M, float Y, float Alpha = 1.0f);
		void SetCMYK(float C, float M, float Y, float K, float Alpha = 1.0f);

		void GetAlpha(float& Alpha);
		void GetGray(float& Gray);
		void GetHLS(float& H, float& S, float& L);
		void GetHSV(float& H, float& S, float& V);
		void GetRGB(float& R, float& G, float& B);
		void GetCMY(float& C, float& M, float& Y);
		void GetCMYK(float& C, float& M, float& Y, float& K);

		float Gray(void);
		float Alpha(void);
		float* GetHLS(void);
		float* GetHSV(void);
		float* GetRGB(void);
		float* GetCMY(void);
		float* GetCMYK(void);

		static Color& GetColor(unsigned int color);

		void Print(void);

		void PrintHLS(void);
		void PrintHSV(void);
		void PrintRGB(void);
		void PrintCMY(void);
		void PrintCMYK(void);

	private:

		void HLStoRGB(void);
		void HSVtoRGB(void);
		void CMYtoRGB(void);
		void CMYKtoRGB(void);

		void RGBtoHLS(void);
		void RGBtoHSV(void);
		void RGBtoCMY(void);
		void RGBtoCMYK(void);

		float HLS[3];
		float HSV[3];
		float RGB[3];
		float CMY[3];
		float CMYK[4];

		float A;
};

#endif