#pragma once

struct SDL_Renderer;
struct SDL_Window;
namespace Renderer
{
	class Renderer final
	{
	public:
		~Renderer();

		static Renderer* GetInstance() noexcept;
		static void Cleanup() noexcept;

		void CreateRenderer(SDL_Window* const pWindow) noexcept;
		void Render();

	private:
		Renderer() = default;

		inline static Renderer* m_pInstance{};
		SDL_Renderer* m_pSDLRenderer{};
	};
}