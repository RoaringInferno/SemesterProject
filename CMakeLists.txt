cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(SemesterProject)

set(EXEC_NAME ${PROJECT_NAME})

add_executable(${EXEC_NAME})
file(GLOB_RECURSE ${EXEC_NAME}_SOURCES "src/*.cpp")
target_sources(${EXEC_NAME} PRIVATE ${${EXEC_NAME}_SOURCES})
target_include_directories(${EXEC_NAME} PRIVATE "include")

add_subdirectory(libs/light-csv)
target_link_libraries(${EXEC_NAME} PRIVATE light-csv)

add_subdirectory(libs/cli-parser)
target_link_libraries(${EXEC_NAME} PRIVATE cli-parser)

add_subdirectory(libs/light-log)
target_link_libraries(${EXEC_NAME} PRIVATE light-log)