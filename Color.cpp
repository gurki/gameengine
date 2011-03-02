//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Color.h"
#include "MathLib.h"

#include "OpenGL.h"

#include <cstdio>

Color::Color(void)
{
	SetRGB(1.0f, 1.0f, 1.0f, 1.0f);
}

Color::Color(unsigned int R, unsigned int G, unsigned int B, float Alpha)
{
	SetRGB(R / 255.0f, G / 255.0f, B / 255.0f, Alpha);
}

void Color::ShiftCW(float value)
{
	SetHLS(HLS[0] - value, HLS[1], HLS[2], A);
}

void Color::ShiftCCW(float value)
{
	SetHLS(HLS[0] + value, HLS[1], HLS[2], A);
}

void Color::Darken(float value)
{
	SetHLS(HLS[0], HLS[1] - value, HLS[2], A);
}

void Color::Lighten(float value)
{
	SetHLS(HLS[0], HLS[1] + value, HLS[2], A);
}

void Color::Saturate(float value)
{
	SetHLS(HLS[0], HLS[1], HLS[2] + value, A);
	// SetHSV(HSV[0], HSV[1] + value, HSV[2], A);
}

void Color::Desaturate(float value)
{
	SetHLS(HLS[0], HLS[1], HLS[2] - value, A);
	// SetHSV(HSV[0], HSV[1] - value, HSV[2], A);
}

void Color::SetGray(float Gray, float Alpha)
{
	SetHLS(0.0f, Gray, 0.0f, Alpha);
}

void Color::SetAlpha(float Alpha)
{
	A = limit(Alpha, 0.0f, 1.0f);
}

void Color::SetHLS(float H, float L, float S, float Alpha)
{
	HLS[0] = modf(H, 1.0f);
	HLS[1] = limit(L, 0.0f, 1.0f);
	HLS[2] = limit(S, 0.0f, 1.0f);

	SetAlpha(Alpha);

	HLStoRGB();
	
	RGBtoHSV();
	RGBtoCMY();
	RGBtoCMYK();
}

void Color::SetHSV(float H, float S, float V, float Alpha)
{
	HSV[0] = modf(H, 1.0f);
	HSV[1] = limit(S, 0.0f, 1.0f);
	HSV[2] = limit(V, 0.0f, 1.0f);

	SetAlpha(Alpha);

	HSVtoRGB();

	RGBtoHLS();
	RGBtoCMY();
	RGBtoCMYK();
}

void Color::SetRGB(float R, float G, float B, float Alpha)
{
	RGB[0] = limit(R, 0.0f, 1.0f);
	RGB[1] = limit(G, 0.0f, 1.0f);
	RGB[2] = limit(B, 0.0f, 1.0f);

	SetAlpha(Alpha);

	RGBtoHSV();
	RGBtoHLS();
	RGBtoCMY();
	RGBtoCMYK();
}

void Color::SetCMY(float C, float M, float Y, float Alpha)
{
	CMY[0] = limit(C, 0.0f, 1.0f);
	CMY[1] = limit(M, 0.0f, 1.0f);
	CMY[2] = limit(Y, 0.0f, 1.0f);

	SetAlpha(Alpha);

	CMYtoRGB();

	RGBtoHSV();
	RGBtoHLS();
	RGBtoCMYK();
}

void Color::SetCMYK(float C, float M, float Y, float K, float Alpha)
{
	CMYK[0] = limit(C, 0.0f, 1.0f);
	CMYK[1] = limit(M, 0.0f, 1.0f);
	CMYK[2] = limit(Y, 0.0f, 1.0f);
	CMYK[3] = limit(K, 0.0f, 1.0f);

	SetAlpha(Alpha);

	CMYKtoRGB();

	RGBtoHSV();
	RGBtoHLS();
	RGBtoCMY();
}

void Color::GetGray(float& Gray)
{
	Gray = HLS[1];
}

void Color::GetAlpha(float& Alpha)
{
	Alpha = A;
}

void Color::GetHLS(float& H, float& S, float& L)
{
	H = HLS[0];
	S = HLS[1];
	L = HLS[2];
}

void Color::GetHSV(float& H, float& S, float& V)
{
	H = HSV[0];
	S = HSV[1];
	V = HSV[2];
}

void Color::GetRGB(float& R, float& G, float& B)
{
	R = RGB[0];
	G = RGB[1];
	B = RGB[2];
}

void Color::GetCMY(float& C, float& M, float& Y)
{
	C = CMY[0];
	M = CMY[1];
	Y = CMY[2];
}

