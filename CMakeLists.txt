cmake_minimum_required(VERSION 3.5)
project(snake_game VERSION 1.0)

if(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(PLATFORM "Win64")
    else()
        set(PLATFORM "Win32")
    endif()
elseif(APPLE)
    set(PLATFORM "Mac")
elseif(UNIX)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(PLATFORM "Linux64")
    else()
        set(PLATFORM "Linux32")
    endif()
endif()


# Set output directory into standart BUILD_TYPE/PLATFORM/VERSION_FOLDER/EXECUTABLE
if(CMAKE_GENERATOR MATCHES "Visual Studio")
    foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES}) # We need that loop for VS 
        string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIGUPPER)
        string(TOLOWER ${OUTPUTCONFIG} OUTPUTCONFIGLOWER)
        set(MY_OUTPUT_DIR ${CMAKE_BINARY_DIR}/${OUTPUTCONFIG}/${PLATFORM}/v.${CMAKE_PROJECT_VERSION})
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIGUPPER} ${MY_OUTPUT_DIR})
    endforeach()
else() 
    string(TOLOWER ${CMAKE_BUILD_TYPE} OUTPUTCONFIG)
    set(MY_OUTPUT_DIR ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${PLATFORM}/v.${CMAKE_PROJECT_VERSION})
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