cmake_minimum_required (VERSION 3.8)

if(POLICY CMP0091)
	cmake_policy(SET CMP0091 NEW) 
endif (POLICY CMP0091)

project(scan_file)
set(CMAKE_CXX_STANDARD 17)

SET(THIS_PROJECT_NAME "scan_file")

set(SOURCE_FILE
${CMAKE_CURRENT_SOURCE_DIR}/source/main.cc
${CMAKE_CURRENT_SOURCE_DIR}/source/csvfile.h
${CMAKE_CURRENT_SOURCE_DIR}/source/iconv.h
${CMAKE_CURRENT_SOURCE_DIR}/source/win_iconv.cc
)

add_executable(${THIS_PROJECT_NAME} ${SOURCE_FILE})
## target_link_libraries(${THIS_PROJECT_NAME} )

set_target_properties(${THIS_PROJECT_NAME} PROPERTIES
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)
if(MSVC)
target_compile_options(${THIS_PROJECT_NAME} PRIVATE "/utf-8")
target_compile_definitions(${THIS_PROJECT_NAME} PRIVATE "_UNICODE" "UNICODE")
endif()

