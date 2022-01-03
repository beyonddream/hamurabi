cmake_minimum_required(VERSION 3.17)

project(hamurabi VERSION 0.1
        DESCRIPTION "Hamurabi - a text adventure game written in C99"
            LANGUAGES C ASM
        )
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(DISABLE_TESTS "If tests should be compiled or not" ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# C11 minimum
set(CMAKE_C_STANDARD 11)
# Show all warning messages
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Og")

# Build Types
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE}
    CACHE STRING "Choose the type of build, options are: asan lsan msan ubsan"
    FORCE)

# AddressSanitize
set(CMAKE_C_FLAGS_ASAN
    "${CMAKE_C_FLAGS} -fsanitize=address -fno-optimize-sibling-calls -fsanitize-address-use-after-scope -fno-omit-frame-pointer -g"
    CACHE STRING "Flags used by the C compiler during AddressSanitizer builds."
    FORCE)

# LeakSanitizer
set(CMAKE_C_FLAGS_LSAN
    "${CMAKE_C_FLAGS} -fsanitize=leak -fno-omit-frame-pointer -g"
    CACHE STRING "Flags used by the C compiler during LeakSanitizer builds."
    FORCE)

# MemorySanitizer
set(CMAKE_C_FLAGS_MSAN
    "${CMAKE_C_FLAGS} -fsanitize=memory -fno-optimize-sibling-calls -fsanitize-memory-track-origins=2 -fno-omit-frame-pointer -g"
    CACHE STRING "Flags used by the C compiler during MemorySanitizer builds."
    FORCE)

# UndefinedBehaviour
set(CMAKE_C_FLAGS_UBSAN
    "${CMAKE_C_FLAGS} -fsanitize=undefined"
    CACHE STRING "Flags used by the C compiler during UndefinedBehaviourSanitizer builds."
    FORCE)

include_directories(include)

list(APPEND EXTRA_SRC
        include/banned.h
        include/hamurabi.h
        )


list(APPEND HAMURABI_SRC
        src/hamurabi.c
        )

add_executable(hamurabi
         src/main.c
         ${HAMURABI_SRC}
         ${EXTRA_SRC}
        )

if (NOT DISABLE_TESTS)
find_package(Check REQUIRED)

enable_testing()
include(CheckTest)
set(LIBS
        ${CHECK_LIBRARIES}
)

CHECK_TEST(check_hamurabi LIBS ${LIBS} SRC ${HAMURABI_SRC} test/check_hamurabi.c DEPS hamurabi)
endif()