void Color::GetCMYK(float& C, float& M, float& Y, float& K)
{
	C = CMYK[0];
	M = CMYK[1];
	Y = CMYK[2];
	K = CMYK[3];
}

float Color::Alpha(void) { return A; }
float Color::Gray(void) { return HLS[1]; }
float* Color::GetHLS(void) { return HLS; }
float* Color::GetHSV(void) { return HSV; }
float* Color::GetRGB(void) { return RGB; }
float* Color::GetCMY(void) { return CMY; }
float* Color::GetCMYK(void) { return CMYK; }


Color& Color::GetColor(unsigned int color)
{
	switch(color)
	{
		case BLACK: {
			static Color black(0x00, 0x00, 0x00);
			return black; }
			
		case GRAY: {
			static Color gray(0x80, 0x80, 0x80);
			return gray; }
			
		case SILVER: {
			static Color silver(0xC0, 0xC0, 0xC0);
			return silver; }

		case RED: {
			static Color red(0xFF, 0x00, 0x00);
			return red; }
	
		case VERMILLION: {
			static Color vermillion(0xE3, 0x42, 0x34); 
			return vermillion; }
	
		case ORANGE: {
			static Color orange(0xFF, 0x7F, 0x00);
			return orange; }
	
		case AMBER: {
			static Color amber(0xFF, 0xBF, 0x00);
			return amber; }
	
		case YELLOW: {
			static Color yellow(0xFF, 0xFF, 0x00);
			return yellow; }
	
		case CHARTREUSE: {
			static Color chartreuse(0x7F, 0xFF, 0x00); 
			return chartreuse; }
	
		case GREEN: {
			static Color green(0x00, 0xFF, 0x00); 
			return green; }
	
		case AQUAMARINE: {
			static Color aquamarine(0x7F, 0xFF, 0xD4); 
			return aquamarine; }
	
		case BLUE: {
			static Color blue(0x00, 0x00, 0xFF); 
			return blue; }
	
		case INDIGO: {
			static Color indigo(0x4B, 0x00, 0x82); 
			return indigo; }
	
		case PURPLE: {
			static Color purple(0x80, 0x00, 0x80); 
			return purple; }
	
		case MAGENTA: {
			static Color magenta(0xFF, 0x00, 0xFF); 
			return magenta; }
			
		default: {
			static Color white(0xFF, 0xFF, 0xFF);
			return white; }
	}
}
	
float HueToRGB(float p, float q, float t)
{
	t = modf(t, 1.0f);

	if(t < 1.0f/6.0f) return p + (q - p) * 6.0f * t;
	if(t < 1.0f/2.0f) return q;
	if(t < 2.0f/3.0f) return p + (q - p) * (2.0f/3.0f - t) * 6.0f;

	return p;
}

 void Color::HLStoRGB(void)
{
	float H = HLS[0]; float L = HLS[1]; float S = HLS[2];
	float& R = RGB[0]; float& G = RGB[1]; float& B = RGB[2];

    if(S == 0)
	{
        R = L;
		G = L;
		B = L; 

		return;
    }
	else
	{
		float q = (L < 0.5f) ? (L * (1.0f + S)) : ((L + S) - (L * S));
        float p = 2.0f * L - q;
    
		R = HueToRGB(p, q, H + 1.0f/3.0f);
        G = HueToRGB(p, q, H);
        B = HueToRGB(p, q, H - 1.0f/3.0f);
    }
} 

void Color::HSVtoRGB(void)
{
	float H = HSV[0]; float S = HSV[1]; float V = HSV[2];
	float& R = RGB[0]; float& G = RGB[1]; float& B = RGB[2];

	if(S == 0.0f)
	{
		R = V;
		G = V;
		B = V;

		return;
	}
	else
	{
		int i = floor(H);      
		float f = modf(H * 6.0f, 6.0f);
	
		float p = V * (1.0f - S);
		float q = V * (1.0f - S * (f - i));
		float t = V * (1.0f - S * (1.0f - (f - i)));

		switch(i)
		{
			case 0:  R = V; G = t; B = p; break;
			case 1:  R = q; G = V; B = p; break;
			case 2:  R = p; G = V; B = t; break;
			case 3:  R = p; G = q; B = V; break;
			case 4:  R = t; G = p; B = V; break;
			default: R = V; G = p; B = q; break;
		}
	}
}

void Color::CMYtoRGB(void)
{
	RGB[0] = 1.0f - CMY[0];
	RGB[1] = 1.0f - CMY[1];
	RGB[2] = 1.0f - CMY[2];	
}

