cmake_minimum_required(VERSION 3.0)
project(linux-test)

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

include_directories(${PROJECT_NAME}  ${SDL2_INCLUDE_DIRS} )

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_image SDL2_ttf SDL2_mixer)

#file(GLOB MY_DLLS ${PROJECT_SOURCE_DIR}/bin/*.dll)

#foreach(Current_DLL IN LISTS MY_DLLS)
#    add_custom_command(
#               TARGET ${PROJECT_NAME} POST_BUILD
#               COMMAND ${CMAKE_COMMAND} -E copy ${Current_DLL} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
#               COMMENT "Copying header: ${Current_DLL}")
#endforeach()

#add_custom_command(
#        TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#                ${CMAKE_CURRENT_SOURCE_DIR}/assets
#                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)