cmake_minimum_required(VERSION 3.10)

project(HMCCC)

cmake_policy(SET CMP0074 NEW)

aux_source_directory(./src DIR_SRCS)

set(BOOST_ROOT C:/boost_1_81_0)

set(Boost_NO_SYSTEM_PATHS ON)

find_package(CURL REQUIRED)

find_package(Boost REQUIRED)

include_directories(./include ${CURL_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

add_executable(ConsoleLauncher ${DIR_SRCS} )

target_link_libraries(ConsoleLauncher ${CURL_LIBRARIES} ${Boost_LIBRARIES})