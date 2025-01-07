cmake_minimum_required(VERSION 3.5)

include(FetchContent)

project(
	TinyBlinnPhong
	VERSION 1.0.0
	LANGUAGES C
)

#SDL3 - steam builds should tick this off
option(SDL_VENDORED "I don't have SDL3 installed" ON)
if(SDL_VENDORED)
	FetchContent_Declare(
		SDL3
		GIT_REPOSITORY https://github.com/libsdl-org/SDL
		GIT_TAG preview-3.1.6
	)
	FetchContent_MakeAvailable(SDL3)
else()
	find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
endif()

file(COPY wood_floor_2.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(.)

add_executable(TestBlinnPhong 3d_math.c camera.c gl.c main.c)

# Adicione comandos de instalação para o executável do jogo (test)
#install(TARGETS ProjectRockport RUNTIME DESTINATION bin)

# Link to the actual SDL3 library.
target_link_libraries(TestBlinnPhong PRIVATE SDL3::SDL3)
target_link_libraries(TestBlinnPhong PRIVATE m)
