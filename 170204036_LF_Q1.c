/*
Ahsanullah University of Science and Technology
Department of Computer Science and Engineering
Lab Final Examination
Course: CSE 4130 (Formal Languages and Compilers Lab)
Year/Sems: 4/1                           Session: FALL 2020
ID: 170204036                       Set: 2
*/

#include<stdio.h>
#include<string.h>

char a[10000];
int ln  =1;
int main()
{
    FILE *fp = fopen("input1.txt","r");
    int f1 = 0,f2 = 0,f3=0,i,f0=0;
    while(fgets(a,1000,fp))
    {

        int count = 0;
        f1 = 0;
        for(i=0;i<strlen(a);i++)
        {
            if(a[i]==34)
            {
                if(f3==1)
                    f3 = 0;
                else
                    f3 = 1;
            }
            else if(a[i]=='\'')
            {
                if(f3==1 || f1==1)
                    continue;
                if(f2==1)
                    f2 = 0;
                else
                    f2 = 1;
            }
            else if(a[i]=='\\')
            {
                if(f3==1)
                    continue;
                if(i+1<strlen(a) && a[i+1]=='\\')
                {
                    f1 = 1;
                    i++;
                }
                else if(i+1<strlen(a) && a[i+1]=='*')
                {
                    f0 = 1;
                    i++;
                }
            }
            else if(a[i]=='*')
            {
                if(i+1<strlen(a) && a[i+1]=='\\')
                {
                    f1 = 0;
                    i++;
                }
                else
                {
                    count++;
                }
            }
            else if(a[i]=='+' || a[i]=='-' || a[i]=='/')
            {
                count++;
            }

        }
        if(count>0)

            printf("Line No : .%d : No. of Arithmetic Operators %d\n",ln,count);
        ln++;
    }
}
