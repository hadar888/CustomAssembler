#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sentence_parser.h"

void printParsedSentence(const ParsedSentence *parsedSentence) {
    int i;
    printf("Label: %s\n", parsedSentence->label);

    printf("Instruction Type: %d\n", parsedSentence->instruction_type);
    printf("Instruction: %d\n", parsedSentence->instruction);

    printf("Parameter Count: %d\n", parsedSentence->param_count);
    printf("Parameters:\n");
    for (i = 0; i < parsedSentence->param_count; i++) {
        printf("- %s\n", parsedSentence->params[i]);
    }
}


char *extract_label(char *sentence) {
    char *ptr = sentence;
    char *label = NULL;
    char *end = NULL;

    /* Skip leading spaces */
    while (isspace(*ptr)) {
        ptr++;
    }

    /* Check if the first non-space character is a letter (label criteria) */
    if (!isalpha(*ptr)) {
        return NULL;
    }

    /* Find the end of the label */
    end = ptr;
    while (*end != '\0' && (isalnum(*end) || *end == '_')) {
        end++;
    }

    /* Check if the label ends with ':' */
    if (*end == ':' && end - ptr <= LABEL_MAX_LENGTH - 1) {
        /* Allocate memory for the label and copy it */
        label = malloc(end - ptr + 1); /* Add 1 for null terminator */
        if (label == NULL) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            return NULL;
        }
        strncpy(label, ptr, end - ptr);
        label[end - ptr] = '\0'; /* Null-terminate the label */
    }

    return label;
}

int is_ignore_line(char *line) {
    /* Skip leading spaces and tabs */
    while (*line != '\0' && (*line == ' ' || *line == '\t')) {
        line++;
    }

    /* Check if the line starts with a ';' */
    if (*line == ';') {
        return 1; /* Line starts with a ';', treated as a blank line */
    }

    /* Check if the line consists only of whitespace characters */
    while (*line != '\0') {
        if (!isspace(*line)) {
            return 0; /* Not a blank line */
        }
        line++; /* Move to the next character */
    }

    return 1; /* All characters are whitespace, indicating a blank line */
}

void handle_directive(const char *token, ParsedSentence *parsedSentence) {
    /*TODO: implement each sentence*/
    if (strncmp(token, ".define", 7) == 0 && strlen(token) == 7) {
        parsedSentence->instruction_type = DEFINE;
        parsedSentence->instruction = DEFINE_INST;
        printf("Sentence starts with '.define' and token length matches.\n");
    } else if (strncmp(token, ".data", 5) == 0 && strlen(token) == 5) {
        parsedSentence->instruction = DATA_INST;
        printf("Sentence starts with '.data' and token length matches.\n");
    } else if (strncmp(token, ".string", 7) == 0 && strlen(token) == 7) {
        parsedSentence->instruction = STRING_INST;
        printf("Sentence starts with '.string' and token length matches.\n");
    } else if (strncmp(token, ".entry", 6) == 0 && strlen(token) == 6) {
        parsedSentence->instruction = ENTRY_INST;
        printf("Sentence starts with '.entry' and token length matches.\n");
    } else if (strncmp(token, ".extern", 7) == 0 && strlen(token) == 7) {
        parsedSentence->instruction = EXTERN_INST;
        printf("Sentence starts with '.extern' and token length matches.\n");
    } else {
        parsedSentence->instruction_type = INVALID;
        printf("Sentence starting with dot should be one of those: \".define\", \".data\", \".string\", \".entry\", \".extern\"\n");
    }
    if (parsedSentence->instruction_type != DEFINE) {
        parsedSentence->instruction_type = DIRECTIVE;
    }
}

