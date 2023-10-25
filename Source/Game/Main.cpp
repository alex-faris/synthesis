#include <iostream>
#include <memory>

#include <Engine/Graphics/EGLManager.hpp>
#include <Engine/Graphics/Renderer.hpp>

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
    window->Destroy();

    return -1;
  }
  std::cout << "EGL creation OK!" << std::endl;

  Engine::Renderer renderer(eglManager);
  if (!renderer.TryCreate())
  {
    renderer.Destroy();
    eglManager.Destroy();
    window->Destroy();

    return -1;
  }
  std::cout << "Renderer creation OK!" << std::endl;

  while (true)
  {
    static std::size_t i = 0;

    renderer.Draw();
    renderer.Update();

    std::cout << i++ << std::endl;  // Still no event polling :]
  }

  renderer.Destroy();
  eglManager.Destroy();
  window->Destroy();
  return 0;
}
