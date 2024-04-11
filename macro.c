#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "macro.h"

#define MAX_LEN_MACRO_DICTIONARY 100
#define MAX_MACRO_NAME 100
#define MAX_MACRO_VALUE 3000
#define MAX_CURRENT_LINE_VALUE 1000

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

    while (codeSection[i] != '\0')
    {
        int isCurrentLineHasSpace = 0;
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
            if (codeSection[i] == ' ')
            {
                isCurrentLineHasSpace = 1;
            }
            currentLine[j] = codeSection[i];
            i++;
            j++;
        }
        currentLine[j] = '\0';
        i++;

        if (!isCurrentLineHasSpace)
        {
            int currLineMacroIndex = GetCurrLineMacroIndex(currentLine, macroDictionary, macroDictionaryLen);
            if (currLineMacroIndex != -1)
            {
                strcpy(updatedCode[k], macroDictionary[currLineMacroIndex].macroValue);
            }

            else {
                strcpy(updatedCode[k], strcat(currentLine, "\n"));
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

int GetMacroDict(char* macroSection, struct macro* macroDictionary)
{
    char mcrStr[] = "mcr ";
    char endmcrStr[] = "endmcr";
    char currentPartForMcrCheck[5] = "";
    char currentPartForEndMcrCheck[7] = "";
    int i = 0;
    int k = 0;

    while (macroSection[i] != '\0') {
        strncpy(currentPartForMcrCheck, &macroSection[i], 4);
        if (strcmp(currentPartForMcrCheck, mcrStr) == 0)
        {
            i = i + 4;

            char *macroName = NULL;
            macroName = (char *)malloc(MAX_MACRO_NAME * sizeof(char *));
            if (macroName==NULL)
            {
                printf("Error! Could not allocate");
                return -1;
            }

            char *macroValue = NULL;
            macroValue = (char *)malloc(MAX_MACRO_VALUE * sizeof(char *));
            if (macroValue==NULL)
            {
                printf("Error! Could not allocate");
                return -1;
            }

            int j = 0;
            while (macroSection[i] != '\0' && macroSection[i] != '\n') {
                macroName[j] = macroSection[i];
                j++;
                i++;
            }
            macroName[j] = '\0';
            j++;

            if (macroSection[i] == '\0' ){
                return -1;
                //invalid macro, macro has no value
            }

            i++;

            strncpy(macroDictionary[k].macroName, macroName, j);

            j = 0;
            while (macroSection[i] != '\0' && strcmp(currentPartForEndMcrCheck, endmcrStr) != 0) {
                macroValue[j] = macroSection[i];
                j++;
                i++;
                strncpy(currentPartForEndMcrCheck, &macroSection[i], 6);
            }
            macroValue[j] = '\0';
            j++;
            strcpy(currentPartForEndMcrCheck, "");

            if (macroSection[i] == '\0' ){
                return -1;
                //invalid macro, macro has no endmcr
            }

            i = i + 6;

            strncpy(macroDictionary[k].macroValue, macroValue, j);
            k++;
            if (macroSection[i] == '\n' ) {
                i++;
            }

            free(macroName);
            free(macroValue);
        }
        else {
            i++;
        }
        strcpy(currentPartForMcrCheck, "");
    }

    return k;
}

int MacroHandler(char* macroSection, char* codeSection, char** updatedCode)
{
    struct macro* macroDictionary = NULL;

    macroDictionary = (struct macro*)malloc(MAX_LEN_MACRO_DICTIONARY * sizeof(struct macro));
    if (macroDictionary == NULL)
    {
        printf("Error! Could not allocate");
        return -1;
    }

    int i=0;
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

    int macroDictionaryLen = GetMacroDict(macroSection, macroDictionary);
    int updatedCodeLen = MacroReplace(macroDictionary, codeSection, macroDictionaryLen, updatedCode);

    return updatedCodeLen;
}
