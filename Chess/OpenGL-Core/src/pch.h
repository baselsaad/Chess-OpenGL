#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Utilities\Colors.h"

#include "Renderer\OpenGLWindow.h"
#include "Renderer\Texture.h"
#include "Renderer\Shader.h"
#include "Renderer\VertexArray.h"
#include "Renderer\VertexBuffer.h"
#include "Renderer\VertexBufferLayout.h"
#include "Renderer\IndexBuffer.h"
#include "Renderer\Renderer.h"
#include "Renderer\Components.h"


#ifdef GLCORE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif