#include "pch.h"
#include "OpenGL-Core.h"
#include "stb_image.h"

Texture::Texture(const std::string& path)
	: m_RendererID(0)
	, m_FilePath(path)
	, m_LocalBuffer(nullptr)
	, m_Height(0), m_Width(0)
	, m_BitsPerPixel(0)
{
	// OpenGL expect the image to read from bottom right
	stbi_set_flip_vertically_on_load(1);

	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BitsPerPixel, 4);
	ASSERT(m_LocalBuffer != nullptr, "Can not load the image, Check the path: " + m_FilePath);

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	UnBind();

	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(uint32_t slot /*= 0*/) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::EnableBlending() const
{
	/**
	 *  src alpha = 0
	 *  dest = 1-0 = 1
	 *
	 *	R = (r-src * 0) + (r-dest * (1 - 0)) = r-dest
	 *	G = (g-src * 0) + (g-dest * (1 - 0)) = g-dest
	 *	B = (b-src * 0) + (b-dest * (1 - 0)) = b-dest
	 *	A = (a-src * 0) + (a-dest * (1 - 0)) = a-dest
	 */

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Texture::DisableBlending()
{
	glDisable(GL_BLEND);
}

void Texture::DisableTexturing()
{
	glDisable(GL_TEXTURE_2D);
}
