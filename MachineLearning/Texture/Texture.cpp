#include "Texture.h"

#include <SDL_image.h>
#include <SDL_video.h>
#include <SDL.h>

#include "../Renderer/Renderer.h"

Texture::Texture(const std::string& path)
	: m_pTexture{}
{
	m_pTexture = SDL_CreateTextureFromSurface(Renderer::Renderer::GetInstance()->GetSDLRenderer(), SDL_LoadBMP(path.c_str()));
}

Texture::~Texture()
{
	SDL_DestroyTexture(m_pTexture);
}

SDL_Texture* const Texture::GetSDLTexture() const noexcept
{
	return m_pTexture;
}
