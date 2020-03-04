#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<math.h>

#include "../include/uPowerSim.h"

int i;

char bin_enc[35]; // stores the binary encoding of the instructions

char* register_translator(char* t) // 5 bit representations of register numbers
{
    if(strcmp(t,"R1")==0)
        return "00001";
    else if(strcmp(t,"R2")==0)
        return "00010";
    else if(strcmp(t,"R3")==0)
        return "00011";
    else if(strcmp(t,"R4")==0)
        return "00100";
    else if(strcmp(t,"R5")==0)
        return "00101";
    else if(strcmp(t,"R6")==0)
        return "00110";
    else if(strcmp(t,"R7")==0)
        return "00111";
    else if(strcmp(t,"R8")==0)
        return "01000";
    else if(strcmp(t,"R9")==0)
        return "01001";
    else if(strcmp(t,"R10")==0)
        return "01010";
    else if(strcmp(t,"R11")==0)
        return "01011";
    else if(strcmp(t,"R12")==0)
        return "01100";
    else if(strcmp(t,"R13")==0)
        return "01101";            
    else if(strcmp(t,"R14")==0)
        return "01110";
    else if(strcmp(t,"R15")==0)
        return "01111";
    else if(strcmp(t,"R16")==0)
        return "10000";
    else if(strcmp(t,"R17")==0)
        return "10001";
    else if(strcmp(t,"R18")==0)
        return "10010";
    else if(strcmp(t,"R19")==0)
        return "10011";
    else if(strcmp(t,"R20")==0)
        return "10100";
    else if(strcmp(t,"R21")==0)
        return "10101";
    else if(strcmp(t,"R22")==0)
        return "10110";
    else if(strcmp(t,"R23")==0)
        return "10111";
    else if(strcmp(t,"R24")==0)
        return "11000";
    else if(strcmp(t,"R25")==0)
        return "11001";
    else if(strcmp(t,"R26")==0)
        return "11010";
    else if(strcmp(t,"R27")==0)
        return "11011";
    else if(strcmp(t,"R28")==0)
        return "11100";
    else if(strcmp(t,"R29")==0)
        return "11101";
    else if(strcmp(t,"R30")==0)
        return "11110";
    else if(strcmp(t,"R31")==0)
        return "11111";

        char* temp = instr_v[i];

        //To extract register number
        if(temp[2]=='\0')                   
            l = 1;
        else 
            l = 2;
        b=0;                         
}

/* utility function for binary encoding 
   of the registers in the instructions of X format
*/
void src_trgts_reg_translate_for_x_format(char* instr_v[])
{
    char* temp1=register_translator(instr_v[1]);
    for(i=6;i<=10;i++)
        bin_enc[i]=temp1[i-6];
    temp1=register_translator(instr_v[2]);
    for(i=11;i<=15;i++)
        bin_enc[i]=temp1[i-11];
    
    if(strcmp(instr_v[0],"extsw")!=0)
    {
        temp1=register_translator(instr_v[3]);
        for(i=16;i<=20;i++)
            bin_enc[i]=temp1[i-16];
    }

    else
    {
        for(i=16;i<=20;i++)
            bin_enc[i]='0';
    }   
}

char* and(int instr_c, char *instr_v[])
{
    // PO  011111
    bin_enc[0]='0';
    for(i=1;i<=5;i++)
    {
        bin_enc[i]='1';
    }

    // XO  0000011100
    for(i=21;i<=25;i++)
    {
        bin_enc[i]='0';
    }
    for(i=26;i<=28;i++)
    {
        bin_enc[i]='1';
    }
    bin_enc[29]='0';
    bin_enc[30]='0';

    // Rc
    bin_enc[31]='0';

    // RS RA RB
    src_trgts_reg_translate_for_x_format(instr_v);

    bin_enc[32] = ' ';
    bin_enc[33] = 'X';
    bin_enc[34] = '\0';

    return bin_enc;
}

char* nand(int instr_c, char *instr_v[])
{
    // PO 011111 sym_tab_text_head = NULL; sym_tab_text_head = NULL;


   bin_enc[0]='0';
   for(i=1;i<=5;i++)
   {
       bin_enc[i]='1';
   }

    // XO   0111011100
    bin_enc[21]='0';
    for(i=22;i<=24;i++)
    {
        bin_enc[i]='1';
    }
    bin_enc[25]='0';
    for(i=26;i<=28;i++)
    {
        bin_enc[i]='1';
    }
    bin_enc[29]='0';
    bin_enc[30]='0';

    // Rc
    bin_enc[31]='0';

    // RS RA RB
    src_trgts_reg_translate_for_x_format(instr_v);

    bin_enc[32] = ' ';
    bin_enc[33] = 'X';
    bin_enc[34] = '\0';

    return bin_enc;
}

