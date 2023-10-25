cmake_minimum_required(VERSION 3.8)
project(Synthesis)

if(WIN32)
	add_definitions("-D_WIN32")
	set(PLATFORM_LIBRARIES winmm)
endif()

if(MSVC)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} /MT")
endif()

function(create_target_directory_groups target_name)
	source_group("Other Files" REGULAR_EXPRESSION ".")
	get_target_property(target_sources "${target_name}" SOURCES)

	foreach(file_name IN LISTS target_sources)
		get_filename_component(dir_name "${file_name}" PATH)
		string(REPLACE "/" "\\" group_name "${dir_name}")
		source_group("${group_name}" FILES "${file_name}")
	endforeach()
endfunction()

add_subdirectory(Externals)
add_subdirectory(Source)
