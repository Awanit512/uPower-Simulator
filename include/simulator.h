#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>

// Registers
int64_t R[32];
int64_t LR, CIA, NIA, SRR0;
int32_t CR;

// Binary instruction array
struct bin_line
{
    char instr[100];
    char type[10];
};

struct bin_line bin_lines[100];

// Functions
void initialize();
void read_bin();
void instr_typ_x(char *bin_instr);
void instr_typ_xo(char *bin_instr);
void instr_typ_d(char *bin_instr);
int instr_typ_b(char *bin_instr);
void instr_typ_ds(char *bin_instr);