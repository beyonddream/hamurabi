cmake_minimum_required(VERSION 3.17)

project(hamurabi VERSION 0.1
        DESCRIPTION "Hamurabi - a text adventure game written in C99"
            LANGUAGES C ASM
        )

list(APPEND EXTRA_SRC
        include/banned.h
        include/hamurabi.h
        )

add_executable(hamurabi
        src/main.c
        src/hamurabi.c
        ${EXTRA_SRC}
        )
