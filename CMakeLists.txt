cmake_minimum_required(VERSION 3.10)
project(SM9 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Compiler warning flags
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -O2)
elseif(MSVC)
    add_compile_options(/W4 /O2)
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# SM9 Library source files
set(SM9_SOURCES
    src/core/bigint.c
    src/core/field2.c
    src/core/field4.c
    src/core/field12.c
    src/curve/point.c
    src/curve/point2.c
    src/curve/pairing.c
    src/hash/sm3.c
    src/hash/sm4.c
    src/sm9/params.c
    src/sm9/sm9_dsa.c
    src/sm9/sm9_ka.c
    src/sm9/sm9_pkc.c
    src/utility.c
)

# SM9 Library headers
set(SM9_HEADERS
    include/sm9/core/bigint.h
    include/sm9/core/field2.h
    include/sm9/core/field4.h
    include/sm9/core/field12.h
    include/sm9/curve/point.h
    include/sm9/curve/point2.h
    include/sm9/curve/pairing.h
    include/sm9/hash/sm3.h
    include/sm9/hash/sm4.h
    include/sm9/sm9/params.h
    include/sm9/sm9/sm9_dsa.h
    include/sm9/sm9/sm9_ka.h
    include/sm9/sm9/sm9_pkc.h
    include/sm9/utility.h
)

# Create static library
add_library(sm9 STATIC ${SM9_SOURCES} ${SM9_HEADERS})

# Link math library on Unix-like systems
if(UNIX)
    target_link_libraries(sm9 m)
endif()

# Test executable
add_executable(sm9_test tests/test_sm9.c)
target_link_libraries(sm9_test sm9)

# Output directories
set_target_properties(sm9 PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

set_target_properties(sm9_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Install targets
install(TARGETS sm9 sm9_test
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install headers
install(DIRECTORY include/sm9 DESTINATION include)
