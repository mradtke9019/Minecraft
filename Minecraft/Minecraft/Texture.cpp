#include "Texture.h"

Texture::Texture()
{
	id = -1;
	type = nullptr;
	path = nullptr;
}

Texture::Texture(const char* path, GLenum target) : TextureID(0), FilePath(path), BufferData(nullptr), Width(0), Height(0), BitsPerPixel(0), Target(target)
{
	stbi_set_flip_vertically_on_load(1);
	BufferData = stbi_load(path, &Width, &Height, &BitsPerPixel, 4);

	glEnable(Target);
	glGenTextures(1, &TextureID);
	glBindTexture(Target, TextureID);

	glTexParameteri(Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(Target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(Target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(Target, 0, GL_RGBA8, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, BufferData);
	glBindTexture(Target, 0);

	if (BufferData)
		stbi_image_free(BufferData);
}

Texture::~Texture()
{
	glDeleteTextures(1, &TextureID);
}


void Texture::Bind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(Target, TextureID);
}

void Texture::Unbind()
{
	glBindTexture(Target, 0);
}


unsigned int& Texture::GetTextureID()
{
	return TextureID;
}

std::string& Texture::GetFilePath()
{
	return FilePath;
}

int& Texture::GetHeight()
{
	return Height;
}

int& Texture::GetWidth()
{
	return Width;
}

GLenum& Texture::GetTarget()
{
	return Target;
}

void Texture::SetTextureSlot(int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
}

