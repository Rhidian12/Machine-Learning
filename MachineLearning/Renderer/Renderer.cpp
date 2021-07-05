#include "Renderer.h"

#include <SDL.h>

void Renderer::Renderer::CreateRenderer(SDL_Window* const pWindow) noexcept
{
    m_pSDLRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
}

Renderer::Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_pSDLRenderer);
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

void Renderer::Renderer::Render()
{

}

SDL_Renderer* const Renderer::Renderer::GetSDLRenderer() const noexcept
{
    return m_pSDLRenderer;
}
