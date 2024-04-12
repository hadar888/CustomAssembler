#ifndef MAMAN14_MACRO_H
#define MAMAN14_MACRO_H
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN_MACRO_DICTIONARY 100
#define MAX_MACRO_NAME 100
#define MAX_MACRO_VALUE 3000
#define MAX_CURRENT_LINE_VALUE 1000

struct macro {
    char* macroName;
    char* macroValue;
};

int GetCurrLineMacroIndex(char* currentLine, struct macro* macroDictionary, int macroDictionaryLen);
int MacroReplace(struct macro* macroDictionary, const char* codeSection, int macroDictionaryLen, char** updatedCode);
int GetMacroDict(char* macroSection, struct macro* macroDictionary);
int MacroHandler(char* macroSection, char* codeSection, char** updatedCode);

#endif
