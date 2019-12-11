cmake_minimum_required(VERSION 3.10)
project(Image_processing)

set(CMAKE_CXX_STANDARD 14)
set( CMAKE_CXX_FLAGS "-pthread")
enable_testing()
add_subdirectory(gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#include_directories(libraries)


add_executable(main src/main.cpp src/Run.cpp src/Run.h src/Reader.cpp src/Reader.h src/ContourExtractor.cpp src/ContourExtractor.h src/Writer.cpp src/Writer.h src/FFT.h src/FFT.cpp src/Histogram.h src/Histogram.cpp)
add_executable(readerTest test/readerTest.cpp src/Reader.cpp src/Reader.h)
add_executable(contourExtractorTest test/contourExtractorTest.cpp src/ContourExtractor.h src/ContourExtractor.cpp src/Reader.cpp src/Reader.h src/Writer.h src/Writer.cpp)
add_executable(histogramTest test/histogramTest.cpp src/Histogram.cpp src/Histogram.h src/Reader.h src/Reader.cpp)
add_executable(fftTest test/fftTest.cpp src/FFT.cpp src/FFT.h src/Reader.h src/Reader.cpp src/Writer.cpp src/Writer.h)
add_executable(writerTest test/writerTest.cpp src/Writer.cpp src/Writer.h src/Reader.h src/Reader.cpp)

target_link_libraries(readerTest gtest gtest_main)
add_test(readerTest readerTest)

target_link_libraries(contourExtractorTest gtest gtest_main)
add_test(contourExtractorTest contourExtractorTest)

target_link_libraries(histogramTest gtest gtest_main)
add_test(histogramTest histogramTest)

target_link_libraries(fftTest gtest gtest_main)
add_test(fftTest fftTest)

target_link_libraries(writerTest gtest gtest_main)
add_test(writerTest writerTest)

find_package (PNG)
if (PNG_FOUND)
    MESSAGE("PNG information:")
    MESSAGE("  PNG_INCLUDE_DIR: ${PNG_INCLUDE_DIR}")
    MESSAGE("  PNG_LIBRARIES: ${PNG_LIBRARY}")
    target_include_directories(main PUBLIC ${PNG_INCLUDE_DIR})
    target_link_libraries (main ${PNG_LIBRARY})
    target_include_directories(readerTest PUBLIC ${PNG_INCLUDE_DIR})
    target_link_libraries (readerTest ${PNG_LIBRARY})
    target_include_directories(contourExtractorTest PUBLIC ${PNG_INCLUDE_DIR})
    target_link_libraries (contourExtractorTest ${PNG_LIBRARY})
    target_include_directories(histogramTest PUBLIC ${PNG_INCLUDE_DIR})
    target_link_libraries (histogramTest ${PNG_LIBRARY})
    target_include_directories(fftTest PUBLIC ${PNG_INCLUDE_DIR})
    target_link_libraries (fftTest ${PNG_LIBRARY})
    target_include_directories(writerTest PUBLIC ${PNG_INCLUDE_DIR})
    target_link_libraries (writerTest ${PNG_LIBRARY})

else ()

    message(FATAL_ERROR "libpng not found")
endif ()

find_package (JPEG)
if (JPEG_FOUND)
    MESSAGE("JPEG information:")
    MESSAGE("  JPEG_INCLUDE_DIR: ${JPEG_INCLUDE_DIR}")
    MESSAGE("  JPEG_LIBRARIES: ${JPEG_LIBRARY}")
    target_include_directories(main PUBLIC ${JPEG_INCLUDE_DIR})
    target_link_libraries (main ${JPEG_LIBRARY})
    target_include_directories(readerTest PUBLIC ${JPEG_INCLUDE_DIR})
    target_link_libraries (readerTest ${JPEG_LIBRARY})
    target_include_directories(contourExtractorTest PUBLIC ${JPEG_INCLUDE_DIR})
    target_link_libraries (contourExtractorTest ${JPEG_LIBRARY})
    target_include_directories(histogramTest PUBLIC ${JPEG_INCLUDE_DIR})
    target_link_libraries (histogramTest ${JPEG_LIBRARY})
    target_include_directories(fftTest PUBLIC ${JPEG_INCLUDE_DIR})
    target_link_libraries (fftTest ${JPEG_LIBRARY})
    target_include_directories(writerTest PUBLIC ${JPEG_INCLUDE_DIR})
    target_link_libraries (writerTest ${JPEG_LIBRARY})

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