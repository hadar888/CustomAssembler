#ifndef CUSTOMASSEMBLER_CONSTANTS_H
#define CUSTOMASSEMBLER_CONSTANTS_H

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
    HLT
} AssemblyInstructions;

#endif