char* or(int instr_c, char *instr_v[])
{
    // PO 011111
    bin_enc[0]='0';
    for(i=1;i<=5;i++)
    {
        bin_enc[i]='1';
    }

    // XO 0110111100
    bin_enc[21]='0';
    bin_enc[22]='1';
    bin_enc[23]='1';
    bin_enc[24]='0';
    for(i=25;i<=28;i++)
    {
        bin_enc[i]='1';
    }
    bin_enc[29]='0';
    bin_enc[30]='0';

    // Rc
    bin_enc[31]='0';

    // RS RA RB
     src_trgts_reg_translate_for_x_format(instr_v);

    bin_enc[32] = ' ';
    bin_enc[33] = 'X';
    bin_enc[34] = '\0';

    return bin_enc;
}

char* xor(int instr_c, char *instr_v[])
{
    // PO 011111
    bin_enc[0]='0';
    for(i=1;i<=5;i++)
    {
        bin_enc[i]='1';
    }

    // XO 0100111100
    bin_enc[21]='0';
    bin_enc[22]='1';
    bin_enc[23]='0';
    bin_enc[24]='0';
    for(i=25;i<=28;i++)
    {
        bin_enc[i]='1';
    }
    bin_enc[29]='0';
    bin_enc[30]='0';

    // Rc
    bin_enc[31]='0';

    // RS RA RB
    src_trgts_reg_translate_for_x_format(instr_v);

    bin_enc[32] = ' ';
    bin_enc[33] = 'X';
    bin_enc[34] = '\0';

    return bin_enc;
}

char* extsw(int instr_c, char *instr_v[])
{
    // PO 011111
    bin_enc[0]='0';
    for(i=1;i<=5;i++)
    {
        bin_enc[i]='1';
    }

    // XO 1111011010
    for(i=21;i<=24;i++)
    {
        bin_enc[i]='1';
    }
    bin_enc[25]='0';
    bin_enc[26]='1';
    bin_enc[27]='1';
    bin_enc[28]='0';
    bin_enc[29]='1';
    bin_enc[30]='0';

    // Rc
    bin_enc[31]='0';

    // RS RA RB
    src_trgts_reg_translate_for_x_format(instr_v);

    bin_enc[32] = ' ';
    bin_enc[33] = 'X';
    bin_enc[34] = '\0';

    return bin_enc;
}

char* sld(int instr_c, char *instr_v[])
{
    // PO 011111
    bin_enc[0]='0';
    for(i=1;i<=5;i++)
    {
        bin_enc[i]='1';
    }

    // XO 0000011011
    for(i=21;i<=25;i++)
    {
        bin_enc[i]='0';
    }
    bin_enc[26]='1';
    bin_enc[27]='1';
    bin_enc[28]='0';
    bin_enc[29]='1';
    bin_enc[30]='1';

    // Rc
    bin_enc[31]='0';

    // RS RA RB
    src_trgts_reg_translate_for_x_format(instr_v);

    bin_enc[32] = ' ';
    bin_enc[33] = 'X';
    bin_enc[34] = '\0';

    return bin_enc;
}

char* srd(int instr_c, char *instr_v[])
{
    // PO 011111
    bin_enc[0]='0';
    for(i=1;i<=5;i++)
    {
        bin_enc[i]='1';
    }

    // XO 1000011011
    bin_enc[21]='1';
    for(i=22;i<=25;i++)
    {
        bin_enc[i]='0';
    }
    bin_enc[26]='1';
    bin_enc[27]='1';
    bin_enc[28]='0';
    bin_enc[29]='1';
    bin_enc[30]='1';

    // Rc
    bin_enc[31]='0';

    // RS RA RB
    src_trgts_reg_translate_for_x_format(instr_v);

    bin_enc[32] = ' ';
    bin_enc[33] = 'X';
    bin_enc[34] = '\0';

    return bin_enc;
}

