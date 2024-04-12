#include<stdio.h>
#include<stdlib.h>
#include "macro.h"

#define UPDATED_CODE_LEN 10000
#define MAX_CURRENT_LINE_VALUE 1000

int main()
{
    char codeSection[] = "Donec posuere\nmacro1\narcu in gravida cursus, augue\nmacro2\nquam mattis sem";
    char macroSection[] = "mcr macro1\nvalue1\nendmcr\nmcr macro2\nvalue2\nendmcr";
    char** updatedCode = NULL;
    int i = 0;
    int lenUpdatedCode;

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

    lenUpdatedCode = MacroHandler(macroSection, codeSection, updatedCode);

    for (i = 0; i < lenUpdatedCode; ++i) {
        printf("%s", updatedCode[i]);
    }

    return 0;
}
