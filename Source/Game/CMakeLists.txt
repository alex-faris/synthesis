include_directories(.)

add_executable(Game
	"Main.cpp"
)

if (MSVC)
    set_property(TARGET Game PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
endif()

add_custom_command(TARGET Game POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/Data $<TARGET_FILE_DIR:Game>/Data)

target_link_libraries(Game PRIVATE Engine)
create_target_directory_groups("Game")
