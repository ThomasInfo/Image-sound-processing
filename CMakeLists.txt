cmake_minimum_required(VERSION 3.10)
project(Image_processing)

set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_OUTPUT_PATH "build")

enable_testing()
add_subdirectory(gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(main src/main.cpp src/Reader.cpp src/Reader.h)
add_executable (readerTest test/readerTest.cpp src/Reader.cpp src/Reader.h)

target_link_libraries(readerTest gtest gtest_main)
add_test(readerTest readerTest)

# Recherche la dépendance externe
find_package (PNG)
if (PNG_FOUND)
    # Une fois la dépendance trouvée, nous l'incluons au projet
    target_include_directories(main PUBLIC ${PNG_INCLUDE_DIR})
    target_link_libraries (main ${PNG_LIBRARY})
    target_include_directories(readerTest PUBLIC ${PNG_INCLUDE_DIR})
    target_link_libraries (readerTest ${PNG_LIBRARY})

else ()
    # Sinon, nous affichons un message
    message(FATAL_ERROR "libpng not found")
endif ()