#pragma once

#include <string>

struct SDL_Texture;
class Texture final
{
public:
	Texture(const std::string& path);
	~Texture();

	SDL_Texture* const GetSDLTexture() const noexcept;
	const int GetWidth() const noexcept;
	const int GetHeight() const noexcept;

private:
	SDL_Texture* m_pTexture;

	int m_Width;
	int m_Height;
};