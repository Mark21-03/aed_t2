cmake_minimum_required(VERSION 3.10)
project(aed_t2)

set(CMAKE_CXX_STANDARD 11)

set(CREATE_EXE TRUE)  #creates a exe folder for the execution file in cmake-buid-release


if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_subdirectory(lib/googletest-master)
    include_directories(lib/googletest-master/googletest/include)
    include_directories(lib/googletest-master/googlemock/include)

    add_executable(aed_t2 mainTest.cpp Tests/tests.cpp

            src/file.cpp include/file.h
            )

    target_link_libraries(aed_t2 gtest gtest_main)
    message("Debug mode")

endif ()


if (CMAKE_BUILD_TYPE MATCHES Release)

    add_executable(aed_t2 main.cpp

            src/file.cpp include/file.h
            )
    message("Release mode")

endif ()
