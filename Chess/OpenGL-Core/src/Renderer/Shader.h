#pragma once
#include "glm/mat4x4.hpp"

//Forward declaration
namespace Colors { struct RGBA;};

struct Shaders
{
	std::string VertexShader;
	std::string FragmentShader;
};

class Shader
{
public:
	Shader() = default;
	Shader(const std::string& filePath);
	~Shader();

public:
	void Bind() const;
	void UnBind() const;

	void SetUniform1i(const char* name, int v0);
	void SetUniform1f(const char* name, float v0);
	void SetUniform4f(const char* name, float v0, float v1, float v2, float v3);
	void SetUniform4f(const char* name, const Colors::RGBA& color);
	void SetUniformMat4f(const char* name, const glm::mat4& matrix);

private:
	Shaders ParaseShader(const std::string& filePath);
	uint32_t CompileShader(uint32_t type, const std::string& source);
	uint32_t CreateShader(const std::string& fragmentShader, const std::string& vertexShader);

	int GetUniformLocation(const char* name);

private:
	uint32_t m_RendererID;
	std::string m_FilePath;
	std::unordered_map<std::string, int> m_ShaderCache;
};

