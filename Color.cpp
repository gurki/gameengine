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

float Color::conv[5] = {1, 1, 1, 1, 1};

Color::Color(void)
{
	RGBA[0] = 1.0f;
	RGBA[1] = 1.0f;
	RGBA[2] = 1.0f;
	RGBA[3] = 1.0f;
}

Color::Color(float R, float G, float B, float A)
{
	*this = WithRGB(R, G, B, A);
}

Color& Color::ShiftCW(float v)
{
	float* HLS = GetHLS();

	*this = WithHLS(HLS[0] - v, HLS[1], HLS[2], RGBA[3]);

	return *this;
}

Color& Color::ShiftCCW(float v)
{
	float* HLS = GetHLS();

	*this = WithHLS(HLS[0] + v, HLS[1], HLS[2], RGBA[3]);

	return *this;
}

Color& Color::Darken(float v)
{
	float* HLS = GetHLS();

	*this = WithHLS(HLS[0], HLS[1] - v, HLS[2], RGBA[3]);

	return *this;
}

Color& Color::Lighten(float v)
{
	float* HLS = GetHLS();

	*this = WithHLS(HLS[0], HLS[1] + v, HLS[2], RGBA[3]);

	return *this;
}

Color& Color::Saturate(float v)
{
	float* HLS = GetHLS();

	*this = WithHLS(HLS[0], HLS[1], HLS[2] + v, RGBA[3]);

	return *this;
}

Color& Color::Desaturate(float v)
{
	float* HLS = GetHLS();

	*this = WithHLS(HLS[0], HLS[1], HLS[2] - v, RGBA[3]);

	return *this;
}

Color& Color::SetAlpha(float Alpha)
{
	RGBA[3] = limit(Alpha, 0.0f, 1.0f);

	return *this;
}

// static getter
Color Color::WithLuminance(float L, float A)
{
	return WithHLS(0.0f, L, 0.0f, A);
}

float HueToRGB(float p, float q, float t)
{
	t = modf(t, 1.0f);

	if(t < 1.0f/6.0f) return p + (q - p) * 6.0f * t;
	if(t < 1.0f/2.0f) return q;
	if(t < 2.0f/3.0f) return p + (q - p) * (2.0f/3.0f - t) * 6.0f;

	return p;
}

Color Color::WithHLS(float H, float L, float S, float A)
{
	H = mod(H, 1.0f);
	L = limit(L, 0.0f, 1.0f);
	S = limit(S, 0.0f, 1.0f);
	A = limit(A, 0.0f, 1.0f);

	Color c;

    if(S == 0)
	{
        c.RGBA[0] = L;
		c.RGBA[1] = L;
		c.RGBA[2] = L; 
		c.RGBA[3] = A;

		return c;
    }
	else
	{
		float q = (L < 0.5f) ? (L * (1.0f + S)) : ((L + S) - (L * S));
        float p = 2.0f * L - q;
    
		c.RGBA[0] = HueToRGB(p, q, H + 1.0f/3.0f);
        c.RGBA[1] = HueToRGB(p, q, H);
        c.RGBA[2] = HueToRGB(p, q, H - 1.0f/3.0f);
		c.RGBA[3] = A;
    }

	return c;
}

Color Color::WithHSV(float H, float S, float V, float A)
{
	H = mod(H, 1.0f);
	S = limit(S, 0.0f, 1.0f);
	V = limit(V, 0.0f, 1.0f);
	A = limit(A, 0.0f, 1.0f);

	Color c;

	if(S == 0.0f)
	{
		c.RGBA[0] = V;
		c.RGBA[1] = V;
		c.RGBA[2] = V;
		c.RGBA[3] = A;

		return c;
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
			case 0:  c.RGBA[0] = V; c.RGBA[1] = t; c.RGBA[2] = p; break;
			case 1:  c.RGBA[0] = q; c.RGBA[1] = V; c.RGBA[2] = p; break;
			case 2:  c.RGBA[0] = p; c.RGBA[1] = V; c.RGBA[2] = t; break;
			case 3:  c.RGBA[0] = p; c.RGBA[1] = q; c.RGBA[2] = V; break;
			case 4:  c.RGBA[0] = t; c.RGBA[1] = p; c.RGBA[2] = V; break;
			default: c.RGBA[0] = V; c.RGBA[1] = p; c.RGBA[2] = q; break;
		}
	}

	return c;
}

