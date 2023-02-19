cmake_minimum_required(VERSION 3.0)
project(SDL_GAME1)

if(WIN32)
        set(SDL2_DIR ${PROJECT_SOURCE_DIR}/lib/cmake/SDL2)
endif()

set(SDL2_image_DIR ${PROJECT_SOURCE_DIR}/lib/cmake/SDL2_image)
set(SDL2_ttf_DIR ${PROJECT_SOURCE_DIR}/lib/cmake/SDL2_ttf)
set(SDL2_mixer_DIR ${PROJECT_SOURCE_DIR}/lib/cmake/SDL2_mixer)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src )

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE IMGUI "include/imgui/*.cpp")

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -static-libgcc -static-libstdc++")
endif()

add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI})

if(WIN32)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_link_options(${PROJECT_NAME} PRIVATE "-Wl,-subsystem,console")
    endif()
endif()

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_image SDL2_ttf SDL2_mixer)


if (CMAKE_COMPILER_IS_GNUCXX)
    add_custom_command(
     TARGET ${PROJECT_NAME} POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy
                 ${CMAKE_CURRENT_SOURCE_DIR}/bin/g++/libwinpthread-1.dll
                 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
file(GLOB MY_DLLS ${PROJECT_SOURCE_DIR}/bin/*.dll)
foreach(Current_DLL IN LISTS MY_DLLS)
    add_custom_command(
               TARGET ${PROJECT_NAME} POST_BUILD
               COMMAND ${CMAKE_COMMAND} -E copy ${Current_DLL} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
               COMMENT "Copying header: ${Current_DLL}")
endforeach()

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/assets
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)