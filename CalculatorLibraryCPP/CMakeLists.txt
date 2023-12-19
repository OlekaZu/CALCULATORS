cmake_minimum_required (VERSION 3.8)

project (Calculator)

# set(CMAKE_MAKE_PROGRAM "C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
#set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../MAUI/MyCalculator_v3.0/Libraries/")

file(GLOB SRC_LIBRARY "windows_src/*.cpp")

add_library(${PROJECT_NAME}Library SHARED ${SRC_LIBRARY})

target_include_directories(${PROJECT_NAME}Library
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/windows_src
)

set_target_properties(
    ${PROJECT_NAME}Library 
    PROPERTIES 
        PREFIX ""
        OUTPUT_NAME "CalculatorModelLibrary"
        CXX_STANDARD 17
)
