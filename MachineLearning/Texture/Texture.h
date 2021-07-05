#pragma once
#include <string>

#include "../Math/MathUtils.h"

struct SDL_Texture;
class Texture final
{
public:
	Texture(const std::string& path);
	Texture(const std::string& path, const std::string& text, const int ptSize, const MathUtils::RGBColour& colour);
	~Texture();

	Texture(const Texture& other) noexcept;
	Texture(Texture&& other) noexcept;
	Texture& operator=(const Texture& other) noexcept;
	Texture& operator=(Texture&& other) noexcept;

	SDL_Texture* const GetSDLTexture() const noexcept;
	const int GetWidth() const noexcept;
	const int GetHeight() const noexcept;

private:
	SDL_Texture* m_pTexture;

	int m_Width;
	int m_Height;
};