cmake_minimum_required(VERSION 2.8)

project(student_toolkit)
add_executable(${PROJECT_NAME} "main.cpp" 
	"png_toolkit.cpp" "png_toolkit.h"
	"stb_image.h" "stb_image_write.h"
	"Configs.cpp" "Configs.h"
	"Filter.cpp" "Filter.h"
	"FilterRed.cpp" "FilterRed.h"
	"FilterIntensity.cpp" "FilterIntensity.h"
	"FilterNeighborhood.cpp" "FilterNeighborhood.h"
	"FilterBlur.cpp" "FilterBlur.h"
	"FilterEdge.cpp" "FilterEdge"
	"FilterThreshold.cpp" "FilterThreshold.h"
	"FilterThreshold2.cpp" "FilterThreshold2.h")