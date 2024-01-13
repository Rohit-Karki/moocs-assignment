#include <stdio.h>
#include <stdint.h>
#include <signal.h>
/* unix only */
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>

#define MEMORY_MAX (1 << 16)
uint16_t memory[MEMORY_MAX]; /* 65536 locations */

// Registers
enum
{
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC, /* program counter */
    R_COND,
    R_COUNT = 10
};

uint16_t reg[R_COUNT];

// Condition Flags
enum
{
    FL_POS = 1 << 0, /* P */
    FL_ZRO = 1 << 1, /* Z */
    FL_NEG = 1 << 2, /* N */
};

// OPCODE operations
enum
{
    OP_BR = 0, /* branch */
    OP_ADD,    /* add  */
    OP_LD,     /* load */
    OP_ST,     /* store */
    OP_JSR,    /* jump register */
    OP_AND,    /* bitwise and */
    OP_LDR,    /* load register */
    OP_STR,    /* store register */
    OP_RTI,    /* unused */
    OP_NOT,    /* bitwise not */
    OP_LDI,    /* load indirect */
    OP_STI,    /* store indirect */
    OP_JMP,    /* jump */
    OP_RES,    /* reserved (unused) */
    OP_LEA,    /* load effective address */
    OP_TRAP    /* execute trap */
};

// Memory Referenced Registers
enum
{
    MR_KBSR = 0xFE00, /* keyboard status */
    MR_KBDR = 0xFE02, /* keyboard Data */
};

// Update the condition flags
uint16_t sign_extent(uint16_t r)
{
    if (reg[r] == 0)
    {
        reg[R_COND] = FL_ZRO
    }
    else if (reg[r] >> 15)
    {
        // 15 bit in the number is sign bit
        reg[R_COND] = FL_NEG
    }
    else
    {
        reg[R_COND] = FL_POS;
    }
}

uint16_t swap16(uint16_t x)
{
    return (x << 8) | (x >> 8);
}

// Here is the code for reading an LC-3 program into memory:
void read_image_file(FILE *file)
{
    // where to write the image in the memory
    uint16_t origin;
    fread(&origin, sizeof(origin), 1, file);
    // Swap16 converts the big endian to little endian since big endian is used in lc-3
    origin = swap16(origin);

    uint16_t max_read = MEMORY_MAX - origin;
    uint16_t *p = memory + origin;
    size_t read = fread(p, sizeof(uint16_t), max_read, file);

    /* swap to little endian */
    while (read-- > 0)
    {
        *p = swap16(*p);
        ++p;
    }
}

int readFile(const char *filePath)
{
    FILE *file = fopen(filePath, "rb");
    if (!file)
        return 0;
    read_image_file(file);
}

uint16_t mem_read(uint16_t addr)
{
    if (addr == MR_KBSR)
    {
        if (check_key())
        {
            memory[MR_KBSR] = (1 << 15);
            memory[MR_KBDR] = getChar();
        }
        else
        {
            memory[MR_KBSR] = 0;
        }
    }
    return memory[addr];
}

// Main Program
int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        /* show usage string */
        printf("lc3 [image-file1] ...\n");
        exit(2);
    }

    for (int j = 1; j < argc; ++j)
    {
        if (!read_image(argv[j]))
        {
            printf("failed to load image: %s\n", argv[j]);
            exit(1);
        }
    }

    // Set the default condition flag Z flag to 0
    reg[R_COND] = FL_ZRO;

    // Set the PC to the default value which is the 0x3000
    enum
    {
        PC_START = 0x3000,
    };
    reg[R_PC] = PC_START;

    int running = 1;
    while (running)
    {
        /*
       Fetch the instruction from the PC location
       OPCODE is in 12-15 so Right Shift upto 12 will make the instr only have the opcode and all other bits set to 0
        */
        uint16_t instr = mem_read[reg[R_PC]++];
        uint16_t opcode = instr >> 12;

        switch (OPCODE)
        {
        case OP_ADD:
        {
            // Add Instructions
            /* destination register (DR) */
            uint16_t r0 = (instr >> 9) & 0x7;
            /* first operand (SR1) */
            uint16_t r1 = (instr >> 6) & 0x7;
            /* whether we are in immediate mode */
            uint16_t imm_flag = (instr >> 5) & 0x1;

            if (imm_flag)
            {
                uint16_t imm5 = sign_extend(instr & 0x1F, 5);
                reg[r0] = reg[r1] + imm5;
            }
            else
            {
                uint16_t r2 = instr & 0x7;
                reg[r0] = reg[r1] + reg[r2];
            }

            update_flags(r0);
        }
        case OP_AND:
        {
            uint16_t r0 = (instr >> 9) & 0x7;
            /* first operand (SR1) */
            uint16_t r1 = (instr >> 6) & 0x7;
            /* whether we are in immediate mode */
            uint16_t imm_flag = (instr >> 5) & 0x1;

            if (imm_flag)
            {
                uint16_t imm5 = sign_extend(instr & 0x1F, 5);
                reg[r0] = reg[r1] && imm5;
            }
            else
            {
                uint16_t r2 = instr & 0x7;
                reg[r0] = reg[r1] && reg[r2];
            }

            update_flags(r0);
        }
        /* LDI Load Indirect */
        case OP_LDI:
        {
            // Destination register
            uint16_t r0 = (instr >> 9) & 0x7;
            /* Address field of LDI */
            uint16_t addr = reg[R_PC] + (instr >> 6) & 0x7;
            addr = sign_extent(addr, 7);
            uint16_t nextaddr = mem_read[addr];
            r0 = mem_read[nextaddr];
            update_flags(r0);
        }
        }
    }
}
