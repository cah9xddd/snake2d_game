cmake_minimum_required(VERSION 3.5)
project(snake_game VERSION 1.0)

# Set output directory
if(CMAKE_GENERATOR MATCHES "Visual Studio")
    foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES}) # We need that loop for VS 
        string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
        string(TOLOWER ${OUTPUTCONFIG} OUTPUTCONFIGLOWER)
        set(MY_OUTPUT_DIR ${CMAKE_BINARY_DIR}/v.${CMAKE_PROJECT_VERSION}-${OUTPUTCONFIGLOWER})
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${MY_OUTPUT_DIR})
    endforeach()
else()
    string(TOLOWER ${CMAKE_BUILD_TYPE} OUTPUTCONFIG)
    set(MY_OUTPUT_DIR ${CMAKE_BINARY_DIR}/v.${CMAKE_PROJECT_VERSION}-${OUTPUTCONFIG})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MY_OUTPUT_DIR}) 
endif()

include_directories(${PROJECT_NAME}  ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src )

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

# Find SDL2 package
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE   $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
                                                $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>)

find_package(SDL2_image CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)

find_package(SDL2_mixer CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>)

find_package(SDL2_ttf CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>)

# Find + link ImGui package
find_package(imgui CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/assets
                $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)