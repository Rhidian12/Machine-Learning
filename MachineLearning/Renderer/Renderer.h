#pragma once

#include "../Math/MathUtils.h"

struct SDL_Renderer;
struct SDL_Window;
class Texture;
namespace Renderer
{
	class Renderer final
	{
	public:
		~Renderer();

		static Renderer* GetInstance() noexcept;
		static void Cleanup() noexcept;
		void CreateRenderer(SDL_Window* const pWindow) noexcept;

		void ClearRenderer() noexcept;
		void Render(Texture* pTexture, const MathUtils::Point2f& position) noexcept;
		void Present() noexcept;

		SDL_Renderer* const GetSDLRenderer() const noexcept;

	private:
		Renderer();

		inline static Renderer* m_pInstance{};
		SDL_Renderer* m_pSDLRenderer{};
	};
}