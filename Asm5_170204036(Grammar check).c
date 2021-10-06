#include<stdio.h>
#include<string.h>

char inp[1000];
int pos =0;
int f = 0;

void reload()
{
    f = 0;
    pos = 0;
}

/////////////////////////////////////task 1

void A()
{
    if(strlen(inp)<2)
    {
        f=  0;
        return;
    }
    if(inp[pos]!='a')
    {
        f = 0;
        return;
    }
    pos++;
    X();
    if(f==1)
    {
        if(pos+1==strlen(inp) && inp[pos]=='d')
        {
            pos++;
            f = 1;
            return;
        }
        else
        {
            f = 0;
            return;
        }
    }
    else
    {
        f = 0;
        return;
    }
}

void X()
{
    if(pos+2<strlen(inp) && inp[pos]=='b' && inp[pos+1]=='b')
    {
        pos+=2;
        X();
        return;
    }
    if(pos+2<strlen(inp) && inp[pos]=='b' && inp[pos+1]=='c')
    {
        pos+=2;
        X();
        return;
    }
    if(pos+1<strlen(inp) && inp[pos]=='d')
    {
        pos++;
        f = 1;
        return;
    }
    //f = 1;
    return;
}

//////////////////////////////////task 2

void Exp()
{
    Term();
    if(pos==strlen(inp) || f==0)
    {
        return;
    }
    if(inp[pos]=='+' || inp[pos]=='-')
    {
        pos++;
        Term();

    }
}

void Term()
{
    Factor();
    if(pos==strlen(inp) || f==0)
    {
        return;
    }
    if(inp[pos]=='*' || inp[pos]=='/')
    {
        pos++;
        Factor();
    }
}

void Factor()
{
    ID();
    if(f==1)
        return;
    NUM();
    if(f==1)
        return;
    if(pos<strlen(inp) && inp[pos]=='(')
    {
        pos++;
        Exp();
        if(f==1)
        {
            if(pos<strlen(inp) && inp[pos]==')')
            {
                pos++;
                f = 1;
                return;
            }
            f = 0;
            return;
        }
        f = 0;
        return;

    }
    f =0;
    return;
}


void ID()
{
    if(pos<strlen(inp) && inp[pos]>='a' && inp[pos]<='e')
    {
        pos++;
        f  =1;
        return;
    }
    f = 0;
    return;
}

void NUM()
{
    if(pos<strlen(inp) && inp[pos]>='0' && inp[pos]<='9')
    {
        pos++;
        f  =1;
        return;
    }
    f = 0;
    return;
}

//////////////////////////task 3

void stat()
{
    int temp  =pos;
    asgn_stat();
    if(f==1)
        return;
    pos = temp;
    dscn_stat();
    if(f==1)
        return;
    pos=temp;
    loop_stat();
    if(f==1)
        return;
    f = 0;
    return;
}

void asgn_stat()
{
    if(pos+2<strlen(inp) && inp[pos]=='i' && inp[pos+1]=='d' && inp[pos+2]=='=')
    {
        pos+=3;
        expn();
        return;

    }
        f = 0;
        return;
}

void expn()
{
    Exp();
    if(f==1)
    {
        extn();
        return;
    }
    return;
}

void extn()
{
    int temp = pos;
    relop();
    if(f==1)
    {
        Exp();
        if(f==1)
        {
            return;
        }
    }
    pos = temp;
    f= 1;
    return;
}

void dscn_stat()
{
    if(pos+2<strlen(inp) && inp[pos]=='i' && inp[pos+1]=='f' && inp[pos+2]=='(')
    {
        pos+=3;
        expn();
        if(f==1)
        {
            if(pos<strlen(inp) && inp[pos]==')')
            {
                pos++;
                stat();
                if(f==1)
                {
                    extn1();
                    return;
                }
                else
                {
                    return;
                }
            }
            else
            {
                f = 0;
                return;
            }
        }
        else
        {
            return;
        }
    }
    f = 0;
    return;
}

void extn1()
{
    int temp = pos;
    if(pos+3<strlen(inp) && inp[pos]=='e' && inp[pos+1]=='l' && inp[pos+2]=='s' && inp[pos+3]=='e')
    {
        pos+=4;
        stat();
        if(f==1)
        {
            return;
        }

    }
    pos= temp;
    f =1;
    return;
}

void loop_stat()
{
    int temp = pos;
    if(pos+5<strlen(inp) && inp[pos]=='w' && inp[pos+1]=='h' && inp[pos+2]=='i' && inp[pos+3]=='l' && inp[pos+4]=='e' && inp[pos+5]=='(')
    {
        pos+= 6;
        expn();
        if(f==1 && pos<strlen(inp) && inp[pos]==')')
        {
            pos++;
            stat();
            if(f==1)
            {
                return;
            }
        }

    }
    pos = temp;
    if(pos+3<strlen(inp) && inp[pos]=='f' && inp[pos+1]=='o' && inp[pos+2]=='r' && inp[pos+3]=='(')
    {
        pos+=4;
        asgn_stat();
        if(f==1)
        {
            if(pos<strlen(inp) && inp[pos]==';')
            {
                pos++;
                expn();
                if(f==1)
                {
                    if(pos<strlen(inp) && inp[pos]==';')
                    {
                        pos++;
                        asgn_stat();
                        if(pos<strlen(inp) && inp[pos]==')')
                        {
                            pos++;
                            stat();
                            if(f==1)
                                return;
                        }
                    }
                }
            }
        }

    }
    f=  0;
    return;
}



void relop()
{
    if(pos+1<strlen(inp) && inp[pos]=='=' && inp[pos+1]=='=')
    {
        f = 1;
        pos+=2;
        return;
    }

    if(pos+1<strlen(inp) && inp[pos]=='!' && inp[pos+1]=='=')
    {
        f = 1;
        pos+=2;
        return;
    }
    if(pos+1<strlen(inp) && inp[pos]=='<' && inp[pos+1]=='=')
    {
        f = 1;
        pos+=2;
        return;
    }
    if(pos+1<strlen(inp) && inp[pos]=='>' && inp[pos+1]=='=')
    {
        f = 1;
        pos+=2;
        return;
    }
    if(pos<strlen(inp) && inp[pos]=='>')
    {
        f = 1;
        pos++;
        return;
    }
    if(pos<strlen(inp) && inp[pos]=='<')
    {
        f = 1;
        pos++;
        return;
    }
    f = 0;
    return;
}

int main()
{
    int flag = 0;
    printf("Input string : ");
    scanf("%s",inp);
    reload();
    A();
    if(f){
        printf("\nString verifies Grammar-1 \n");
        flag = 1;
    }
    reload();
    Exp();
    if(f==1 && pos==strlen(inp)){
        printf("\nString verifies Grammar-2 \n");
        flag = 1;
    }
    reload();
    stat();
    if(f==1 && pos==strlen(inp)){
        printf("\nString verifies Grammar-3 \n");
        flag = 1;
    }
    if(flag == 0)
        printf("Input string doesn't match any grammar!");

    return 0;

}
