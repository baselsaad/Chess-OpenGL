#pragma once
#include "Renderer/Debug.h"

namespace Defaults
{
	static const int PositionsSize = 4 * 4;
	static const int IndicesCount = 6;

	//positions with texture coord 2 | 2
	// Each "Line" for X , Y 
	static constexpr float positions[PositionsSize] =
	{
		 -50.0f, -50.0f , 0.0f, 0.0f,		// 0 bottom_left 
		  50.0f, -50.0f , 1.0f, 0.0f,		// 1 bottom_right
		  50.0f,  50.0f , 1.0f, 1.0f,		// 2 top_right
		 -50.0f,  50.0f , 0.0f, 1.0f		// 3 top_left
	};

	static constexpr uint32_t indices[IndicesCount] =
	{
		0, 1, 2,
		2, 3, 0
	};

	/**************************************************
	 *				3 * * * * * * * * * * * 2
	 *				*					*   *
	 *				* 			   *		*
	 *				*  		  *				*
	 * 				*  	  *					*
	 * 				*  *					*
	 * 				0 * * * * * * * * * * * 1
	 **************************************************/

}



