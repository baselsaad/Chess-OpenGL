#include "pch.h"
#include "OpenGL-Core.h"
#include "Utilities\Debug.h"


Shader::Shader(const std::string& filePath)
	: m_FilePath(filePath), m_RendererID(0)
{
	Shaders shadersSource = ParaseShader(m_FilePath);
	m_RendererID = CreateShader(shadersSource.FragmentShader, shadersSource.VertexShader);
}

Shader::~Shader()
{
	GL_CALL(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
	//bind shaders
	GL_CALL(glUseProgram(m_RendererID));
}

void Shader::UnBind() const
{
	GL_CALL(glUseProgram(0));
}

void Shader::SetUniform1i(const char* name, int v0)
{
	GL_CALL(glUniform1i(GetUniformLocation(name), v0));
}

void Shader::SetUniform1f(const char* name, float v0)
{
	GL_CALL(glUniform1f(GetUniformLocation(name), v0));
}

void Shader::SetUniform4f(const char* name, float v0, float v1, float v2, float v3)
{
	GL_CALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform4f(const char* name, const Colors::RGBA& color)
{
	using namespace Colors;
	GL_CALL(glUniform4f(GetUniformLocation(name), color.R, color.G, color.B, color.Alpha));
}


void Shader::SetUniformMat4f(const char* name, const glm::mat4& matrix)
{
	GL_CALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

Shaders Shader::ParaseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);
	ASSERT(stream.is_open(), "Can not find the shader file path: "+filePath);

	enum class ParsingState
	{
		None = -1, Vertex = 0, Fragment = 1
	};

	ParsingState state = ParsingState::None;
	std::string line;
	std::stringstream source[2];//two shaders

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				state = ParsingState::Vertex;
			else if (line.find("fragment") != std::string::npos)
				state = ParsingState::Fragment;
		}
		else
		{
			source[(uint32_t)state] << line << '\n';
		}
	}

	return { source[0].str(),source[1].str() };
}

uint32_t Shader::CompileShader(uint32_t type, const std::string& source)
{
	uint32_t id = glCreateShader(type);
	const char* src = source.c_str();
	const int HOW_MANY_SHADERS = 1;
	GL_CALL(glShaderSource(id, HOW_MANY_SHADERS, &src, NULL));//Replaces the source code in a shader object
	GL_CALL(glCompileShader(id));

	//Compile Error Handling
	int result;
	GL_CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GL_CALL(glGetShaderInfoLog(id, length, &length, message));

		std::cout << "Shader Compile Error in " << (type == GL_FRAGMENT_SHADER ? "fragment Shader: " : "vertex Shader: ") << std::endl;
		std::cout << message;
		GL_CALL(glDeleteShader(id));

		ASSERT(false, "failed to compile the shader!");
		return 0;
	}

	return id;
}

uint32_t Shader::CreateShader(const std::string& fragmentShader, const std::string& vertexShader)
{
	// creates an empty program object.
	// program object is an object to which shaders can be attached
	uint32_t programm = glCreateProgram();

	uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexShader);

	GL_CALL(glAttachShader(programm, fs));
	GL_CALL(glAttachShader(programm, vs));

	GL_CALL(glLinkProgram(programm));//links any attached shader to program
	GL_CALL(glValidateProgram(programm)); // checks, if can execute given the current OpenGL state

	GL_CALL(glDeleteShader(fs));
	GL_CALL(glDeleteShader(vs));

	return programm;
}

GLint Shader::GetUniformLocation(const char* name)
{
	auto shaderFinder = m_ShaderCache.find(name);
	if (shaderFinder != m_ShaderCache.end())
	{
		return shaderFinder->second;
	}

	GLint location = glGetUniformLocation(m_RendererID, name);
	if (location == -1)
		std::cout << "Warning Uniform " << name << " does not exist!!\n";

	m_ShaderCache[name] = location;
	return location;
}
