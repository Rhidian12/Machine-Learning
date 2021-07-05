#include "Renderer.h"
#include "../Utils/Utils.h"
#include "../Texture/Texture.h"

#include <SDL.h>

Renderer::Renderer::Renderer()
{
    Utils::Assert(m_pSDLRenderer != nullptr, "Renderer::GetInstance()> First call Renderer::CreateRenderer()!");
}

Renderer::Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_pSDLRenderer);
}

void Renderer::Renderer::CreateRenderer(SDL_Window* const pWindow) noexcept
{
    Utils::Assert(m_pSDLRenderer == nullptr, "Renderer::CreateRenderer() > Only call this function once!");

    m_pSDLRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
}

Renderer::Renderer* Renderer::Renderer::GetInstance() noexcept
{
    if (!m_pInstance)
        m_pInstance = new Renderer{};

    return m_pInstance;
}

void Renderer::Renderer::Cleanup() noexcept
{
    delete m_pInstance;
    m_pInstance = nullptr;
}

void Renderer::Renderer::ClearRenderer() noexcept
{
    SDL_RenderClear(m_pSDLRenderer);
}

void Renderer::Renderer::Render(Texture* pTexture, const MathUtils::Point2f& position)
{
    Utils::Assert(m_pSDLRenderer != nullptr, "Renderer::Render() > Renderer::CreateRenderer() has not been called!");

    SDL_Rect destRect{};
    destRect.x = position.x;
    destRect.y = position.y;
    SDL_RenderCopy(m_pSDLRenderer, pTexture->GetSDLTexture(), nullptr, &destRect);
}

void Renderer::Renderer::Present() noexcept
{
    Utils::Assert(m_pSDLRenderer != nullptr, "Renderer::Present() > Renderer::CreateRenderer() has not been called!");
    SDL_RenderPresent(m_pSDLRenderer);
}

SDL_Renderer* const Renderer::Renderer::GetSDLRenderer() const noexcept
{
    return m_pSDLRenderer;
}