Color Color::WithRGB(float R, float G, float B, float A)
{
	R = limit(R, 0.0f, 1.0f);
	B = limit(B, 0.0f, 1.0f);
	G = limit(G, 0.0f, 1.0f);
	A = limit(A, 0.0f, 1.0f);

	Color c;

	c.RGBA[0] = R;
	c.RGBA[1] = G;
	c.RGBA[2] = B;
	c.RGBA[3] = A;

	return c;
}

Color Color::WithUnsignedRGB(uint R, uint G, uint B, float A)
{
	R = limit(R, 0, 255);
	B = limit(B, 0, 255);
	G = limit(G, 0, 255);
	A = limit(A, 0.0f, 1.0f);

	Color c;

	c.RGBA[0] = R / 255.0f;
	c.RGBA[1] = G / 255.0f;
	c.RGBA[2] = B / 255.0f;
	c.RGBA[3] = A / 255.0f;

	return c;
}

Color Color::WithCMY(float C, float M, float Y, float A)
{
	C = limit(C, 0.0f, 1.0f);
	M = limit(M, 0.0f, 1.0f);
	Y = limit(Y, 0.0f, 1.0f);
	A = limit(A, 0.0f, 1.0f);

	Color c;

	c.RGBA[0] = 1.0f - C;
	c.RGBA[1] = 1.0f - M;
	c.RGBA[2] = 1.0f - Y;	

	return c;
}

Color Color::WithCMYK(float C, float M, float Y, float K, float A)
{
	C = limit(C, 0.0f, 1.0f);
	M = limit(M, 0.0f, 1.0f);
	Y = limit(Y, 0.0f, 1.0f);
	K = limit(K, 0.0f, 1.0f);
	A = limit(A, 0.0f, 1.0f);

	Color c;

	c.RGBA[0] = (1.0f - (C * (1.0f - K) + K));
	c.RGBA[1] = (1.0f - (M * (1.0f - K) + K));
	c.RGBA[2] = (1.0f - (Y * (1.0f - K) + K));

	return c;
}

// getter
float Color::GetAlpha(void)
{ 
	return RGBA[3]; 
}

float* Color::GetHLS(void) 
{ 
	float max = max3(RGBA[0], RGBA[1], RGBA[2]);
	float min = min3(RGBA[0], RGBA[1], RGBA[2]);

	conv[1] = (max + min) / 2.0f;
  
    if(max == min)
	{
		conv[0] = 0.0f;
		conv[2] = 0.0f; 
    }
	else
	{
		float d = max - min;

        conv[2] = (conv[1] > 0.5f) ? (d / (2.0f - max - min)) : (d / (max + min));

        if(max == RGBA[0]) 
		{
			conv[0] = 0.0f + (RGBA[1] - RGBA[2]) / d;
		}
		else if(max == RGBA[1]) 
		{
			conv[0] = 2.0f + (RGBA[2] - RGBA[0]) / d;
		}
		else if(max == RGBA[2]) 
		{
			conv[0] = 4.0f + (RGBA[0] - RGBA[1]) / d;
		}
       
		conv[0] = modf(conv[0] / 6.0f, 1.0f);
    }

	conv[3] = RGBA[3];

	return conv; 
}

float* Color::GetHSV(void) 
{ 
	float max = max3(RGBA[0], RGBA[1], RGBA[2]);
	float min = min3(RGBA[0], RGBA[1], RGBA[2]);
	float d = max - min;

	conv[2] = max;

	if(max == min)
	{
		conv[0] = 0.0f;
		conv[1] = 0.0f;
	}
	else
	{	
		conv[1] = d / max;
		
        if(max == RGBA[0]) 
		{
			conv[0] = 0.0f + (RGBA[1] - RGBA[2]) / d;
		}
		else if(max == RGBA[1]) 
		{
			conv[0] = 2.0f + (RGBA[2] - RGBA[0]) / d;
		}
		else if(max == RGBA[2]) 
		{
			conv[0] = 4.0f + (RGBA[0] - RGBA[1]) / d;
		}
	
		conv[0] = modf(conv[0] / 6.0f, 1.0f);
	}

	conv[3] = RGBA[3];

	return conv;
}

float* Color::GetRGB(void) 
{
	return RGBA;
}

float* Color::GetCMY(void) 
{ 
	conv[0] = 1.0f - RGBA[0];
	conv[1] = 1.0f - RGBA[1];
	conv[2] = 1.0f - RGBA[2];
	conv[3] = RGBA[3];

	return conv;
}

