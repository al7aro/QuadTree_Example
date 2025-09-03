cmake_minimum_required(VERSION 3.4...3.28 FATAL_ERROR)

project(stb
    LANGUAGES C
)

file(GLOB_RECURSE source_files
    "./stb/stb_image.c"
)

add_library(stb
    ${source_files}
)

set_target_properties(stb PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug/vendor/stb
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug/vendor/stb
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug/vendor/stb

    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release/vendor/stb
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release/vendor/stb
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release/vendor/stb
	
	FOLDER vendor
)

target_include_directories(stb PUBLIC "./stb/include/glad")