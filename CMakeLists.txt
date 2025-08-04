cmake_minimum_required(VERSION 3.16)
project(Enigma)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML paths
set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML")
set(SFML_INCLUDE_DIR "${SFML_DIR}/include")
set(SFML_LIB_DIR "${SFML_DIR}/lib")

# Include headers from SFML and project Header folder
include_directories(${SFML_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/Header)

# Link to SFML libraries
link_directories(${SFML_LIB_DIR})

# Find all .cpp files in Source/
file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/Source/*.cpp"
)

# Build executable
add_executable(Enigma ${SOURCES})

# Link with SFML (debug versions)
target_link_libraries(Enigma
    sfml-graphics-d
    sfml-window-d
    sfml-system-d
)

# Copy DLLs after build
add_custom_command(TARGET Enigma POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${SFML_LIB_DIR}"
    $<TARGET_FILE_DIR:Enigma>
)