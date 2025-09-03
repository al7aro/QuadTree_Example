cmake_minimum_required(VERSION 3.4...3.28 FATAL_ERROR)

project(glad
    LANGUAGES C
)

file(GLOB_RECURSE source_files
    "./glad${GLAD_VERSION}/src/glad.c"
    "./glad${GLAD_VERSION}/include/glad/glad.h"
    "./glad${GLAD_VERSION}/include/KHR/khrplatform.h"
)

add_library(glad
    ${source_files}
)

set_target_properties(glad PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug/vendor/glad
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug/vendor/glad
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug/vendor/glad

    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release/vendor/glad
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release/vendor/glad
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release/vendor/glad
	
	FOLDER vendor
)

target_include_directories(glad PRIVATE "./glad${GLAD_VERSION}/include/KHR")
target_include_directories(glad PUBLIC "./glad${GLAD_VERSION}/include")
