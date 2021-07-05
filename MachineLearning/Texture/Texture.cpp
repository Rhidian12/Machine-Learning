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
	color.r = colour.r;
	color.g = colour.g;
	color.b = colour.b;
	color.a = colour.a;

	SDL_Surface* pSurface{ TTF_RenderText_Blended(pFont, text.c_str(), color) };

	Utils::Assert(pSurface != nullptr, SDL_GetError());
	TTF_CloseFont(pFont);

	m_Width = pSurface->w;
	m_Height = pSurface->h;

	m_pTexture = SDL_CreateTextureFromSurface(Renderer::GetInstance()->GetSDLRenderer(), pSurface);

	Utils::Assert(m_pTexture != nullptr, SDL_GetError());

	SDL_FreeSurface(pSurface);
}

Texture::~Texture()
{
	SDL_DestroyTexture(m_pTexture);
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
