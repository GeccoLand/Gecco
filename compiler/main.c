//
// Created by wylan on 12/19/24.
//

#include <stdio.h>
#include <stdlib.h>

#include "vm.h"
#include "command/command_defs.h"
#include "err/status.h"
#include "formatting/ansi_colors.h"

/**
 * Run -> Evaluate -> Print -> Loop.
 */
static void repl() {
    char line[1024];

    printf(BOLD "                    🔁 Gecco REPL 🔁\n" RESET);
    printf("This is the command line REPL (read-eval-print-loop) for" BOLD " Gecco" RESET ". \n"
        "You can run any code in the terminal and it will run as if \nit is part of a" BOLD " .gec" RESET " file."
        " All code is ran through the interpreter.\n");

    for (;;) {
        printf(BOLD "\n> " RESET);

        if (!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }

        interpret(line);
    }
}

/**
 * Allocates a file into the memory of the computer.
 * @param path The path of the file
 * @return a character array
 */
static char *readFile(const char *path) {
    FILE *file = fopen(path, "rb");

    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(FILE_NOT_FOUND);
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char *buffer = malloc(fileSize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
        exit(OUT_OF_MEMORY);
    }

    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    if (bytesRead < fileSize) {
        fprintf(stderr, "Could not read file \"%s\".\n", path);
        exit(FILE_NOT_READABLE);
    }

    buffer[bytesRead] = '\0';

    fclose(file);
    return buffer;
}

/**
 * Executes a .gec file.
 * @param path The file path of the runnable
 */
static void runFile(const char *path) {
    char *source = readFile(path);
    InterpretResult result = interpret(source);
    free(source); // [owner]

    if (result == INTERPRET_COMPILE_ERROR) exit(COMPILER_ERROR);
    if (result == INTERPRET_RUNTIME_ERROR) exit(RUNTIME_ERROR);
}

/**
 * The main entry point for Gecco. This starts the program.
 * @param argc Arguments length
 * @param argv Each appended argument
 * @return 0 if the program was a success
 */
int main(const int argc, const char *argv[]) {
    initVM();

    if (argc == 1) {
        repl();
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        fprintf(stderr, "Usage: gecco [path]\n");
        list_commands();
        exit(EXIT_FAILURE_MINOR);
    }

    freeVM();
    return EXIT_SUCCESS;
}
