# CMakeList.txt : CMake project for pong, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

project ("pong")

if(NOT PLATFORM_NAME)
	set(PLATFORM_NAME "SDL2")
endif()

# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
if (WIN32)
	find_package(SDL2-image REQUIRED)
else()
	find_package(SDL2_image REQUIRED)
endif()
	

set(GAME_SOURCES
	"SDL/main.cpp"
	"SDL/main.hpp"
	"SDL/autoTex.cpp"
	"SDL/autoTex.hpp"
	"SDL/RenderWindow.cpp"
	"SDL/RenderWindow.hpp"
	"gameManager/gameManager.cpp"
	"gameManager/gameManager.hpp"
	"moveDirection.hpp"
	"gameManager/level/Level.cpp" 
	"gameManager/level/Level.hpp"
	"gameManager/sprite/sprite.cpp"
	"gameManager/sprite/sprite.hpp"
	"game/inGame/Entities/playables/Player/Player.cpp" 
	"game/inGame/Entities/playables/Player/Player.hpp" 
	"game/inGame/Entities/Renderable.cpp"
	"game/inGame/Entities/Renderable.hpp"
	"helper/Coord.hpp"
)

	
set(TEXTURE_DICTIONARY
	"texDict/texDict.cpp" 
	"texDict/texDict.hpp"
)


# Add source to this project's executable.
add_executable (
	Client 
	${GAME_SOURCES} 
	${TEXTURE_DICTIONARY}
)

if (WIN32)
target_link_libraries(Client PUBLIC SDL2::SDL2 SDL2::SDL2_image SDL2::SDL2main)
else()
SET (CMAKE_C_COMPILER "/usr/bin/clang")
SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")
target_link_libraries(Client PUBLIC SDL2::Main SDL2::Image)
endif()

# TODO: Add tests and install targets if needed.

# copy assets
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})