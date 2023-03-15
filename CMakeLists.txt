cmake_minimum_required(VERSION 3.10)

project(HMCCC)

aux_source_directory(./src DIR_SRCS)

find_package(CURL REQUIRED)

find_package(cpprestsdk REQUIRED)

include_directories(./include ${CURL_INCLUDE_DIR})

add_executable(ConsoleLauncher ${DIR_SRCS} )

target_link_libraries(ConsoleLauncher ${CURL_LIBRARIES} cpprestsdk::cpprest)