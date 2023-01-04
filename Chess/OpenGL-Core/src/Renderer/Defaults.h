#pragma once

namespace Defaults
{
	static constexpr glm::vec3 DefaultPosition(1.0f);
	static constexpr glm::vec3 DefaultScale(75.0f, 75.0f, 1.0f);

	static constexpr int WINDOW_WIDTH = 700;
	static constexpr int WINDOW_HEIGHT = 700;

	static constexpr float MIN_POSITION_OFFSET = 0.0f;
	static constexpr float MAX_POSITION_OFFSET = 1.0f;

	static constexpr int IndicesCount = 6;

	static constexpr int PositionsCount = 4 * 4;
	static constexpr int PositionsSize = PositionsCount * (sizeof(float));


	//static constexpr float Positions[PositionsCount] =
	//{
	//	// positions          // texture coords
	//	 0.0f, 0.0f,			 0.0f, 0.0f,   // top right
	//	 1.0f, 0.0f,			 1.0f, 0.0f,   // bottom right
	//	 1.0f, 1.0f,			 1.0f, 1.0f,   // bottom left
	//	 0.0f, 1.0f,			 0.0f, 1.0f    // top left 
	//};

	static constexpr float Positions[PositionsCount] =
	{
		// Positions										// Texture Coords
		MIN_POSITION_OFFSET,	MIN_POSITION_OFFSET,			0.0f, 0.0f, // 0 bottom_left 
		MAX_POSITION_OFFSET,	MIN_POSITION_OFFSET,			1.0f, 0.0f, // 1 bottom_right
		MAX_POSITION_OFFSET,	MAX_POSITION_OFFSET,			1.0f, 1.0f, // 2 top_right
		MIN_POSITION_OFFSET,	MAX_POSITION_OFFSET,			0.0f, 1.0f  // 3 top_left
	};

	static constexpr uint32_t Indices[IndicesCount] =
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



