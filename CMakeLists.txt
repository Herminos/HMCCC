cmake_minimum_required(VERSION 3.10)

project(HMCCC)

cmake_policy(SET CMP0074 NEW)

aux_source_directory(./src/account DIR_SRCS_ACCOUNT)

aux_source_directory(./src/download DIR_SRCS_DOWNLOAD)

aux_source_directory(./src/launch DIR_SRCS_LAUNCH)

aux_source_directory(./src/native DIR_SRCS_NATIVE)

aux_source_directory(./src/net DIR_SRCS_NET)

aux_source_directory(./src DIR_SRCS)

set(CMAKE_CXX_STANDARD 17)

set(BOOST_ROOT C:/boost_1_81_0)

set(Boost_NO_SYSTEM_PATHS ON)

find_package(CURL REQUIRED)

find_package(Boost REQUIRED)

include_directories(./include ${CURL_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

add_executable(ConsoleLauncher 
                ${DIR_SRCS}
                ${DIR_SRCS_DOWNLOAD} 
                ${DIR_SRCS_LAUNCH} 
                ${DIR_SRCS_NATIVE} 
                ${DIR_SRCS_ACCOUNT}
                ${DIR_SRCS_NET}
            )

target_link_libraries(ConsoleLauncher ${CURL_LIBRARIES} ${Boost_LIBRARIES})