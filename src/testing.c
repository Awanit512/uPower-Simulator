#include <stdio.h>
#include <string.h>
#include <math.h>

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

void  main()
{
    printf("%d", bin_to_int("1001") );
}