void Color::CMYKtoRGB(void)
{
	float C = CMYK[0]; float M = CMYK[1]; float Y = CMYK[2]; float K = CMYK[3];
	float& R = RGB[0]; float& G = RGB[1]; float& B = RGB[2];

	R = (1.0f - (C * (1.0f - K) + K));
	G = (1.0f - (M * (1.0f - K) + K));
	B = (1.0f - (Y * (1.0f - K) + K));
}

void Color::RGBtoHLS(void)
{
	float R = RGB[0]; float G = RGB[1]; float B = RGB[2];
	float& H = HLS[0]; float& L = HLS[1]; float& S = HLS[2];

    float max = max3(R, G, B);
	float min = min3(R, G, B);

	L = (max + min) / 2.0f;
  
    if(max == min)
	{
        H = 0.0f;
		S = 0.0f; 
    }
	else
	{
		float d = max - min;

        S = (L > 0.5f) ? (d / (2.0f - max - min)) : (d / (max + min));

        if     (max == R) H = 0.0f + (G - B) / d;
		else if(max == G) H = 2.0f + (B - R) / d;
		else if(max == B) H = 4.0f + (R - G) / d;
       
		H = modf(H / 6.0f, 1.0f);
    }
}

void Color::RGBtoHSV(void)
{
	float R = RGB[0]; float G = RGB[1]; float B = RGB[2];
	float& H = HSV[0]; float& S = HSV[1]; float& V = HSV[2];

	float max = max3(R, G, B);
	float min = min3(R, G, B);
	float d = max - min;

	V = max;

	if(max == min)
	{
		H = 0.0f;
		S = 0.0f;
	}
	else
	{	
		S = d / max;
		
		if     (max == R) H = 0.0f + (G - B) / d;
		else if(max == G) H = 2.0f + (B - R) / d;
		else if(max == B) H = 4.0f + (R - G) / d;
	
		H = modf(H / 6.0f, 1.0f);
	}
}

void Color::RGBtoCMY(void)
{
	CMY[0] = 1.0f - RGB[0];
	CMY[1] = 1.0f - RGB[1];
	CMY[2] = 1.0f - RGB[2];
}

void Color::RGBtoCMYK(void)
{
	float R = RGB[0]; float G = RGB[1]; float B = RGB[2];
	float& C = CMYK[0]; float& M = CMYK[1]; float& Y = CMYK[2]; float& K = CMYK[3];

	C = 1.0f - R;
	M = 1.0f - G;
	Y = 1.0f - B;

	K = 1.0f;

	if(C < K) K = C;
	if(M < K) K = M;
	if(Y < K) K = Y;

	if(K == 1.0f) 
	{
	   C = 0;
	   M = 0;
	   Y = 0;
	}
	else 
	{
	   C = (C - K) / (1.0f - K);
	   M = (M - K) / (1.0f - K);
	   Y = (Y - K) / (1.0f - K);
	}
}

void Color::Bind(void)
{
	glColor4f(RGB[0], RGB[1], RGB[2], A);
}

void Color::Print(void)
{
	printf("HLS:  %.2f, %.2f, %.2f      \n", HLS[0],  HLS[1],  HLS[2]);
	printf("HSV:  %.2f, %.2f, %.2f      \n", HSV[0],  HSV[1],  HSV[2]);
	printf("RGB:  %.2f, %.2f, %.2f      \n", RGB[0],  RGB[1],  RGB[2]);
	printf("CMY:  %.2f, %.2f, %.2f      \n", CMY[0],  CMY[1],  CMY[2]);
	printf("CMYK: %.2f, %.2f, %.2f, %2f \n", CMYK[0], CMYK[1], CMYK[2], CMYK[3]);
}

void Color::PrintHLS(void)
{
	printf("HLS: %.2f, %.2f, %.2f \n", HLS[0], HLS[1], HLS[2]);
}

void Color::PrintHSV(void)
{
	printf("HSV: %.2f, %.2f, %.2f \n", HSV[0], HSV[1], HSV[2]);
}

void Color::PrintRGB(void)
{
	printf("RGB: %.2f, %.2f, %.2f \n", RGB[0], RGB[1], RGB[2]);
}

void Color::PrintCMY(void)
{
	printf("CMY: %.2f, %.2f, %.2f \n", CMY[0], CMY[1], CMY[2]);
}

void Color::PrintCMYK(void)
{
	printf("CMYK: %.2f, %.2f, %.2f, %2f \n", CMYK[0], CMYK[1], CMYK[2], CMYK[3]);
}