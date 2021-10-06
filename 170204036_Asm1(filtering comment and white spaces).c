#include <stdio.h>

int main()
{
    FILE *ptr1,*ptr2;
    int temp = 0;
    char ch;

    ptr1 = fopen("input.c","r");
    ptr2 = fopen("output.txt","w");
    if(!ptr1)
    {
        printf("Can't read file");
        return 0;
    }
    if(!ptr2)
    {
        printf("Can't write file");
        return 0;
    }

    while((ch=fgetc(ptr1)) != EOF)
    {
         if((ch == 'm') && (temp == 0))
        {
            temp=1;
            continue;
        }
        else if((ch == 'a') && (temp == 1))
        {
            temp=2;
            continue;
        }
        else if((ch == 'i') && (temp == 2))
        {
            temp = 3;
            continue;
        }
        else if((ch == 'n') && (temp == 3))
        {
            temp = 4;
            continue;
        }
        else if((ch == '(') && (temp == 4))
        {
            temp = 5;
            continue;
        }
        if(temp == 5)
        {
            if((ch != ')'))
            {
               fputc(ch,ptr2);
            }
            continue;
        }

    }
    fclose(ptr1);
    fclose(ptr2);

    ptr1 = fopen("input.c","r");

    ptr2 = fopen("output.txt","r");

    while((ch=fgetc(ptr1)) != EOF )
    {
        printf("%c",ch);
    }

    printf("\n\n");
    while((ch=fgetc(ptr2)) != EOF )
    {
        printf("%c",ch);
    }

    fclose(ptr1);
    fclose(ptr2);

    return 0;
}
