cmake_minimum_required(VERSION 3.0.0)
project(day01 VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

set(PRJ_SRC
    main.cpp 
    load_data.cpp
    day01.cpp
)

add_executable(${PROJECT_NAME} ${PRJ_SRC})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
