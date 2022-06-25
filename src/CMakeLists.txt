project(WordCountSorter)

cmake_minimum_required(VERSION 3.10)

set(SOURCES
	main.cpp
)

add_executable(${PROJECT_NAME}
	${SOURCES}
)

set_property(TARGET ${PROJECT_NAME} PROPERTY OUTPUT_NAME "freq")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
