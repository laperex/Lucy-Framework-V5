cmake_minimum_required(VERSION 3.0.0)
project(Test VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB_RECURSE TARGET_SRC "src/*.cpp" "src/*.c" "./dependencies/src/*.cpp" "./dependencies/src/*.c")

include(C:/Users/krishnadev/vcpkg/scripts/buildsystems/vcpkg.cmake)
include_directories("./dependencies/include/" src C:/Users/krishnadev/vcpkg/installed/x64-windows/include)

set(CMAKE_CXX_STANDARD 20)

add_executable(main ${TARGET_SRC})

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main)

find_path(STB_INCLUDE_DIRS "stb_c_lexer.h")
target_include_directories(main PRIVATE ${STB_INCLUDE_DIRS})

find_package(EnTT CONFIG REQUIRED)
target_link_libraries(main PRIVATE EnTT::EnTT)

find_package(glm CONFIG REQUIRED)
target_link_libraries(main PRIVATE glm::glm)

find_package(glad CONFIG REQUIRED)
target_link_libraries(main PRIVATE glad::glad)

target_link_libraries(main PRIVATE)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)