/*
    Ahsanullah University of Science and Technology
    Department of Computer Science and Engineering
    CSE 4130 (FALL 2020)                      Exam: Online 1
    Set: 2                                      ID: 170204036
*/
#include <stdio.h>
#include <string.h>
int main()
{

    FILE *f1;
    f1 = fopen("input_online1.c","r");
    int STRING[10000];
    char s[10000];


    char PARAMETER[1000],RETURNTYPE[1000];
    int flag=0;
    while(fgets(s,STRING,f1))
    {
        for(int i=0;i<strlen(s)-1;i++)
        {
            if(s[i]=='m')
            {

                    if(s[i]=='m' && s[i+1]=='a' && s[i+2]=='i' && s[i+3]=='n' && s[i+4]=='(')
                    {
                        i+=5;
                        int j=0;
                        while(s[i]!=')' && i<strlen(s))
                        {
                            PARAMETER[j]=s[i];
                            j++;
                            i++;
                        }
                    }

            }
            else if(s[i]=='r')
            {

                    if(s[i]=='r' && s[i+1]=='e' && s[i+2]=='t' && s[i+3]=='u' && s[i+4]=='r' && s[i+5]=='n' && s[i+6]==' ')
                    {
                        i+=7;
                        int j=0;
                        while(s[i]!=';' && i<strlen(s))
                        {
                            RETURNTYPE[j]=s[i];
                            j++;
                            i++;
                        }
                    }

            }
        }
    }
    fclose(f1);
    printf("PARAMETERmeter(s): %s\n",PARAMETER);
    printf("RETURNTYPEurn Value: %s",RETURNTYPE);

}
