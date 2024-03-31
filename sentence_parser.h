#ifndef SENTENCE_PARSER_H
#define SENTENCE_PARSER_H


#define MAX_PARAMS 38 /* maximum number of parameters - calculated when .data get the maximum amount of params and sentence length is 80 */

#define LABEL_MAX_LENGTH 32
#define COMMAND_MAX_LENGTH 20

typedef enum {
    DIRECTIVE = 0,
    COMMAND,
    DEFINE,
    IGNORE, /* comment or blank line */
    INVALID
} SentenceType;

typedef enum {
    MOV = 0,
    CMP,
    ADD,
    SUB,
    NOT,
    CLR,
    LEA,
    INC,
    DEC,
    JMP,
    BNE,
    RED,
    PRN,
    JSR,
    RTS,
    HLT,
    DEFINE_INST,
    DATA_INST,
    STRING_INST,
    ENTRY_INST,
    EXTERN_INST
} AssemblyInstructions;

/* struct to hold command and parameters for commands */
typedef struct {
    char label[LABEL_MAX_LENGTH]; /*label - can be empty*/
    SentenceType instruction_type; /* the command type*/
    AssemblyInstructions instruction; /* the command itself */
    char *params[MAX_PARAMS]; /* params represented as strings - each parameter will be treated according to instruction*/
    int param_count; /* count amount of params */
} ParsedSentence;

ParsedSentence parse_command(char *input);
char *extract_label(char *sentence_start);
void printParsedSentence(const ParsedSentence *parsedSentence);

#endif /* SENTENCE_PARSER_H */
