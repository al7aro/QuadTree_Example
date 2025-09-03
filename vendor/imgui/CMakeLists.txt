cmake_minimum_required(VERSION 3.4...3.28 FATAL_ERROR)

project(imgui)

file(GLOB_RECURSE source_files
	"./imgui/imgui.cpp"
	"./imgui/imgui.h"
	"./imgui/imconfig.h"
	"./imgui/imgui_demo.cpp"
	"./imgui/imgui_draw.cpp"
	"./imgui/imgui_internal.h"
	"./imgui/imgui_tables.cpp"
	"./imgui/imgui_widgets.cpp"
	"./imgui/imstb_rectpack.h"
	"./imgui/imstb_textedit.h"
	"./imgui/imstb_truetype.h"

	"./imgui/backends/imgui_impl_glfw.cpp"
	"./imgui/backends/imgui_impl_glfw.h"
	"./imgui/backends/imgui_impl_opengl3.cpp"
	"./imgui/backends/imgui_impl_opengl3.h"
)

add_library(imgui ${source_files})

target_include_directories(imgui PUBLIC ../glfw/glfw/include ./imgui/backends/ ./imgui)
set_target_properties(imgui
    PROPERTIES
    CXX_STANDARD 11
    CXX_EXTENSIONS off

	ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${IMGUI_OUTPUT_DIRECTORY_DEBUG}
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${IMGUI_OUTPUT_DIRECTORY_DEBUG}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${IMGUI_OUTPUT_DIRECTORY_DEBUG}

    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${IMGUI_OUTPUT_DIRECTORY_RELEASE}
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${IMGUI_OUTPUT_DIRECTORY_RELEASE}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${IMGUI_OUTPUT_DIRECTORY_RELEASE}
	
	FOLDER ${WORKSPACE_NAME}/vendor
) 