#include "Renderer.h"
#include "../Utils/Utils.h"
#include "../Texture/Texture.h"

#include <SDL.h>

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_pSDLRenderer);
}

void Renderer::CreateRenderer(SDL_Window* const pWindow) noexcept
{
    Utils::Assert(pWindow != nullptr, "Renderer::CreateRenderer() > pWindow was a nullptr!");
    SDL_GetWindowSize(pWindow, &m_WindowWidth, &m_WindowHeight);

    Utils::Assert(m_pSDLRenderer == nullptr, "Renderer::CreateRenderer() > Only call this function once!");

    m_pSDLRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Utils::Assert(m_pSDLRenderer != nullptr, SDL_GetError());
}

Renderer* Renderer::GetInstance() noexcept
{
    if (!m_pInstance)
        m_pInstance = new Renderer{};

    return m_pInstance;
}

void Renderer::Cleanup() noexcept
{
    delete m_pInstance;
    m_pInstance = nullptr;
}

void Renderer::ClearRenderer(const MathUtils::RGBColour& clearColour) noexcept
{
    SDL_RenderClear(m_pSDLRenderer);
    SDL_SetRenderDrawColor(m_pSDLRenderer, Uint8(clearColour.r), Uint8(clearColour.g), Uint8(clearColour.b), Uint8(clearColour.a));
    SDL_RenderFillRect(m_pSDLRenderer, nullptr);
}

void Renderer::Render(const Texture* const pTexture, const MathUtils::Point2f& position) noexcept
{
    Utils::Assert(m_pSDLRenderer != nullptr, "Renderer::Render() > Renderer::CreateRenderer() has not been called!");

    const MathUtils::Point2f convertedPoint{ MathUtils::ConvertToBottomLeftOrigin{}(position) };

    SDL_Rect destRect{};
    destRect.x = int(convertedPoint.x);
    destRect.y = int(convertedPoint.y);
    destRect.w = pTexture->GetWidth();
    destRect.h = pTexture->GetHeight();

    Utils::Assert(SDL_RenderCopy(m_pSDLRenderer, pTexture->GetSDLTexture(), nullptr, &destRect) == 0, SDL_GetError());
}

void Renderer::Present() noexcept
{
    Utils::Assert(m_pSDLRenderer != nullptr, "Renderer::Present() > Renderer::CreateRenderer() has not been called!");
   
    SDL_RenderPresent(m_pSDLRenderer);
}

SDL_Renderer* const Renderer::GetSDLRenderer() const noexcept
{
    return m_pSDLRenderer;
}
