cmake_minimum_required(VERSION 3.10)
project(Image_sound_processing)

set(CMAKE_CXX_STANDARD 14)



add_executable(main src/main.cpp)

# Recherche la dépendance externe
find_package (PNG)
if (PNG_FOUND)
    # Une fois la dépendance trouvée, nous l'incluons au projet
    target_include_directories(main PUBLIC ${PNG_INCLUDE_DIR})
    target_link_libraries (main ${PNG_LIBRARY})
else ()
    # Sinon, nous affichons un message
    message(FATAL_ERROR "libpng not found")
endif ()