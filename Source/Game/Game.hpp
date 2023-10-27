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

    void init();
    void run();
    void onClose() override;
    void shutdown();

  private:
    bool mIsRunning;
    std::unique_ptr<Engine::Win32Window> mWindow;
    std::unique_ptr<Engine::EGLManager> mEGL;
    std::unique_ptr<Engine::Renderer> m_Renderer;
  };
}  // namespace Game
