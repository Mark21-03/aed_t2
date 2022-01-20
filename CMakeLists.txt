cmake_minimum_required(VERSION 3.19)
project(aed_t2)

set(CMAKE_CXX_STANDARD 11)

set(CREATE_EXE TRUE)


if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_subdirectory(lib/googletest-master)
    include_directories(lib/googletest-master/googletest/include)
    include_directories(lib/googletest-master/googlemock/include)

    add_executable(aed_t2 mainTest.cpp Tests/tests.cpp

            src/graph.cpp include/graph.h
            src/distanceCalc.cpp include/distanceCalc.h src/menu.cpp include/menu.h include/minHeap.h src/files_reader.cpp include/files_reader.h src/Model.cpp include/Model.h)

    target_link_libraries(aed_t2 gtest gtest_main)
    message("Debug mode")

endif ()


if (CMAKE_BUILD_TYPE MATCHES Release)

    add_executable(aed_t2 main.cpp

            src/graph.cpp include/graph.h
            src/distanceCalc.cpp include/distanceCalc.h src/menu.cpp include/menu.h include/minHeap.h src/files_reader.cpp include/files_reader.h src/Model.cpp include/Model.h)

    message("Release mode")

endif ()
