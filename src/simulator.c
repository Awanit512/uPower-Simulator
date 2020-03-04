#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>
#include<math.h>
#include<string.h>

#include "../include/uPowerSim.h"
#include "../include/simulator.h"

int i;

void initialize()
{
    CIA = 0;
    NIA = 1;
    int displacement;
    read_bin();
    while(CIA != n_instr)
    {
        displacement = 1;
        if(strcmp(bin_lines[CIA].type, "X")==0)
        {
            instr_typ_x(bin_lines[CIA].instr);
        }

        if(strcmp(bin_lines[CIA].type, "XO")==0)
        {
            instr_typ_xo(bin_lines[CIA].instr);
        }

        if(strcmp(bin_lines[CIA].type, "D")==0)
        {
            instr_typ_d(bin_lines[CIA].instr);
        }

        if(strcmp(bin_lines[CIA].type, "B")==0)
        {
            displacement = instr_typ_b(bin_lines[CIA].instr);
        }

        if(strcmp(bin_lines[CIA].type, "DS")==0)
        {
            instr_typ_ds(bin_lines[CIA].instr);
        }

        CIA += displacement;
    }
}

void read_bin()
{
    int i = 0;
    int j, k;
    char *buffer = NULL;
    size_t size = 0;
    char ins[100], typ[100];
    while(getline(&buffer, &size, bin_file) != -1)
	{
        j=0;
        while(buffer[j] != ' ')
        {
            ins[j] = buffer[j];
            j++;
        }
        ins[j] = '\0';

        k=0;
        j++;
        while(buffer[j] != '\0' && buffer[j] != '\r' && buffer[j] != '\n')
        {
            typ[k] = buffer[j];
            k++;
            j++;
        }
        typ[k] = '\0';
        strcpy(bin_lines[i].instr, ins);
        strcpy(bin_lines[i].type, typ);
        i++;
	}
}
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

void instr_typ_x(char *bin_instr)
{
    char sRS[6], sRA[6], sRB[6], sRc[2];
    int RS, RA, RB, Rc, PO, XO;
    char sPO[7], sXO[11];
    for(i=0;i<32;i++)
    {
        if(i<6)
            sPO[i] = bin_instr[i];
        if(i==6)
            sPO[i] = '\0';

        if(i>=6 && i<11)
            sRS[i-6] = bin_instr[i];
        if(i==11)
            sRS[i-6] = '\0';

        if(i>=11 && i<16)
            sRA[i-11] = bin_instr[i];
        if(i==16)
            sRA[i-11] = '\0';

        if(i>=16 && i<21)
            sRB[i-16] = bin_instr[i];
        if(i==21)
            sRB[i-16] = '\0';

        if(i>=21 && i<31)
            sXO[i-21] = bin_instr[i];
        if(i==31)
            sXO[i-21] = '\0';

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
        R[RA] = ~(R[RS] & R[RB]);
    }

    // OR
    if(PO == 31 && XO == 444)
    {
        R[RA] = R[RS] | R[RB];
    }

    // AND
    if(PO == 31 && XO == 28)
    {
        R[RA] = R[RS] & R[RB];
    }

    // XOR
    if(PO == 31 && XO == 316)
    {
        R[RA] = R[RS] ^ R[RB];
    }
}

void instr_typ_xo(char *bin_instr)
{
    char sRT[6], sRA[6], sRB[6], sRc[2], sOE[2];
    int RT, RA, RB, Rc, PO, XO, OE;
    char sPO[7], sXO[10];
    for(i=0;i<32;i++)
    {
        if(i<6)
            sPO[i] = bin_instr[i];
        if(i==6)
            sPO[i] = '\0';

        if(i>=6 && i<11)
            sRT[i-6] = bin_instr[i];
        if(i==11)
            sRT[i-6] = '\0';

        if(i>=11 && i<16)
            sRA[i-11] = bin_instr[i];
        if(i==16)
            sRA[i-11] = '\0';

        if(i>=16 && i<21)
            sRB[i-16] = bin_instr[i];
        if(i==21)
            sRB[i-16] = '\0';

        if(i==21)
            sOE[0] = bin_instr[i];
        sOE[1] = '\0';

        if(i>=22 && i<31)
            sXO[i-22] = bin_instr[i];
        if(i==31)
            sXO[i-22] = '\0';

        if(i==31)
            sRc[0] = bin_instr[i];
        sRc[1] = '\0';
    }

    PO = bin_to_int(sPO);
    RT = bin_to_int(sRT);
    RA = bin_to_int(sRA);
    RB = bin_to_int(sRB);
    OE = bin_to_int(sOE);
    XO = bin_to_int(sXO);
    Rc = bin_to_int(sRc);

    // Add
    if(PO == 31 && OE == 0 && Rc == 0 && XO == 266)
    {
        R[RT] = R[RA] + R[RB];
    }

    // Subtract
    if(PO == 31 && OE == 0 && Rc == 0 && XO == 40)
    {
        R[RT] = R[RB] - R[RA];
    }
}