char* srad(int instr_c, char *instr_v[])
{
    // PO 011111
    bin_enc[0]='0';
    for(i=1;i<=5;i++)
    {
        bin_enc[i]='1';
    }

    // XO 1100011010
    bin_enc[21]='1';
    bin_enc[22]='1';
    for(i=23;i<=25;i++)
    {
        bin_enc[i]='0';
    }
    bin_enc[26]='1';
    bin_enc[27]='1';
    bin_enc[28]='0';
    bin_enc[29]='1';
    bin_enc[30]='0';

    // Rc
    bin_enc[31]='0';

    // RS RA RB
    src_trgts_reg_translate_for_x_format(instr_v);

    bin_enc[32] = ' ';
    bin_enc[33] = 'X';
    bin_enc[34] = '\0';

    return bin_enc;
}




char* add(int instr_c, char *instr_v[])
{
    int32_t instr_hex;
    char a;
    int rt,ra,rb,j,l,b=0,k=6;
    char instr[] = "01111100000000000000001000010100 XO";                   //The binary with registernumbers filled as 0 initially
    int reg[5];                                                         //Temporary storage of register numbers in binary

    for(i=1;i<instr_c;i++){

        char* temp = instr_v[i];

        //To extract register number
        if(temp[2]=='\0')                   
            l = 1;
        else 
            l = 2;
        b=0;                                                            //Finding register number in decimal
        for(j=l;j>=1;j--){

            a = instr_v[i][j];
            int a1 = a-48;
            b = b + a1*pow(10,l-j);

        //    printf("%d ",l);
        }
        //printf("%d ",b);
        if(b>31)
        {
            printf("Invalid register number.\n");                       //Corner Case
            return '\0';
        }
        for(j=4;j>=0;j--)
        {
            reg[j] = b%2;
            b/=2;
        }
       /* for(j=0;j<5;j++)
        {
            printf("%d", reg[j]);
        }*/

        for(j=0;j<5;j++)                                                //Making the changes in the binary
        {
            if(reg[j]==0)
                instr[k+j] = '0';
            else
                instr[k+j] = '1';
        }
        k+=5;
      //  printf("%s ", instr);
    }    

    char* bin_final = (char*) malloc(sizeof(instr));
    bin_final = strcpy(bin_final, instr);

    return bin_final;
}

