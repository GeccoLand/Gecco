cmake_minimum_required(VERSION 3.30)
project(Gecco C)

set(CMAKE_C_STANDARD 23)

add_executable(Gecco
        compiler/chunk/chunk.c
        compiler/chunk/chunk.h
        compiler/common.h
        compiler/compiler/compiler.c
        compiler/compiler/compiler.h
        compiler/debug/debug.c
        compiler/debug/debug.h
        compiler/main.c
        compiler/memory.c
        compiler/memory.h
        compiler/object.c
        compiler/object.h
        compiler/scanner.c
        compiler/scanner.h
        compiler/table.c
        compiler/table.h
        compiler/value.c
        compiler/value.h
        compiler/vm.c
        compiler/vm.h
        compiler/command/version.c
        compiler/command/command_defs.h
        compiler/command/command_defs.c
        compiler/formatting/ansi_colors.h
        compiler/err/status.h
)
