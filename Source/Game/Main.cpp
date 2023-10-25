#include <iostream>
#include <memory>

#include <Engine/Graphics/EGLManager.hpp>

#if defined(_WIN32)
  #include <Engine/Window/Win32/Win32Window.hpp>
#endif  // _WIN32

int main()
{
#if defined(_WIN32)
  std::unique_ptr<Engine::Win32Window> window = std::make_unique<Engine::Win32Window>(1280, 720);
#endif  //_WIN32

  if (!window->TryCreate())
  {
    window->Destroy();
    return -1;
  }

  std::cout << "Window creation OK!" << std::endl;

  Engine::EGLManager eglManager(*window);
  if (!eglManager.TryCreate())
  {
    eglManager.Destroy();
    return -1;
  }

  std::cout << "EGL hook OK!" << std::endl;

  // Debug pause just to see if the window works
  std::cin.get();

  eglManager.Destroy();
  window->Destroy();
  return 0;
}
