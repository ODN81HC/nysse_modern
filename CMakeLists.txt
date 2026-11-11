cmake_minimum_required(VERSION 3.22)
project(nysse_modern LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Create build/compile_commands.json for VSCode so that F12 works

find_package(Eigen3 3.4 REQUIRED)
find_package(OpenCV REQUIRED)

add_library(nysse_core STATIC
    src/location.cpp
    src/initerror.cpp
    src/statistics.cpp
    src/playeractor.cpp
    src/enemy.cpp
    src/modern_city.cpp
    src/pinhole_camera.cpp
)

target_include_directories(nysse_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(nysse_core PUBLIC
    Eigen3::Eigen
    ${OpenCV_LIBS}
)

include(cmake/CompilerWarnings.cmake)
myproject_set_project_warnings(nysse_core FALSE "" "" "" "")
target_compile_options(nysse_core PRIVATE ${PROJECT_WARNINGS_CXX})

enable_testing()
find_package(GTest REQUIRED)
# Create executable target from test .cpp file
add_executable(test_nysse_core
    test/test_nysse_core.cpp
)
# Tell CMake: "This test needs symbols and headers from nysse_code and GoogleTest"
target_link_libraries(test_nysse_core PRIVATE
    nysse_core
    GTest::gtest
    GTest::gtest_main
)
target_compile_options(test_nysse_core PRIVATE ${PROJECT_WARNINGS_CXX})
include(GoogleTest)
gtest_discover_tests(test_nysse_core)