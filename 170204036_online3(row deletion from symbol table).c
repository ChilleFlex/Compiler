/*
Ahsanullah University of Science and Technology
Department of Computer Science and Engineering
CSE 4130 (FALL 2020)                       Exam: Online 3
Set: 2                                     ID: 170204036
*/

#include<stdio.h>
#include<string.h>

int size = 0;

struct data{
    int number;
    char name[100];
    char type[100];
}v[100];

void rowDeletion(int x)
{
    int i;
    int flag = 0;
    for(i=0;i<size;i++)
    {
        if(v[i].no==x)
        {
            flag = 1;
            continue;
        }
        if(flag==1)
        {
            v[i-1]  = v[i];
            v[i-1].number--;
        }

    }
    size--;
}

void printOutput()
{
    int i=0;
    for(i=0;i<size;i++)
    {
        printf("%d %s %s\n",v[i].number,v[i].name,v[i].type);
    }
}
int main()
{
    FILE* fp = fopen("Online3_input.txt","r");
    int i=0;
    while(fscanf(fp,"%d %s %s",&v[i].number,v[i].name,v[i].type)!=EOF)
    {
        i++;
    }
    size = i;
    int x;
    printf("Row to be deleted: ");
    scanf("%d",&x);
    rowDeletion(x);
    printOutput();

}
