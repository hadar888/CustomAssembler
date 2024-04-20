#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "macro.h"

#define MAX_LEN_MACRO_DICTIONARY 100
#define MAX_MACRO_NAME 100
#define MAX_MACRO_VALUE 3000
#define MAX_CURRENT_LINE_VALUE 1000
#define UPDATED_CODE_LEN 10000
#define MAX_CURRENT_LINE_VALUE 1000
#define MAX_CODE_WITHOUT_MACRO 10000

char *removeStartAndEndSpaces(char *str)
{
    char *end;

    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    end[1] = '\0';
    return str;
}

void writeToAMFile(char *str[], int numStrings) {
    int i;
    FILE *amFile = fopen("amFile.am", "w");

    if (amFile == NULL) {
        printf("Error opening .am file");
        return;
    }

    for (i = 0; i < numStrings; i++) {
        fprintf(amFile, "%s\n", str[i]);
    }

    fclose(amFile);
}

int GetCurrLineMacroIndex (char* currentLine, struct macro* macroDictionary, int macroDictionaryLen)
{
    int i;
    for (i=0 ; i < macroDictionaryLen; i++) {
        if (strcmp(currentLine, macroDictionary[i].macroName) == 0)
            return i;
    }

    return -1;
}

int MacroReplace(struct macro* macroDictionary, const char* codeSection, int macroDictionaryLen, char** updatedCode)
{
    int i = 0;
    int k = 0;

    while (codeSection[i-1] != '\0')
    {
        int isCurrentLineHasSpace = 0;
        char* cleanCurrentLine = NULL;
        int j = 0;

        char* currentLine = NULL;
        currentLine = (char *)malloc(MAX_CURRENT_LINE_VALUE * sizeof(char *));
        if (currentLine == NULL)
        {
            printf("Error! Could not allocate");
            return -1;
        }

        while (codeSection[i] != '\n' && codeSection[i] != '\0')
        {
            currentLine[j] = codeSection[i];
            i++;
            j++;
        }

        currentLine[j] = '\0';

        cleanCurrentLine = removeStartAndEndSpaces(currentLine);
        if (strstr(cleanCurrentLine, " ") != NULL) {
            isCurrentLineHasSpace = 1;
        }

        i++;

        if (!isCurrentLineHasSpace)
        {
            int currLineMacroIndex = GetCurrLineMacroIndex(cleanCurrentLine, macroDictionary, macroDictionaryLen);
            if (currLineMacroIndex != -1)
            {
                strcpy(updatedCode[k], macroDictionary[currLineMacroIndex].macroValue);
            }

            else {
                strcpy(updatedCode[k], strcat(cleanCurrentLine, "\n"));
            }
        }

        else {
            strcpy(updatedCode[k], strcat(currentLine, "\n"));
        }

        k++;
        free (currentLine);
    }

    strcpy(updatedCode[k-1], "\0");
    return k;
}

int GetMacroDict(char* code, char** codeWithOutMacro, struct macro* macroDictionary)
{
    char mcrStr[] = "mcr ";
    char endmcrStr[] = "endmcr";
    char currentPartForMcrCheck[5] = "";
    char currentPartForEndMcrCheck[7] = "";
    int i = 0;
    int j;
    int k = 0;
    int z = 0;
    char *macroName;
    char *macroValue;

    while (code[i] != '\0') {
        strncpy(currentPartForMcrCheck, &code[i], 4);
        if (strcmp(currentPartForMcrCheck, mcrStr) == 0)
        {
            i = i + 4;

            macroName = NULL;
            macroName = (char *)malloc(MAX_MACRO_NAME * sizeof(char *));
            if (macroName==NULL)
            {
                printf("Error! Could not allocate");
                return -1;
            }

            macroValue = NULL;
            macroValue = (char *)malloc(MAX_MACRO_VALUE * sizeof(char *));
            if (macroValue==NULL)
            {
                printf("Error! Could not allocate");
                return -1;
            }

            j = 0;
            while (code[i] != '\0' && code[i] != '\n') {
                macroName[j] = code[i];
                j++;
                i++;
            }
            macroName[j] = '\0';
            j++;

            if (code[i] == '\0' ){
                free(macroName);
                return -1;
                /* invalid macro, macro has no value */
            }

            i++;

            strncpy(macroDictionary[k].macroName, macroName, j);

            j = 0;
            while (code[i] != '\0' && strcmp(currentPartForEndMcrCheck, endmcrStr) != 0) {
                macroValue[j] = code[i];
                j++;
                i++;
                strncpy(currentPartForEndMcrCheck, &code[i], 6);
            }
            macroValue[j] = '\0';
            j++;
            strcpy(currentPartForEndMcrCheck, "");

            if (code[i] == '\0' ){
                free(macroName);
                free(macroValue);

                return -1;
                /* invalid macro, macro has no endmcr */
            }

            i = i + 6;

            strncpy(macroDictionary[k].macroValue, macroValue, j);
            k++;
            if (code[i] == '\n' ) {
                i++;
            }

            free(macroName);
            free(macroValue);
        }
        else {
            (*codeWithOutMacro)[z] = code[i];
            i++;
            z++;
        }
        strcpy(currentPartForMcrCheck, "");
    }

    (*codeWithOutMacro)[z] = '\0';
    return k;
}

int MacroHandler(char* code)
{
    struct macro* macroDictionary = NULL;
    int i;
    int macroDictionaryLen;
    int updatedCodeLen;

    char** updatedCode = NULL;

    char* codeWithOutMacro;
    codeWithOutMacro = (char *)malloc(MAX_CODE_WITHOUT_MACRO * sizeof(char));
    if (codeWithOutMacro == NULL)
    {
        printf("Error! Could not allocate");
        return -1;
    }

    updatedCode = (char **)malloc(UPDATED_CODE_LEN * sizeof(char *));
    if (updatedCode == NULL)
    {
        printf("Error! Could not allocate");
        return -1;
    }

    for (i=0; i<UPDATED_CODE_LEN; i++)
    {
        updatedCode[i] = (char*)malloc(MAX_CURRENT_LINE_VALUE * sizeof(char));
        if (updatedCode[i] == NULL)
        {
            printf("Error! Could not allocate");
            return -1;
        }
    }

    macroDictionary = (struct macro*)malloc(MAX_LEN_MACRO_DICTIONARY * sizeof(struct macro));
    if (macroDictionary == NULL)
    {
        printf("Error! Could not allocate");
        return -1;
    }

    for (i=0; i<MAX_LEN_MACRO_DICTIONARY; i++)
    {
        macroDictionary[i].macroName = (char*)malloc(MAX_MACRO_NAME * sizeof(char));
        if (macroDictionary[i].macroName == NULL)
        {
            printf("Error! Could not allocate");
            return -1;
        }

        macroDictionary[i].macroValue = (char*)malloc(MAX_MACRO_VALUE * sizeof(char));
        if (macroDictionary[i].macroValue == NULL)
        {
            printf("Error! Could not allocate");
            return -1;
        }
    }

    macroDictionaryLen = GetMacroDict(code, &codeWithOutMacro, macroDictionary);
    updatedCodeLen = MacroReplace(macroDictionary, codeWithOutMacro, macroDictionaryLen, updatedCode);

    writeToAMFile(updatedCode, updatedCodeLen);
    free(codeWithOutMacro);
    return 0;
}