void instr_typ_d(char *bin_instr)
{
    char sRT[6], sRA[6], sSI[17];
    int RT, RA, SI, PO;
    char sPO[7];
    for(i=0;i<32;i++)
    {
        if(i<6)
            sPO[i] = bin_instr[i];
        if(i==6)
            sPO[i] = '\0';

        if(i>=6 && i<11)
            sRT[i-6] = bin_instr[i];
        if(i==11)
            sRT[i-6] = '\0';

        if(i>=11 && i<16)
            sRA[i-11] = bin_instr[i];
        if(i==16)
            sRA[i-11] = '\0';

        if(i>=16 && i<=31)
            sSI[i-16] = bin_instr[i];
    }
    if(i==32)
        sSI[i-16] = '\0';

    PO = bin_to_int(sPO);
    RT = bin_to_int(sRT);
    RA = bin_to_int(sRA);
    SI = bin_to_int(sSI);

    // Add immediate
    if(PO == 14)
    {
        R[RT] = R[RA] + SI;
    }
}

int instr_typ_b(char *bin_instr)
{
    char sPO[7], sBO[6], sBI[6], sBD[15], sAA[2], sLK[2];
    int PO, BO, BI, BD, AA, LK;
    for(i=0;i<32;i++)
    {
        if(i<6)
            sPO[i] = bin_instr[i];
        if(i==6)
            sPO[i] = '\0';

        if(i>=6 && i<11)
            sBO[i-6] = bin_instr[i];
        if(i==11)
            sBO[i-6] = '\0';

        if(i>=11 && i<16)
            sBI[i-11] = bin_instr[i];
        if(i==16)
            sBI[i-11] = '\0';

        if(i>=16 && i<30)
            sBD[i-16] = bin_instr[i];
        if(i==30)
            sBD[i-16] = '\0';
        
        if(i==30)
            sAA[0] = bin_instr[i];
        sAA[1] = '\0';

        if(i==31)
            sLK[0] = bin_instr[i];
        sLK[1] = '\0';
    }

    PO = bin_to_int(sPO);
    BO = bin_to_int(sBO);
    BI = bin_to_int(sBI);
    BD = bin_to_int(sBD);
    AA = bin_to_int(sAA);
    LK = bin_to_int(sLK);

    if(PO == 19 && AA == 0 && LK == 0)
    {
        if(R[BO] == R[BI])
        {
            return BD;
        }
    }
}

void instr_typ_ds(char *bin_instr)
{
    char sRT[6], sRA[6], sDS[15], sXO[3];
    int RT, RA, DS, PO, XO;
    char sPO[7];
    for(i=0;i<32;i++)
    {
        if(i<6)
            sPO[i] = bin_instr[i];
        if(i==6)
            sPO[i] = '\0';

        if(i>=6 && i<11)
            sRT[i-6] = bin_instr[i];
        if(i==11)
            sRT[i-6] = '\0';

        if(i>=11 && i<16)
            sRA[i-11] = bin_instr[i];
        if(i==16)
            sRA[i-11] = '\0';

        if(i>=16 && i<30)
            sDS[i-16] = bin_instr[i];
        if(i==30)
            sDS[i-16] = '\0';

        if(i==30)
        {
            sXO[0] = bin_instr[i];
            sXO[1] = bin_instr[i+1];
            sXO[2] = '\0';
            break;
        }
    }

    PO = bin_to_int(sPO);
    RT = bin_to_int(sRT);
    RA = bin_to_int(sRA);
    DS = bin_to_int(sDS);
    XO = bin_to_int(sXO);

    // Load doubleword
    if(PO == 58 && XO == 0)
    {
        int ctr = 0;
        struct symbol_table_data *temp;
        temp = sym_tab_data_head;
        int target_address = R[RA] + DS;
        while(temp != NULL)
        {
            if(ctr == target_address)
            {
                int32_t low, high;
                sscanf(temp->data, "%"PRId32"", &low);
                temp=temp->next;
                sscanf(temp->data, "%"PRId32"", &high);
                R[RT] = ((int64_t)high) << 32 | low;
            }
            ctr++;
            temp = temp->next;
        }
    }

    if(PO == 62 && XO == 0)
    {
        int ctr = 0;
        char highstr[20], lowstr[20];
        struct symbol_table_data *temp;
        temp = sym_tab_data_head;
        int target_address = R[RA] + DS;
        while(temp != NULL)
        {
            if(ctr == target_address - 1)
            {
                struct symbol_table_data *s_temp1, *s_temp2;
				s_temp1 = (struct symbol_table_data *)malloc(sizeof(struct symbol_table_data));
                s_temp2 = (struct symbol_table_data *)malloc(sizeof(struct symbol_table_data));
                s_temp1->label = NULL;
                s_temp1->type = NULL;
                s_temp2->label = NULL;
                s_temp2->type = NULL;
                int32_t high, low;
                high = (int32_t)((R[RS] & 0xFFFFFFFF00000000LL) >> 32);
                low = (int32_t)(R[RS] & 0xFFFFFFFFLL);
                sprintf(highstr, "%"PRId32"", high);
                sprintf(lowstr, "%"PRId32"", low);
                s_temp1->data = highstr;
                s_temp2->data = lowstr;
                s_temp2->next = s_temp1;
                s_temp1->next = temp->next;
                temp->next = s_temp2;
            }
            ctr++;
            temp = temp->next;
        }
    }
}