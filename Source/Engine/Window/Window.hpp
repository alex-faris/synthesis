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

    virtual WindowHandle getHandle() const = 0;
    virtual u32 getWidth() const = 0;
    virtual u32 getHeight() const = 0;
    virtual void update() = 0;

    void createObserver(WindowObserver* observer);
    void destroyObserver(WindowObserver* observer);

  protected:
    void notifyResize(u32 new_width, u32 new_height) const;
    void notifyClose();

  private:
    std::vector<WindowObserver*> mObservers;
  };
}  // namespace Engine
