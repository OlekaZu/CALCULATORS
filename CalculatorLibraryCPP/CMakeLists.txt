cmake_minimum_required (VERSION 3.8)

project (CalculatorSharedLib CXX)

set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/out/")

file(GLOB SRC_LIBRARY ${SOURCE_LIB})

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(ModelLibrary SHARED ${SRC_LIBRARY})

target_include_directories(ModelLibrary
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_LIB_DIR}
)

set_target_properties(
    ModelLibrary 
    PROPERTIES 
        PREFIX ""
        OUTPUT_NAME "ModelLibrary"
        SUFFIX ".dll"
        CXX_STANDARD 17
)
