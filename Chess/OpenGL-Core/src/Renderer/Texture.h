#pragma once
#include<iostream>

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

public:
	void Bind(uint32_t slot = 0) const;
	void UnBind() const;

	void EnableBlending() const;
	void DisableBlending();

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline const char* GetFilePath() const { return m_FilePath.c_str(); }

private:
	uint32_t m_RendererID;
	std::string m_FilePath;

	uint8_t* m_LocalBuffer;
	int m_Height, m_Width;
	int m_BitsPerPixel;
};

