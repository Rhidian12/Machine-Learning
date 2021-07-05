#include "Texture.h"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL.h>

#include "../Renderer/Renderer.h"
#include "../Utils/Utils.h"

Texture::Texture(const std::string& path)
	: m_pTexture{}
	, m_Width{}
	, m_Height{}
{
	SDL_Surface* pSurface{ IMG_Load(path.c_str()) };

	Utils::Assert(pSurface != nullptr, SDL_GetError());

	m_Width = pSurface->w;
	m_Height = pSurface->h;

	m_pTexture = SDL_CreateTextureFromSurface(Renderer::GetInstance()->GetSDLRenderer(), pSurface);

	Utils::Assert(m_pTexture != nullptr, SDL_GetError());

	SDL_FreeSurface(pSurface);
}

Texture::Texture(const std::string& path, const std::string& text, const int ptSize, const MathUtils::RGBColour& colour)
	: m_pTexture{}
	, m_Width{}
	, m_Height{}
{
	TTF_Font* pFont{ TTF_OpenFont(path.c_str(), ptSize) };

	Utils::Assert(pFont != nullptr, SDL_GetError());

	SDL_Color color;
	color.r = Uint8(colour.r);
	color.g = Uint8(colour.g);
	color.b = Uint8(colour.b);
	color.a = Uint8(colour.a);

	SDL_Surface* pSurface{ TTF_RenderText_Blended(pFont, text.c_str(), color) };

	Utils::Assert(pSurface != nullptr, SDL_GetError());

	m_Width = pSurface->w;
	m_Height = pSurface->h;

	m_pTexture = SDL_CreateTextureFromSurface(Renderer::GetInstance()->GetSDLRenderer(), pSurface);

	Utils::Assert(m_pTexture != nullptr, SDL_GetError());

	TTF_CloseFont(pFont);
	SDL_FreeSurface(pSurface);
}

Texture::~Texture()
{
	SDL_DestroyTexture(m_pTexture);
}

Texture::Texture(const Texture& other) noexcept
	: m_pTexture{ other.m_pTexture }
	, m_Width{ other.m_Width }
	, m_Height{ other.m_Height }
{
}

Texture::Texture(Texture&& other) noexcept
	: m_pTexture{ std::move(other.m_pTexture) }
	, m_Width{ std::move(other.m_Width) }
	, m_Height{ std::move(other.m_Height) }
{
	other.m_pTexture = nullptr;
}

Texture& Texture::operator=(const Texture& other) noexcept
{
	m_pTexture = other.m_pTexture;
	m_Width = other.m_Width;
	m_Height = other.m_Height;
	return *this;
}

Texture& Texture::operator=(Texture&& other) noexcept
{
	m_pTexture = std::move(other.m_pTexture);
	m_Width = std::move(other.m_Width);
	m_Height = std::move(other.m_Height);
	other.m_pTexture = nullptr;
	return *this;
}

SDL_Texture* const Texture::GetSDLTexture() const noexcept
{
	return m_pTexture;
}

const int Texture::GetWidth() const noexcept
{
	return m_Width;
}

const int Texture::GetHeight() const noexcept
{
	return m_Height;
}
