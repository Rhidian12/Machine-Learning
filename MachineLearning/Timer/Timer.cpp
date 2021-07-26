#include "Timer.h"

Timer::Timer()
	: m_MaxElapsedSeconds{ 0.1f }
	, m_ElapsedSeconds{}
	, m_TotalElapsedSeconds{}
	, m_FPS{}
	, m_FPSCounter{}
	, m_FPSTimer{}
	, m_TimePerFrame{ 1.f / 144.f }
{
	Start();
}

Timer* Timer::GetInstance() noexcept
{
    if (!m_pInstance)
        m_pInstance = new Timer{};

    return m_pInstance;
}

void Timer::Cleanup() noexcept
{
    delete m_pInstance;
    m_pInstance = nullptr;
}

void Timer::Start()
{
	m_PreviousTimepoint = std::chrono::steady_clock::now();
}

void Timer::Update()
{
	m_StartTimepoint = std::chrono::steady_clock::now();
	m_ElapsedSeconds = std::chrono::duration<float>(m_StartTimepoint - m_PreviousTimepoint).count();
	m_ElapsedSeconds = std::min(m_ElapsedSeconds, m_MaxElapsedSeconds);
	m_TotalElapsedSeconds += m_ElapsedSeconds;

	m_PreviousTimepoint = m_StartTimepoint;

	m_FPS = int(1.f / m_ElapsedSeconds);
}

int Timer::GetFPS() const noexcept
{
	return m_FPS;
}

float Timer::GetElapsedSeconds() const noexcept
{
	return m_ElapsedSeconds;
}

float Timer::GetTimePerFrame() const noexcept
{
	return m_TimePerFrame;
}

float Timer::GetTotalElapsedSeconds() const noexcept
{
	return m_TotalElapsedSeconds;
}