float* Color::GetCMYK(void)
{ 
	conv[0] = 1.0f - RGBA[0];
	conv[1] = 1.0f - RGBA[1];
	conv[2] = 1.0f - RGBA[2];
	conv[3] = 1.0f;

	if(conv[0] < conv[3]) conv[3] = conv[0];
	if(conv[1] < conv[3]) conv[3] = conv[1];
	if(conv[2] < conv[3]) conv[3] = conv[2];

	if(conv[3] == 1.0f) 
	{
	   conv[0] = 0;
	   conv[1] = 0;
	   conv[2] = 0;
	}
	else 
	{
	   conv[0] = (conv[0] - conv[3]) / (1.0f - conv[3]);
	   conv[1] = (conv[1] - conv[3]) / (1.0f - conv[3]);
	   conv[2] = (conv[2] - conv[3]) / (1.0f - conv[3]);
	}

	conv[3] = RGBA[3];

	return conv;
}
		
Color Color::WithBlack(void)
{
	static Color black = Color::WithUnsignedRGB(0x00, 0x00, 0x00);
	return black; 
}
			
Color Color::WithGray(void)
{
	static Color gray = Color::WithUnsignedRGB(0x80, 0x80, 0x80);
	return gray; 
}
			
Color Color::WithSilver(void)
{
	static Color silver = Color::WithUnsignedRGB(0xC0, 0xC0, 0xC0);
	return silver; 
}

Color Color::WithWhite(void)
{
	static Color white = Color::WithUnsignedRGB(0xFF, 0xFF, 0xFF);
	return white; 
}

Color Color::WithRed(void)
{
	static Color red = Color::WithUnsignedRGB(0xFF, 0x00, 0x00);
	return red; 
}
	
Color Color::WithRedOrange(void)
{
	static Color vermillion = Color::WithUnsignedRGB(0xE3, 0x42, 0x34); 
	return vermillion;
}
	
Color Color::WithOrange(void)
{
	static Color orange = Color::WithUnsignedRGB(0xFF, 0x7F, 0x00);
	return orange; 
}
	
Color Color::WithYellowOrange(void)
{
	static Color amber = Color::WithUnsignedRGB(0xFF, 0xBF, 0x00);
	return amber;
}
	
Color Color::WithYellow(void)
{
	static Color yellow = Color::WithUnsignedRGB(0xFF, 0xFF, 0x00);
	return yellow;
}
	
Color Color::WithYellowGreen(void)
{
	static Color chartreuse = Color::WithUnsignedRGB(0x7F, 0xFF, 0x00); 
	return chartreuse;
}
	
Color Color::WithGreen(void)
{
	static Color green = Color::WithUnsignedRGB(0x00, 0xFF, 0x00); 
	return green; 
}
	
Color Color::WithBlueGreen(void)
{
	static Color aquamarine = Color::WithUnsignedRGB(0x7F, 0xFF, 0xD4); 
	return aquamarine; 
}
	
Color Color::WithBlue(void)
{
	static Color blue = Color::WithUnsignedRGB(0x00, 0x00, 0xFF); 
	return blue;
}
	
Color Color::WithBluePurple(void)
{
	static Color indigo = Color::WithUnsignedRGB(0x4B, 0x00, 0x82); 
	return indigo; 
}
	
Color Color::WithPurple(void)
{
	static Color purple = Color::WithUnsignedRGB(0x80, 0x00, 0x80); 
	return purple; 
}
	
Color Color::WithRedPurple(void)
{
	static Color magenta = Color::WithUnsignedRGB(0xFF, 0x00, 0xFF); 
	return magenta; 
}

void Color::Bind(void) const
{
	glColor4f(RGBA[0], RGBA[1], RGBA[2], RGBA[3]);
}

ostream& operator << (ostream& out, const Color& c)
{
	out << "(" << c.RGBA[0] << ", " << c.RGBA[1] << ", " << c.RGBA[2] << ", " << c.RGBA[3] << ")";
			
	return out;
}

istream& operator >> (istream& in, Color& c)
{
	float v[4];
	
	cin >> v[0];
	cin >> v[1];
	cin >> v[2];
	cin >> v[3];
	
	c = Color::WithRGB(v[0], v[1], v[2], v[3]);
	
	return in;
}