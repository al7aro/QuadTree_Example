set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug/vendor/glfw)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug/vendor/glfw)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug/vendor/glfw)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release/vendor/glfw)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release/vendor/glfw)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release/vendor/glfw)


add_subdirectory("./glfw")
set_target_properties(uninstall PROPERTIES
	FOLDER vendor/GLFW3
)
set_target_properties(glfw PROPERTIES
	FOLDER vendor/GLFW3
)
set_target_properties(update_mappings PROPERTIES
	FOLDER vendor/GLFW3
)