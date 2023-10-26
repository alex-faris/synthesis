#pragma once

#include <list>
#include <vector>

#if defined(_WIN32)
  #include "Win32/Win32Types.hpp"
#endif

#include "Engine/Types.hpp"

#include "WindowObserver.hpp"

namespace Engine
{
  class Window
  {
  public:
    virtual ~Window() = default;

    virtual WindowHandle GetNativeHandle() const = 0;
    virtual u32 GetNativeWidth() const = 0;
    virtual u32 GetNativeHeight() const = 0;
    virtual void Update() = 0;

    void CreateObserver(WindowObserver* observer);
    void DestroyObserver(WindowObserver* observer);

  protected:
    void NotifyResize(u32 new_width, u32 new_height) const;
    void NotifyClose();

  private:
    std::vector<WindowObserver*> m_Observers;
  };
}  // namespace Engine
