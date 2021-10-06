/*
Ahsanullah University of Science and Technology
Department of Computer Science and Engineering
CSE 4130 (FALL 2020)   Exam: Online 2
Set: 2     ID: 170204036
*/

#include<stdio.h>
#include<string.h>
int main()
{
    char a[1009];
    printf("Input String: ");
    scanf("%s",a);
    int i,n;
    n = strlen(a);
    int s = 0;
    int f = 0;
    for(i=0;i<n;i++)
    {
        if(a[i]>='a' && a[i]<='z')
        {
            if(s==0)
            {
                s = 1;
            }
            else
            {
                f = 1;
                break;
            }
        }
        else if(a[i]>='0' && a[i]<='9')
        {
            if(s==1 || s==2)
            {
                s = 2;
            }
            else if(s==5)
            {
                s = 6;
            }
            else
            {
                f = 1;
                break;
            }
        }
        else if(a[i]=='_')
        {
            if(s==2)
            {
                s = 3;
            }
            else
            {
                f = 1;
                break;
            }
        }
        else if(a[i]=='S')
        {
            if(s==3)
            {
                s = 4;
            }
            else
            {
                f = 1;
                break;
            }
        }
        else if(a[i]=='B')
        {
            if(s==4)
            {
                s = 5;
            }
            else
            {
                f = 1;
                break;
            }
        }

    }
    if(f==1)
        printf("String does not follow the pattern.\n");
    else printf("String follows the pattern.\n");

}
