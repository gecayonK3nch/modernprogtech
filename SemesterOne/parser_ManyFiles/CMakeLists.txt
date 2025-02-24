cmake_minimum_required(VERSION 3.10)
project(parser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_GENERATOR_PLATFORM x64)
set(CMAKE_TOOLCHAIN_FILE "C:/Users/gecay/OneDrive/Desktop/Projects/Bots/schedulegram/parser/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_PREFIX_PATH "C:/Users/gecay/OneDrive/Desktop/Projects/Bots/schedulegram/parser/vcpkg/installed/x64-windows")
find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
include_directories(${CMAKE_SOURCE_DIR})

add_executable(parser main.cpp req.cpp)
target_link_libraries(parser PRIVATE cpr::cpr nlohmann_json::nlohmann_json)
