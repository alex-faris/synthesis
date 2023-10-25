include_directories(.)

set_property(DIRECTORY APPEND PROPERTY
	COMPILE_DEFINITIONS $<$<CONFIG:Debug>:"_DEBUG"> $<$<NOT:$<CONFIG:Debug>>:"NDEBUG">)

if(MSVC)
	set(CMAKE_CONFIGURATION_TYPES "Debug" "Release" CACHE STRING "" FORCE)

	add_definitions(
		"-D_CRT_NONSTDC_NO_DEPRECATE" 
		"-D_SCL_SECURE_NO_WARNINGS"
		"-DNOMINMAX"
		"-DWIN32_LEAN_AND_MEAN"
		"-DUNICODE" 
		"-D_UNICODE"
	)

	add_compile_options(
		"/MP"
		"/Zm200"
		"/Zo"
		"/permissive-"
		"/EHsc"
		"/std:c++14"
		"/utf-8"
		"/volatile:iso"
		"/Zc:externConstexpr"
		"/Zc:inline"
		"/Zc:preprocessor"
		"/Zc:throwingNew"
		"/GT"
		"/external:anglebrackets"
		"/external:W0"
		"/W4"
		"/WX"
		"/Zi"
		$<$<CONFIG:Release>:"/GS">
	)

		set(CMAKE_EXE_LINKER_FLAGS_DEBUG "/DEBUG /MANIFEST:NO" CACHE STRING "" FORCE)
		set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/DEBUG /MANIFEST:NO /INCREMENTAL:NO /OPT:REF,ICF" CACHE STRING "" FORCE)
endif()

add_subdirectory(Engine)
add_subdirectory(Game)