void handle_commands(const char *token, ParsedSentence *parsedSentence) {
    /*TODO: implement each sentence*/
    if (strncmp(token, "mov", 3) == 0) {
        printf("Handling 'mov' instruction.\n");
        parsedSentence->instruction = MOV;
    } else if (strncmp(token, "cmp", 3) == 0) {
        printf("Handling 'cmp' instruction.\n");
        parsedSentence->instruction = CMP;
    } else if (strncmp(token, "add", 3) == 0) {
        printf("Handling 'add' instruction.\n");
        parsedSentence->instruction = ADD;
    } else if (strncmp(token, "sub", 3) == 0) {
        printf("Handling 'sub' instruction.\n");
        parsedSentence->instruction = SUB;
    } else if (strncmp(token, "not", 3) == 0) {
        printf("Handling 'not' instruction.\n");
        parsedSentence->instruction = NOT;
    } else if (strncmp(token, "clr", 3) == 0) {
        printf("Handling 'clr' instruction.\n");
        parsedSentence->instruction = CLR;
    } else if (strncmp(token, "lea", 3) == 0) {
        printf("Handling 'lea' instruction.\n");
        parsedSentence->instruction = LEA;
    } else if (strncmp(token, "inc", 3) == 0) {
        printf("Handling 'inc' instruction.\n");
        parsedSentence->instruction = INC;
    } else if (strncmp(token, "dec", 3) == 0) {
        printf("Handling 'dec' instruction.\n");
        parsedSentence->instruction = DEC;
    } else if (strncmp(token, "jmp", 3) == 0) {
        printf("Handling 'jmp' instruction.\n");
        parsedSentence->instruction = JMP;
    } else if (strncmp(token, "bne", 3) == 0) {
        printf("Handling 'bne' instruction.\n");
        parsedSentence->instruction = BNE;
    } else if (strncmp(token, "red", 3) == 0) {
        printf("Handling 'red' instruction.\n");
        parsedSentence->instruction = RED;
    } else if (strncmp(token, "prn", 3) == 0) {
        printf("Handling 'prn' instruction .\n");
        parsedSentence->instruction = PRN;
    } else if (strncmp(token, "jsr", 3) == 0) {
        printf("Handling 'jsr' instruction.\n");
        parsedSentence->instruction = JSR;
    } else if (strncmp(token, "rts", 3) == 0) {
        printf("Handling 'rts' instruction.\n");
        parsedSentence->instruction = RTS;
    } else if (strncmp(token, "hlt", 3) == 0) {
        printf("Handling 'hlt' instruction.\n");
        parsedSentence->instruction = HLT;
    } else {
        printf("Invalid way to start a sentence!\n");
        parsedSentence->instruction_type = INVALID;
    }
    if (parsedSentence->instruction_type != INVALID) {
        parsedSentence->instruction_type = COMMAND;
    }
}

ParsedSentence parse_command(char *input) {
    ParsedSentence parsedSentence;
    char *label = NULL;
    char *token = NULL;
    int token_count = 0;
    parsedSentence.param_count = 0;
    parsedSentence.label[0] = '\0'; /* this also acts as label flag - we can check if the first index of label is null terminator or not */
    parsedSentence.instruction_type = IGNORE;

    if (is_ignore_line(input)) {
        parsedSentence.instruction_type = IGNORE;
        return parsedSentence;
    }

    token = strtok(input, " \t,");
    while (token != NULL) {
        if (token_count == 0) { /* check if first word is label */
            /*TODO: understand if after a label there must be a space*/
            label = extract_label(token);
            if(label != NULL) {
                /* TODO: check if label is in label list and handle for true or false*/
                strcpy(parsedSentence.label, label); /*TODO: remove line! - now I assume that every label is valid for simplification*/
                input += strlen(parsedSentence.label) + 1;
                free(label);
                token = strtok(NULL, " \t,");
                token_count++;
                continue;
            } else {
                printf("No label found.\n");
            }
        }
        if ((token_count == 0 && parsedSentence.label[0] == '\0') || (token_count == 1 && parsedSentence.label[0] != '\0')){ /* check if first or second word is valid command */
            if (strncmp(token, ".", 1) == 0){
                /* this means it's a directive, define or invalid instruction */
                handle_directive(token, &parsedSentence);
                if(parsedSentence.instruction_type == INVALID){
                    return parsedSentence;
                }
                token = strtok(NULL, " \t,");
                token_count++;
            }
            else if (strlen(token) == 3){
                /* this means it's a command or invalid instruction */
                handle_commands(token, &parsedSentence);
                if(parsedSentence.instruction_type == INVALID){
                    return parsedSentence;
                }
                token = strtok(NULL, " \t,");
                token_count++;
            }
            else {
                /* this means it's invalid instruction */
                parsedSentence.instruction_type = INVALID;
                return parsedSentence;
            }
        }
        else {
            /* here we handle parameters */
            /* TODO: should we handle parameters here or later? */
            if (parsedSentence.param_count >= MAX_PARAMS) {
                printf("Error: too many params!");
                return parsedSentence;
            }
            parsedSentence.params[parsedSentence.param_count] = malloc((strlen(token) + 1) * sizeof(char));
            if (parsedSentence.params[parsedSentence.param_count] == NULL) {
                fprintf(stderr, "Error: Memory allocation failed for word %s\n", token);
                exit(EXIT_FAILURE);
            }

            strncpy(parsedSentence.params[parsedSentence.param_count], token, strlen(token));
            parsedSentence.params[parsedSentence.param_count][strlen(token)] = '\0';
            parsedSentence.param_count++;
            token = strtok(NULL, " \t,");
            token_count++;
        }
    }

    return parsedSentence;
}
