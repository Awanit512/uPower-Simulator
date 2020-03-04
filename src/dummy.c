#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>
#include<math.h>
#include<string.h>

#include "../include/uPowerSim.h"
#include "../include/simulator.h"

int bin_to_int(char* bin)
{
    int ans=0;
    int l=strlen(bin),i;
    for(i=l-1;i>=0;i--)
    {
        if(bin[i]=='1')
            ans+=pow(2,l-1-i);
    }
    return ans;
}

void x_check(char *bin_instr)
{
    int RS, RA, RB, Rc, PO, XO;
    char sRS[6], sRA[6], sRB[6], sRc[2];
    char sPO[7], sXO[11];
    int i;
    for(i=0;i<32;i++)
    {
        if(i<6)
            sPO[i] = bin_instr[i];
        if(i==6)
            sPO[6] = '\0';

        if(i>=6 && i<11)
            sRS[i-6] = bin_instr[i];
        if(i==11)
            sRS[5] = '\0';

        if(i>=11 && i<16)
            sRA[i-11] = bin_instr[i];
        if(i==16)
            sRA[5] = '\0';

        if(i>=16 && i<21)
            sRB[i-16] = bin_instr[i];
        if(i==21)
            sRB[5] = '\0';

        if(i>=21 && i<31)
            sXO[i-21] = bin_instr[i];
        if(i==31)
            sXO[10] = '\0';

        if(i==31)
            sRc[0] = bin_instr[i];
        sRc[1] = '\0';
    }

    PO = bin_to_int(sPO);
    RS = bin_to_int(sRS);
    RA = bin_to_int(sRA);
    RB = bin_to_int(sRB);
    XO = bin_to_int(sXO);
    Rc = bin_to_int(sRc);

    // NAND
    if(PO == 31 && XO == 476)
    {
        R[RS] = ~(R[RA] & R[RB]);
    }

    // OR
    if(PO == 31 && XO == 444)
    {
        R[RS] = R[RA] | R[RB];
    }

    // AND
    if(PO == 31 && XO == 28)
    {
        R[RS] = R[RA] & R[RB];
    }

    // XOR
    if(PO == 31 && XO == 316)
    {
        R[RS] = R[RA] ^ R[RB];
    }
}

int main()
{
    R[2]=0;
    R[3]=16;
    char* test= (char*)malloc(sizeof(char)*35);
    test="01111100100000100001101001111000 X";
    x_check(test);
    printf("%ld",R[4]);
}