#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define arr_len(x) (sizeof(x)/sizeof(x[0]))

char* asm_to_hex(char *inst)
{
    if (strcmp(inst, "DBG") == 0) return "0x99";
    if (strcmp(inst, "NOP") == 0) return "0x0";
    if (strcmp(inst, "HLT") == 0) return "0x1";
    if (strcmp(inst, "LDA") == 0) return "0x2";
    if (strcmp(inst, "LDB") == 0) return "0x3";
    if (strcmp(inst, "ADD") == 0) return "0x4";
    if (strcmp(inst, "SUB") == 0) return "0x5";
    if (strcmp(inst, "MUL") == 0) return "0x6";
    if (strcmp(inst, "DIV") == 0) return "0x7";
    if (strcmp(inst, "MOV") == 0) return "0x8";
    if (strcmp(inst, "JMP") == 0) return "0x9";
    if (strcmp(inst, "PRNT") == 0) return "0xA";
    if (strcmp(inst, "CMP") == 0) return "0xB";
    if (strcmp(inst, "JC") == 0) return "0xC";
    if (strcmp(inst, "JZ") == 0) return "0xD";

    return inst;
}


int main(int argc, char *argv[])
{
    char *input_file;
    char *output_file;
    char *buffer = 0;
    char *tokens;
    long length;

    if (argc < 2) {
        printf("Input filename required.\n");
    }
    input_file = argv[1];

    if (argc > 2) {
        output_file = argv[2];
    } else {
        output_file = "prog.bin";
    }

    // open and read ASM file
    FILE *f = fopen(input_file, "rb");
    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer)
        {
            fread(buffer, 1, length, f);
        }
        fclose(f);
    }

    // tokenize
    if (buffer) {
        // https://www.cplusplus.com/reference/cstring/strtok/
        tokens = strtok(buffer, " \n");

        while (tokens != NULL) {
            printf("%s ", asm_to_hex(tokens));
            tokens = strtok(NULL, " \n");
        }
    }

    printf("\n");
}
