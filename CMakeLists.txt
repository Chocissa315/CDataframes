cmake_minimum_required(VERSION 3.27)
project(CDataframes)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CDataframes
        .idea/.gitignore
        .idea/CDataframes.iml
        .idea/modules.xml
        .idea/vcs.xml
        Column.c
        Column.h
        README.md
        main.c
        list.h
        cdataframe.c
        cdataframe.h
)
