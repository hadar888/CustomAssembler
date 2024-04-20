#include "macro.h"

int main()
{
    char code[] = ".define sz = 2\n"
                   "MAIN: mov r3, LIST[sz]\n"
                   "LOOP: jmp L1\n"
                   "mcr m_mcr\n"
                   "cmp r3, #sz\n"
                   " bne END\n"
                   "endmcr\n"
                   " prn #-5\n"
                   " mov STR[5], STR[2]\n"
                   " sub r1, r4\n"
                   "m_mcr\n"
                   "L1: inc K\n"
                   " bne LOOP\n"
                   "END: hlt\n"
                   ".define len = 4\n"
                   "STR: .string “abcdef”\n"
                   "LIST: .data 6, -9, len\n"
                   "K: .data 22";

    MacroHandler(code);

    return 0;
}
