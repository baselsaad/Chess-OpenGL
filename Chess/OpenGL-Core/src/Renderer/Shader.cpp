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
	glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
	//bind shaders
	glUseProgram(m_RendererID);
}

void Shader::UnBind() const
{
	glUseProgram(0);
}

void Shader::SetUniform1i(const char* name, int v0)
{
	glUniform1i(GetUniformLocation(name), v0);
}

void Shader::SetUniform1f(const char* name, float v0)
{
	glUniform1f(GetUniformLocation(name), v0);
}

void Shader::SetUniform4f(const char* name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform4f(const char* name, const Colors::RGBA& color)
{
	using namespace Colors;
	glUniform4f(GetUniformLocation(name), color.R, color.G, color.B, color.Alpha);
}


void Shader::SetUniformMat4f(const char* name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

Shaders Shader::ParaseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);
	ASSERT(stream.is_open(), "Can not find the shader file path: " + filePath);

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
	glShaderSource(id, HOW_MANY_SHADERS, &src, NULL);//Replaces the source code in a shader object
	glCompileShader(id);

	//Compile Error Handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		Debug::Error("Shader Compile Error in {0}", (type == GL_FRAGMENT_SHADER ? "fragment Shader: " : "vertex Shader: "));
		Debug::Error(message);
		glDeleteShader(id);

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

	glAttachShader(programm, fs);
	glAttachShader(programm, vs);

	glLinkProgram(programm);//links any attached shader to program
	glValidateProgram(programm); // checks, if can execute given the current OpenGL state

	glDeleteShader(fs);
	glDeleteShader(vs);

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
		Debug::Error("Uniform {0} does not exsist!", name);

	m_ShaderCache[name] = location;
	return location;
}
