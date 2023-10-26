#pragma once

#include <memory>

#include <Engine/Graphics/EGLManager.hpp>
#include <Engine/Graphics/Renderer.hpp>
#include <Engine/Window/Win32/Win32Window.hpp>

namespace Game
{
  class Game : Engine::WindowObserver
  {
  public:
    Game();
    ~Game();

    void Init();
    void Run();
    void OnClose() override;
    void Shutdown();

  private:
    bool m_IsRunning;
    std::unique_ptr<Engine::Win32Window> m_Window;
    std::unique_ptr<Engine::EGLManager> m_EGL;
    std::unique_ptr<Engine::Renderer> m_Renderer;
  };
}  // namespace Game
