cmake_minimum_required(VERSION 3.12)
project(PathTracer VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ======== GLM ========
add_library(
	glm INTERFACE
)
target_include_directories(glm INTERFACE dependencies/glm)

# ======== Library ========
add_library(
	PathTracer
	PathTracer/Intersection.cpp
	PathTracer/Radiance.cpp
	PathTracer/Scene.cpp
)
target_link_libraries(PathTracer PUBLIC glm)
target_include_directories(PathTracer PUBLIC . dependencies/)

# ======== Reflex ========
add_executable(
	PathTracerCLI
	PathTracerCLI/source.cpp
)
target_link_libraries(PathTracerCLI PUBLIC PathTracer)
