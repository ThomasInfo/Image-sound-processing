cmake_minimum_required(VERSION 3.10)
project(Image_processing)

set(CMAKE_CXX_STANDARD 14)
#set(EXECUTABLE_OUTPUT_PATH "build")

enable_testing()
add_subdirectory(gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(main src/main.cpp src/Reader.cpp src/Reader.h)
add_executable (readerTest test/readerTest.cpp src/Reader.cpp src/Reader.h)

target_link_libraries(readerTest gtest gtest_main)
add_test(readerTest readerTest)


find_package (PNG)
if (PNG_FOUND)

    target_include_directories(main PUBLIC ${PNG_INCLUDE_DIR})
    target_link_libraries (main ${PNG_LIBRARY})
    target_include_directories(readerTest PUBLIC ${PNG_INCLUDE_DIR})
    target_link_libraries (readerTest ${PNG_LIBRARY})

else ()

    message(FATAL_ERROR "libpng not found")
endif ()

find_package (JPEG)
if (JPEG_FOUND)

    target_include_directories(main PUBLIC ${JPEG_INCLUDE_DIR})
    target_link_libraries (main ${JPEG_LIBRARY})
    target_include_directories(readerTest PUBLIC ${JPEG_INCLUDE_DIR})
    target_link_libraries (readerTest ${JPEG_LIBRARY})

else ()

    message(FATAL_ERROR "libjpeg not found")
endif ()

find_package(Doxygen)
if(DOXYGEN_FOUND)

    # We then check if the Doxygen.in configuration file exists
    IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/doxy.in)
        message(FATAL_ERROR "Doxygen configuration file is needed to build the documentation:
         - ${CMAKE_CURRENT_SOURCE_DIR}/doxy.in not found.
         - Generate one in the project folder with doxygen -g doxy.in")
    ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/doxy.in)

    # We configure the doxyfile for make.
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxy.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
            ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            )
ELSE(DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
ENDIF(DOXYGEN_FOUND)