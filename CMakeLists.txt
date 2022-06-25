project(WordCountSorterProject)

cmake_minimum_required(VERSION 3.10)

FILE(GLOB DOC_FILES "README.md" "docs/*")
add_custom_target(docs SOURCES ${DOC_FILES})

add_subdirectory(src)

if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT WordCountSorter)
endif()
