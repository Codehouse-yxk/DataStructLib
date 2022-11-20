cmake_minimum_required(VERSION 3.16.3)
project(DataStructLib)

set(CMAKE_CXX_STANDARD 98)

#自动查找源文件
message("list dir: " ${CMAKE_CURRENT_LIST_DIR})
file(GLOB_RECURSE SRC_DIR_LIST "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
LIST(APPEND SRC_DIR_LIST ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
LIST(REMOVE_DUPLICATES SRC_DIR_LIST) #去重
message("find src file: " ${SRC_DIR_LIST})

#自动查找头文件
macro(FIND_INCLUDE_DIR result curdir)  #定义函数,参数:result 存放结果；curdir 指定路径；
    file(GLOB_RECURSE children "${curdir}/*.hpp" "${curdir}/*.h")
    message(STATUS "children= ${children}")
    set(dirlist "")
    foreach (child ${children})
        string(REGEX REPLACE "(.*)/.*" "\\1" LIB_NAME ${child})
        if (IS_DIRECTORY ${LIB_NAME})
            LIST(APPEND dirlist ${LIB_NAME})
        endif ()
    endforeach ()
    LIST(REMOVE_DUPLICATES dirlist) #去重
    set(${result} ${dirlist})
endmacro()

#查找include目录下的所有*.hpp,*.h头文件,并路径列表保存到 INCLUDE_DIR_LIST 变量中
FIND_INCLUDE_DIR(INC_DIR_LIST ${PROJECT_SOURCE_DIR}/src)
message("find inc dir: " ${INC_DIR_LIST})
include_directories(${INC_DIR_LIST})

add_executable(DataStructLib ${SRC_DIR_LIST})