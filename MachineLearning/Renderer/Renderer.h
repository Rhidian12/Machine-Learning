#pragma once

#include "../Math/MathUtils.h"

struct SDL_Renderer;
struct SDL_Window;
class Texture;
class Camera;

class Renderer final
{
public:
	~Renderer();

	static Renderer* GetInstance() noexcept;
	static void Cleanup() noexcept;
	void CreateRenderer(SDL_Window* const pWindow) noexcept;

	void ClearRenderer(const MathUtils::RGBColour& clearColour) noexcept;
	void Render(const Texture* const pTexture, const MathUtils::Point2f& position) noexcept;
	void Present() noexcept;

	void SetCamera(Camera* const pCamera) noexcept;

	SDL_Renderer* const GetSDLRenderer() const noexcept;

private:
	Renderer() = default;

	inline static Renderer* m_pInstance{};
	SDL_Renderer* m_pSDLRenderer{};

	Camera* m_pCamera{};

	int m_WindowWidth{};
	int m_WindowHeight{};
};
