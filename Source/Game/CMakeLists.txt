include_directories(.)

add_executable(Game
	"Main.cpp"
)

target_link_libraries(Game PRIVATE Engine)
create_target_directory_groups("Game")
