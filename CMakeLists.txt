cmake_minimum_required (VERSION 3.8)

project(scan_file)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
SET(THIS_PROJECT_NAME "scan_file")

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILE
${CMAKE_CURRENT_SOURCE_DIR}/source/main.cc
${CMAKE_CURRENT_SOURCE_DIR}/source/csvfile.h
${CMAKE_CURRENT_SOURCE_DIR}/source/iconv.h
${CMAKE_CURRENT_SOURCE_DIR}/source/win_iconv.cc
)

add_executable(${THIS_PROJECT_NAME} ${SOURCE_FILE})
## target_link_libraries(${THIS_PROJECT_NAME} )

if(MSVC)
target_compile_options(${THIS_PROJECT_NAME} PRIVATE "/utf-8")
target_compile_definitions(${THIS_PROJECT_NAME} PRIVATE "_UNICODE" "UNICODE")
endif()

