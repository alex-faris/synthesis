#pragma once

#include <cstdint>
#include <list>
#include <vector>

#if defined(_WIN32)
  #include "Win32/Win32Types.hpp"
#endif

#include "WindowObserver.hpp"

namespace Engine
{
  class Window
  {
  public:
    virtual ~Window() = default;

    virtual WindowHandle GetNativeHandle() const = 0;
    virtual std::uint32_t GetNativeWidth() const = 0;
    virtual std::uint32_t GetNativeHeight() const = 0;
    virtual void Update() = 0;

    void CreateObserver(WindowObserver* observer);
    void DestroyObserver(WindowObserver* observer);

  protected:
    void NotifyResize(std::uint32_t new_width, std::uint32_t new_height) const;
    void NotifyClose();

  private:
    std::vector<WindowObserver*> m_Observers;
  };
}  // namespace Engine
