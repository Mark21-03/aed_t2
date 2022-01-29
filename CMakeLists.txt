cmake_minimum_required(VERSION 3.19)
project(aed_t2)

set(CMAKE_CXX_STANDARD 11)

set(CREATE_EXE TRUE)


if (CMAKE_BUILD_TYPE MATCHES Debug)

    add_executable(aed_t2 main.cpp

            src/graph.cpp include/graph.h
            include/Utils.h src/menu.cpp include/menu.h include/minHeap.h src/files_reader.cpp
            include/files_reader.h include/GraphBuilder.h include/structs.h src/GraphBuilder.cpp
            src/InverseGraph.cpp include/InverseGraph.h include/GraphInverseBuilder.h src/GraphInverseBuilder.cpp include/menuAsks.h)


endif ()
