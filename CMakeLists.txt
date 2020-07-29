cmake_minimum_required(VERSION 3.17)

project(hamurabi VERSION 0.1
        DESCRIPTION "Hamurabi - a text adventure game written in C99"
            LANGUAGES C ASM
        )

option(DISABLE_TESTS "If tests should be compiled or not" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# C11 minimum
set(CMAKE_C_STANDARD 11)
# Show all warning messages
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

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

find_package(Check REQUIRED)

enable_testing()
include(CheckTest)
set(LIBS
        ${CHECK_LIBRARIES}
)

CHECK_TEST(check_hamurabi LIBS ${LIBS} SRC ${HAMURABI_SRC} test/check_hamurabi.c DEPS hamurabi)