char* addi(int instr_c, char *instr_v[])
{
    int32_t instr_hex;
    char a;
    int rt,ra,j,l,b=0,k=6;
    char instr[] = "00111000000000000000000000000000 D";                  //The binary with register numbers filled as 0 initially
    int reg[5];                                                         //Temporary storage of register numbers in binary
    int imm[16];                                                        //Temporary storage of immediate value

    for(i=1;i<instr_c-1;i++){

        char* temp = instr_v[i];

        //To extract register number
        if(temp[2]=='\0')                   
            l = 1;
        else 
            l = 2;
        b=0;                                                            //Finding register number in decimal
        for(j=l;j>=1;j--){

            a = instr_v[i][j];
            int a1 = a-48;
            b = b + a1*pow(10,l-j);

        //    printf("%d ",l);
        }
        //printf("%d ",b);
        if(b>31)
        {
            printf("Invalid register number.\n");                       //Corner Case
            return '\0';
        }
        for(j=4;j>=0;j--)
        {
            reg[j] = b%2;
            b/=2;
        }
       /* for(j=0;j<5;j++)
        {
            printf("%d", reg[j]);
        }*/

        for(j=0;j<5;j++)                                                //Making the changes in the binary
        {
            if(reg[j]==0)
                instr[k+j] = '0';
            else
                instr[k+j] = '1';
        }
        k+=5;
    }

    //printf("%s ", instr);

    l = strlen(instr_v[3]);   
    b=0;

    for(i=l-1;i>=0;i--){                                              //Extracting the immediate value integer form the string array
        a = instr_v[3][i];
        int a1 = a-48;
        b = b + a1*pow(10,l-1-i);
    }
    for(i=15;i>=0;i--){                                               //Converting immediate to a 16-bit binary
        imm[i] = b%2;
        b/=2;
    }

    k = 16;
    for(j=0;j<16;j++)                                                //Making the changes in the binary
    {
        if(imm[j]==0)
            instr[k+j] = '0';
        else
            instr[k+j] = '1';
    }
    //printf("%s", instr);  

    char* bin_final = (char*) malloc(sizeof(instr);
    bin_final = strcpy(bin_final, instr);  

    return bin_final;
}

char* beq(int instr_c, char *instr_v[], int curr_addr)
{
    int32_t instr_hex;
    char* temp;
    char* instr[] = "01001100000000000000000000000000 B";                     //Binary with BD,BI and BO parts filled with 0's
    int addr,j,k=0,l,b=0,a;
    int bd[14],reg[5];
    struct symbol_table_text* ptr = sym_tab_text_head;
    while (ptr->next!=NULL)
    {
        temp = ptr->label;
        if(strcmp(temp, instr_v[3])==0)                         //Finding address of label to jump to
        {
            addr = temp->rel_add;
            break;
        }
        else
        {
            ptr = ptr->next;
        }
    }    
    if(ptr->next==NULL)                                         //Checking the last instruction
    {
        temp = ptr->label;
        if(strcmp(temp, instr_v[3])==0){
            addr = temp->rel_add;
        }
        else
        {
            printf("Invalid label\n");
            return '\0';
        }
    }
    int b = curr_addr - addr;                                   //The branch displacement
    k = 16;
    if(b>=0)                                                    //Branch displacement as a 14-bit binary
    {
        for(i=14;i>=0;i--)
        {   
            bd[i] = b%2;
            b/=2;
        }
        for(i=0;i<14;i++)
        {
            if(bd[i] == 0)
                instr[k+i] = '0';
            else
                instr[k+i] = '1';
        }
    }
    else                                                        //If Branch Displacement<0, calculate binary using 1's complement of -b-1;
    {
        b = b*(-1);
        b-=1;
        for(i=14;i>=0;i--)
        {   
            bd[i] = b%2;
            b/=2;
        }
        for(i=0;i<14;i++)
        {
            if(bd[i] == 0)
                instr[k+i] = '1';                               //The complements
            else
                instr[k+i] = '0';
        }
    }
    char* bin_final = (char*) malloc(sizeof(instr);
    bin_final = strcpy(bin_final, instr);
    for(i=1;i<instr_c-1;i++){                                   //Finding the register numbers to be compared.
        
        temp = instr_v[i];

        //To extract register number
        if(temp[2]=='\0')                   
            l = 1;
        else 
            l = 2;
        b=0;                                                            //Finding register number in decimal
        for(j=l;j>=1;j--){

            a = instr_v[i][j];
            int a1 = a-48;
            b = b + a1*pow(10,l-j);

        //    printf("%d ",l);
        }
        //printf("%d ",b);
  
        if(b>31)
        {
            printf("Invalid register number.\n");                       //Corner Case
            return -1;
        }
        for(j=4;j>=0;j--)
        {
            reg[j] = b%2;
            b/=2;
        }
       /* for(j=0;j<5;j++)
        {
            printf("%d", reg[j]);
        }*/
        k=6;

        for(j=0;j<5;j++)                                                //Making the changes in the binary
        {
            if(reg[j]==0)
                instr[k+j] = '0';
            else
                instr[k+j] = '1';
        }
        k+=5;
      //  printf("%s ", instr);
    }    

    char* bin_final = (char*) malloc(sizeof(instr)*sizeof(char));
    bin_final = strcpy(bin_final, instr);

    return bin_final;
}

char* subf(int instr_c, char *instr_v[])
{
    char a;
    int rt,ra,rb,i,j,l,b=0,k=6;
    char instr[] = "01111100000000000000000001010000 XO";                   //The binary with registernumbers filled as 0 initially
    int reg[5];                                                         //Temporary storage of register numbers in binary

    for(i=1;i<instr_c;i++){

        char* temp = instr_v[i];

        //To extract register number
        if(temp[2]=='\0')                   
            l = 1;
        else 
            l = 2;
        b=0;                                                            //Finding register number in decimal
        for(j=l;j>=1;j--){

            a = instr_v[i][j];
            int a1 = a-48;
            b = b + a1*pow(10,l-j);

        //    printf("%d ",l);
        }
        //printf("%d ",b);
        if(b>31)
        {
            printf("Invalid register number.\n");                       //Corner Case
            return "\0";
        }
        for(j=4;j>=0;j--)
        {
            reg[j] = b%2;
            b/=2;
        }
       /* for(j=0;j<5;j++)
        {
            printf("%d", reg[j]);
        }*/

        for(j=0;j<5;j++)                                                //Making the changes in the binary
        {
            if(reg[j]==0)
                instr[k+j] = '0';
            else
                instr[k+j] = '1';
        }
        k+=5;
      //  printf("%s ", instr);
    }    

    char* bin_final = (char*) malloc(sizeof(instr));
    bin_final = strcpy(bin_final, instr);

    return bin_final;
}