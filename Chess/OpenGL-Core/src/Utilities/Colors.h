#pragma once
#include <vector>

namespace Colors
{
	struct RGBA
	{
		float R, G, B, Alpha;

		RGBA(float r, float g, float b, float a = 1.0f)
			: R(r)
			, G(g)
			, B(b)
			, Alpha(a)
		{
		}

		RGBA(const RGBA& rgba)
			: R(rgba.R)
			, G(rgba.G)
			, B(rgba.B)
			, Alpha(rgba.Alpha)
		{
		}
	};


	RGBA Red{ 0.77f, 0.12f, 0.23f };			//#C41E3A
	RGBA Dark_Magenta{ 0.64f, 0.19f, 0.79f };	//#A330C9
	RGBA Orange{ 1.00f, 0.49f, 0.04f };			//#FF7C0A
	RGBA Dark_Cyan{ 0.20f, 0.58f, 0.50f };		//#33937F
	RGBA Green{ 0.67f, 0.83f, 0.45f };			//#AAD372
	RGBA Light_Blue{ 0.25f, 0.78f, 0.92f };		//#3FC7EB
	RGBA Spring_Green{ 0.00f, 1.00f, 0.60f };	//#00FF98
	RGBA Pink{ 0.96f, 0.55f, 0.73f };			//#F48CBA
	RGBA White{ 1.00f, 1.00f, 1.00f };			//#FFFFFF
	RGBA Yellow{ 1.00f, 0.96f, 0.41f };			//#FFF468
	RGBA Blue{ 0.00f, 0.44f, 0.87f };			//#0070DD
	RGBA Purple{ 0.53f, 0.53f, 0.93f };			//#8788EE
	RGBA Tan{ 0.78f, 0.61f, 0.43f };			//#C69B6D

	const std::vector<RGBA> ColorsArray =
	{
	  Red
	, Dark_Magenta
	, Orange
	, Dark_Cyan
	, Green
	, Light_Blue
	, Spring_Green
	, Pink
	, White
	, Yellow
	, Blue
	, Purple
	, Tan
	};



}



