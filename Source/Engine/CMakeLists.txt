include_directories(.)

add_library(Engine STATIC
	"Graphics/EGLManager.hpp"
	"Graphics/EGLManager.cpp"
	"Window/Window.hpp"
	"Window/Win32/Win32Types.hpp"
	"Window/Win32/Win32Window.hpp"
	"Window/Win32/Win32Window.cpp"
)

if(MSVC)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} /MT")
endif()

set(LIBRARIES_DIR "${CMAKE_SOURCE_DIR}/Libraries")

if(WIN32)
	target_link_libraries(Engine PUBLIC
		$<$<CONFIG:DEBUG>:${LIBRARIES_DIR}/Win32/Debug/libEGL.lib>
		$<$<CONFIG:DEBUG>:${LIBRARIES_DIR}/Win32/Debug/libGLESv2.lib>
		$<$<CONFIG:DEBUG>:${LIBRARIES_DIR}/Win32/Debug/zlibd.lib>
		$<$<NOT:$<CONFIG:Debug>>:${LIBRARIES_DIR}/Win32/Release/libEGL.lib>
		$<$<NOT:$<CONFIG:Debug>>:${LIBRARIES_DIR}/Win32/Release/libGLESv2.lib>
		$<$<NOT:$<CONFIG:Debug>>:${LIBRARIES_DIR}/Win32/Release/zlib.lib>)
endif()

target_link_libraries(Engine PUBLIC egl)
target_link_libraries(Engine PUBLIC gles3)
create_target_directory_groups("Engine")
